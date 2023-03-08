# Created by Daniel R. Cappel ("DRGN")
# Version 1.2
#
# Analyzes float constants used within a source ASM (.s) file
# to determine file boundaries. This considers duplicate float
# usage, calls that a function makes to other functions within
# the source file, and padding between single-precision floats.
#
# This will also offer to create the new source (.c) files for
# the user, with function headers including some function info.
#
# Usage:
#         split_suggester.py [fileToSplit.s]
#                     OR
#         split_suggester.py [fileToSplit.s] [mapFilePath.map]
#
# If a map file is provided, function names from it will be
# included in the generated function headers. If your data,
# text, and sdata sections are not in the same file, you may
# create a new file with them all included and input that.
#
# Exit codes:
#   0: Success; all parsing properly completed
#   1: Invalid program input
#   2: .sdata2 section not found in the file
#   3: Unable to find and parse floats data from sdata2

import os
import sys
import time
import math
import errno
import struct
from collections import OrderedDict

debugging = False

if sys.version_info[0] == 3:
    runningPython3 = True
else:
    runningPython3 = False

# Parse command line arguments
# Expecting the file to split and [optionally] a map file
mapFilePath = ""
if len(sys.argv) < 2:
    print("Invalid input; you must provide one .s file to split.")
    sys.exit(1)
elif len(sys.argv) == 3:
    if sys.argv[2].lower().endswith(".map"):
        mapFilePath = sys.argv[2]
    else:
        print("Invalid input; the second argument is expected to be a .map file.")
        sys.exit(1)
elif len(sys.argv) > 3:
    print("Invalid input; got more than the expected one or two arguments.")
    sys.exit(1)


# Tracking for which section is being parsed
fileSections = OrderedDict([])  # Key=sectionName, value=sectionSize
currentSection = ""
uncertainBytecounts = set()

# For function processing
functionEndLikely = True
functionEndCertain = False
floatsData = OrderedDict([])
currentFunction = None
functions = []
mapNames = {}

# For sData processing
firstValueProcessed = False
floatTypes = {}
susPadding = []
lastLabel = ""


class Function(object):
    def __init__(self, name):
        self.name = name
        self.mapName = ""
        self.start = -1
        self.end = -1
        self.lines = []
        self.labels = []  # Contains all refs in order, which may include duplicates
        self.uniqueLabels = []

        self._length = -1

    @property
    def length(self):
        if self._length == -1:
            assert (
                self.start != -1
            ), 'Unable to calculate function length; start address not set for "{}".'.format(
                self.name
            )
            assert (
                self.end != -1
            ), 'Unable to calculate function length; end address not set for "{}".'.format(
                self.name
            )

            start = int(self.start, 16)
            end = int(self.end, 16)

            self._length = end - start

        return self._length

    def checkForMapName(self):
        if mapNames and self.start != -1:
            name = mapNames.get(self.start)
            if name and not name.startswith("zz") and not name.endswith("_"):
                self.mapName = name

    def addLabel(self, label):
        self.labels.append(label)

        if label not in self.uniqueLabels:
            self.uniqueLabels.append(label)


def align(x, base=32):
    """Rounds up to nearest increment of [base] (default: 32 or 0x20)."""

    return int(base * math.ceil(float(x) / base))


def createFolders(folderPath):
    try:
        os.makedirs(folderPath)

        # Primitive failsafe to prevent race condition
        attempt = 0
        while not os.path.exists(folderPath):
            time.sleep(0.3)
            if attempt > 10:
                raise Exception("Unable to create folder: " + folderPath)
            attempt += 1

    except OSError as error:  # Python >2.5
        if error.errno == errno.EEXIST and os.path.isdir(folderPath):
            pass
        else:
            raise


def userConfirms():
    """Accepts input from the user. Anything starting with
    'Y' or 'y' will return True; all else is False."""

    print("")  # Separates query from response

    if runningPython3:
        userInput = input()
    else:
        userInput = raw_input()

    return userInput.lower()[0] == "y"


def grammarfyList( theList ):

    """ Converts a given iterable to a human-readable string. For example: 
        the list [apple, pear, banana] will be returned as the string 'apple, pear, and banana' """

    theList = list( theList )  # Ensure it's a list (could be a set, tuple, etc.)

    if len( theList ) == 1:
        return str( theList[0] )
    elif len( theList ) == 2:
        return str( theList[0] ) + ' and ' + str( theList[1] )
    else:
        return ', '.join( theList[:-1] ) + ', and ' + str( theList[-1] )


# Parse the map file for function names
if mapFilePath:
    with open(mapFilePath, "r") as mapFile:
        for line in mapFile:
            line = line.strip()
            if not line or line.startswith("."):
                continue

            try:
                lineParts = line.split()
                funcStart = lineParts[0].upper()
                funcName = lineParts[-1]
                mapNames[funcStart] = funcName
            except:
                print("Unable to parse map file line: " + line)


# Open the file to be split and parse its contents
fileToSplit = sys.argv[1]
with open(fileToSplit, "r") as sourceFile:
    for line in sourceFile:
        line = line.split("//")[0]  # Removes comments
        line = line.split("#")[0]  # Removes comments
        line = line.strip()  # Removes leading and trailing whitespace

        if not line:
            continue
        elif line.startswith(".global "):
            functionEndCertain = True
            continue

        # Track what file section we're in
        elif line.startswith(".section"):
            sectionName = line.split()[1].replace(",", "")
            fileSections[sectionName] = 0  # Initialize section data length
            currentSection = sectionName

            # Ensure the last function from the data section is collected
            if len( fileSections ) == 2:  # Assumes .text is always first
                functions.append(currentFunction)

            continue

        # Start parsing for specific sections
        elif currentSection == ".sdata2":
            if line.endswith(":"):
                lastLabel = line[:-1]  # Strips colon
                firstValueProcessed = False

            elif line.startswith(".4byte") or line.startswith(".float"):
                stringValue = line.split()[-1]
                if stringValue == "NULL":
                    stringValue = "00000000"

                if firstValueProcessed:
                    # Now processing for the latter 4 bytes of what could be a double
                    if floatType == "f32":
                        # There may be a file boundary here.
                        susPadding.append(lastLabel)

                    elif floatType == "f64":
                        # Combine these bytes with those from the previous line
                        if line.startswith(".float"):
                            # The value is already decoded; need to re-encode the value as raw bytes
                            valueBytes += struct.pack(">f", float(stringValue))
                        else:
                            valueBytes += bytearray.fromhex(stringValue.replace("0x", ""))

                        # Decode the value as a double and store it
                        value = struct.unpack(">d", valueBytes)[0]
                        floatsData[lastLabel] = (lastLabel, "f64", value)

                # Process a single or the first 4 bytes of a double
                else:
                    # Get the type that this script found
                    floatType = floatTypes.get(lastLabel)
                    if not floatType:
                        print(
                            "Warning! Unable to determine a float type for " + lastLabel
                        )
                        continue

                    if line.startswith(".float"):
                        # The value is already decoded; need to re-encode the 
                        # value as raw bytes (in case this is actually a double).
                        valueBytes = struct.pack(">f", float(stringValue))

                        if floatType == "f32":
                            floatsData[lastLabel] = (lastLabel, "f32", float(stringValue))
                        else: # convert_data.py thought this was a single, but it's a double
                            print("{} is described in the file as a single, but appears to be a double.".format(lastLabel))

                    else: # Handling for an undetermined .4byte
                        valueBytes = bytearray.fromhex(stringValue.replace("0x", ""))

                        if floatType == "f32":
                            value = struct.unpack(">f", valueBytes)[0]
                            floatsData[lastLabel] = (lastLabel, "f32", value)

                    firstValueProcessed = True

                fileSections[".sdata2"] += 4

            elif line.startswith(".double"):
                stringValue = line.split()[-1]
                if stringValue == "NULL":
                    stringValue = "00000000"

                # Get the type that this script found
                floatType = floatTypes.get(lastLabel)
                if not floatType:
                    print(
                        "Warning! Unable to determine a float type for " + lastLabel
                    )
                    continue
                
                # Store this literal as a double or a single
                if floatType == "f64":
                    floatsData[lastLabel] = (lastLabel, "f64", float(stringValue))

                else: # convert_data.py thought this was a double, but it's a single
                    # There may be a file boundary here.
                    susPadding.append(lastLabel)

                    # Re-encode the value back to 8 bytes, and decode just the first 4 as a single
                    valueBytes = struct.pack(">d", float(stringValue))
                    value = struct.unpack(">f", valueBytes[:4])[0]
                    floatsData[lastLabel] = (lastLabel, "f32", value)
                    print("{} is described in the file as a double, but appears to be a single.".format(lastLabel))

        # Function processing
        elif currentSection == ".text":
            if line.startswith("/*"):  # Indicates a code line
                if line.endswith("blr"):
                    functionEndLikely = True

                # Check if this is a line referencing a float from sdata
                elif "lbl_" in line:
                    asm = line.split("*/")[1].lstrip()

                    labelPortion = asm.split(",")[-1]
                    label = labelPortion.split("@")[0].lstrip()

                    if asm.startswith("lfs "):
                        floatTypes[label] = "f32"
                        currentFunction.addLabel(label)
                    elif asm.startswith("lfd "):
                        floatTypes[label] = "f64"
                        currentFunction.addLabel(label)

                # Set the function's start address and the last function's end address
                if currentFunction.start == -1:
                    lineParts = line.split()
                    currentFunction.start = lineParts[1]
                    currentFunction.checkForMapName()
                    if len(functions) > 1:  # First item is None
                        functions[-1].end = lineParts[1]  # Previous function

                currentFunction.lines.append(line)
                fileSections[".text"] += 4

            # Check if this is the start of a new function
            elif line.endswith(":"):
                label = line[:-1]  # Removes colon

                # Check if the last line was THE end, or just AN end to the function
                if currentFunction and functionEndLikely and not functionEndCertain:
                    for funcLine in currentFunction.lines:
                        if funcLine.startswith("/*"):  # Indicates a code line
                            asm = funcLine.split("*/")[1].lstrip()

                            # If a branch points to right after the blr, it's probably not the end of the full function
                            if label in asm and asm.startswith("b"):
                                functionEndLikely = False
                                if debugging:
                                    print("discredited function end on line", line)
                                    print("considering line", funcLine)
                                break

                if functionEndLikely or functionEndCertain:
                    functions.append(currentFunction)

                    # Create a new function object to add properties to
                    currentFunction = Function(label)
                    functionEndLikely = False
                    functionEndCertain = False
                else:
                    currentFunction.lines.append(line)

        # Tally byte totals for other sections
        elif line.startswith(".4byte") or line.startswith(".float"):
            fileSections[currentSection] += 4
        elif line.startswith(".asciz"):
            stringLength = len(line.split('"')[1])
            fileSections[currentSection] += align(stringLength + 1, 4)
        elif line.startswith(".skip"):
            skipAmount = int(line.split()[1], 16)
            fileSections[currentSection] += skipAmount
        elif line.startswith(".int"):
            fileSections[currentSection] += 4  # Can these be single bytes or halfwords?
            uncertainBytecounts.add(currentSection)


# Sanity checks
if ".sdata2" not in fileSections:
    print("Unable to find the .sdata2 section of the file!")
    sys.exit(2)
elif not floatsData:
    print("Unable to parse floats data from sdata2!")
    sys.exit(3)


# Account for alignment padding in byte usage totals
for section, byteTotal in list(fileSections.items())[:1]:  # Skips last section!
    fileSections[section] = align(byteTotal, 8)


# Set the last function's end address (the rest are set in the loop above)
lastCodeLine = functions[-1].lines[-1]
lineParts = lastCodeLine.split()
lineAddress = int(lineParts[1], 16)
functions[-1].end = "{:X}".format(lineAddress + 4)


# Analyze padding among literals to look for file breaks
paddingBreaks = []
if susPadding:
    checkNextType = False
    for name, floatType, value in floatsData.values():
        if checkNextType:
            if floatType == "f32":
                paddingBreaks.append(name)
            checkNextType = False

        if name in susPadding:
            checkNextType = True
    if debugging:
        if paddingBreaks:
            print("File breaks suspected before these labels:")
            print(paddingBreaks)
        else:
            print("Suspicious padding absolved.")
elif debugging:
    print("No suspicious padding.")


# Remove leading 'None' in functions list and get all function names
functions = functions[1:]
functionNames = [func.name for func in functions]


"""     Separate functions - Pass 1

    Here, a multi-dimentional list is created, wherein the main list represents a list of files,
    and each list within that will be a list of functions within that file. This pass checks for
    float literal usage, and identifies file boundaries when new labels are used for floats that
    were already available in sdata. File breaks determined from analyzing the padding among the
    floats will also be applied here. """

floatWarnings = set()
labelsUsed = set()
fileList = [
    []
]  # This will be a list of lists. Each list will be a list of functions for one file
for func in functions:
    # Add this to the last file if it references no float labels
    if not func.labels:
        fileList[-1].append(func)
        continue

    floatsInThisFunction = set()
    moveToNewFile = False

    for label in func.labels:
        floatInstance = floatsData.get(label)
        if not floatInstance:
            if label not in floatWarnings:  # Prevent duplicate warnings
                print("Warning! Unable to parse float information for " + label)
                floatWarnings.add(label)
            continue

        # Check for breaks due to usage of new instances of existing float literals
        if not moveToNewFile:
            for name, floatType, value in labelsUsed:
                if (
                    name != floatInstance[0]
                    and floatType == floatInstance[1]
                    and value == floatInstance[2]
                ):
                    if debugging:
                        print(
                            "Moving {} to a new file due to float usage (using new {} {} value).".format(
                                func.name, floatType, value
                            )
                        )
                    moveToNewFile = True
                    if floatInstance[0] in paddingBreaks:
                        paddingBreaks.remove(floatInstance[0])
                    break

        # Check for breaks due to padding
        if not moveToNewFile:
            if label in paddingBreaks:
                if debugging:
                    print("Moving {} to a new file due to padding.".format(func.name))
                moveToNewFile = True
                paddingBreaks.remove(label)

        floatsInThisFunction.add(floatInstance)

    if moveToNewFile:
        # Move this function to a new list (which will be a new file)
        fileList.append([func])

        # Reset the labelsUsed so far in this new file to just those in this function
        labelsUsed = floatsInThisFunction
    else:
        # Add this function to the current file
        fileList[-1].append(func)

        # Add the float data collected for this function to those used in this file
        labelsUsed.update(floatsInThisFunction)


# Parse the given file for directory, filename, and extension
parentDir = os.path.dirname(fileToSplit)
filename = os.path.basename(fileToSplit)  # Includes extension
filename, ext = os.path.splitext(filename)


if debugging:  # Print results so far
    print("\nSuggesting {} files (after 1st pass):".format(len(fileList)))
    for i, functionList in enumerate(fileList, start=1):
        newFileName = filename + str(i) + ext
        print("\n\t{}  |  {} functions".format(newFileName, len(functionList)))

        for func in functionList:
            print("\t\t" + func.name)


"""     Separate functions - Pass 2

    This pass will look at each function (starting from the last file and last function) and
    determine if functions from the previous file are needed by it. Those files will then be
    moved over to the current file if they are. """

currentFileIndex = -1
for functionList in reversed(fileList):
    earliestFunction = -1

    for function in reversed(functionList):
        # Gather a list of functions required by this current one
        requiredFunctions = set()
        for line in function.lines:
            for name in functionNames:
                # Check if a function name is in this line and it's not a label
                if name in line and not line.endswith(":"):
                    requiredFunctions.add(name)

        # Exclude functions already in this file
        if requiredFunctions:
            if debugging:
                print(
                    "Found required functions for {}: {}".format(
                        function.name, requiredFunctions
                    )
                )
            for funct in functionList:
                if funct.name in requiredFunctions:
                    requiredFunctions.remove(funct.name)

        # If there are still required functions, check the previous file for them
        previousFileIndex = currentFileIndex - 1
        if requiredFunctions:
            # Ensure this isn't the first file (no previous file)
            if abs(previousFileIndex) <= len(fileList):
                if debugging:
                    print(
                        " -> looking for these in previous file: {}".format(
                            requiredFunctions
                        )
                    )
                for functionIndex, funct in enumerate(fileList[previousFileIndex]):
                    if funct.name in requiredFunctions:
                        # Remember the earliest file index and function index
                        if earliestFunction == -1 or functionIndex < earliestFunction:
                            if debugging:
                                print(
                                    " -> setting earliest funct to "
                                    + str(earliestFunction)
                                )
                            earliestFunction = functionIndex
                        requiredFunctions.remove(funct.name)

                if requiredFunctions and debugging:
                    print(" x  In file index {}".format(previousFileIndex))
                    print(
                        " x  Unable to find these required functions for {} from the current or previous file: {}".format(
                            function.name, requiredFunctions
                        )
                    )

    # Move functions from the previous file to the current one if required functions were found
    if earliestFunction != -1:
        funcName = fileList[previousFileIndex][earliestFunction].name
        functionsToMove = fileList[previousFileIndex][earliestFunction:]
        if debugging:
            print(
                "\nMoving {} functions from file index {} to file index {},".format(
                    len(functionsToMove), previousFileIndex, currentFileIndex
                )
            )
            print(
                "Starting from function at index {} ({})\n".format(
                    earliestFunction, funcName
                )
            )
        fileList[currentFileIndex] = functionsToMove + fileList[currentFileIndex]
        fileList[previousFileIndex] = fileList[previousFileIndex][:earliestFunction]

    currentFileIndex -= 1


# Print results
print("  Total functions:            " + str(len(functions)))
print("  Total floats (in sdata2):   " + str(len(floatTypes)))
for section, byteTotal in fileSections.items():
    sectionName = section + " section:"
    print("  {:28}0x{:X} bytes".format(sectionName, byteTotal))
if uncertainBytecounts:
    if len(uncertainBytecounts) == 1:
        print('(The bytecount for ' + next(iter(uncertainBytecounts)) + ' is uncertain, because it contains ints of unknown size.)' )
    else:
        print('(The bytecounts for ' + grammarfyList(uncertainBytecounts) + ' are uncertain, because they contain ints of unknown size.)' )

if mapNames:
    print("\n\t(Function names found in the map file are shown to the right.)")
fileCount = len(fileList)
if debugging:
    print("\nAll floats data:")
    print(floatsData)
    print("\nAll float types:")
    print(floatTypes)
    print("")
    if fileCount == 1:
        print("\nSuggesting 1 file  (after 2nd pass):")
    else:
        print("\nSuggesting {} files  (after 2nd pass):".format(fileCount))
else:
    if fileCount == 1:
        print("\nSuggesting 1 file:")
    else:
        print("\nSuggesting {} files:".format(fileCount))
for i, functionList in enumerate(fileList, start=1):
    newFileName = filename + str(i) + ext
    print("\n\t{}  |  {} functions".format(newFileName, len(functionList)))
    for func in functionList:
        if func.mapName:
            print("\t\t{}\t\t({})".format(func.name, func.mapName))
        else:
            print("\t\t" + func.name)


# Determine (and create) a directory to create the new files in
newParentDir = parentDir.replace("\\asm\\", "\\src\\")
if newParentDir.endswith("\\ft\\chara"):  # Add a subfolder for characters
    charFolderName = "ft" + filename[2].upper() + filename[3:]
    newParentDir = os.path.join(newParentDir, charFolderName)
createFolders(newParentDir)


# Ask if the user would like to create files and function headers
print("\nWould you like to create files and function headers with these results? (y/n)")
print('These will be created in "{}"'.format(newParentDir))
if not userConfirms():
    sys.exit(0)


# Check for existing files
allExist = True
someExist = False
lines = []
for i, functionList in enumerate(fileList, start=1):
    newFileName = filename + str(i) + ".c"
    newFilePath = os.path.join(newParentDir, newFileName)

    if os.path.exists(newFilePath):
        lines.append("\t{} - Already exists".format(newFileName))
        someExist = True
    else:
        lines.append("\t{}".format(newFileName))
        allExist = False


# Prompt to overwrite existing files
if allExist:
    print("\nThe suggested files already exist.")
    print("Would you like to overwrite them? (y/n)")
    overwrite = userConfirms()
elif someExist:
    print("\nSome of the suggested files already exist.")
    print("Would you like to overwrite these? (y/n)")
    print("")
    for line in lines:
        print(line)
    overwrite = userConfirms()
else:  # No existing files
    overwrite = True


# Build the string for the relative header-include path
head, tail = os.path.split(newParentDir)
pathParts = [tail, filename]
while True:
    # Grab each part of the path until we reach the folder above the 'melee' folder
    head, tail = os.path.split(head)
    pathParts.insert(0, tail)

    if tail == "melee":  # The new path will start with this
        includePath = "#include <{}.h>".format("/".join(pathParts))
        break
    elif not tail: # Failsafe; reached the drive root directory
        print('Warning: Unable to determine an include path for headers.')
        includePath = ""
        break


# Write output files
for i, functionList in enumerate(fileList, start=1):
    # Create the file name and path
    newFileName = filename + str(i) + ".c"
    newFilePath = os.path.join(newParentDir, newFileName)

    # Create a new name if the user doesn't wish to overwrite existing files
    if not overwrite and os.path.exists(newFilePath):
        newFileName = filename + str(i) + " - NEW.c"
        newFilePath = os.path.join(newParentDir, newFileName)

    with open(newFilePath, "w") as cFile:
        if includePath:
            cFile.write(includePath)

        # Write out all of the floats that will be referenced 
        # in the following functions (i.e. those from sdata2).
        alreadyWritten = []
        for function in functionList:
            for label in function.uniqueLabels:
                if label not in alreadyWritten:
                    name, floatType, value = floatsData.get(label)
                    cFile.write("\n// {} const {} = {};".format(floatType, name, value))
                    alreadyWritten.append(label)
        cFile.write("\n")

        # Write headers for each function
        for function in functionList:
            cFile.write("\n")
            if function.mapName:
                cFile.write("\n// {}".format(function.mapName))
            cFile.write(
                "\n// {} - {} (0x{:X} bytes)".format(
                    function.start, function.end, function.length
                )
            )
            cFile.write("\n// ")  # Placeholder line for scratch link

            # Write the float literals this function references
            for label in function.uniqueLabels:
                name, floatType, value = floatsData.get(label)
                cFile.write("\n// {} ({}: {})".format(name, floatType, value))

print("\nFile templates created.")
