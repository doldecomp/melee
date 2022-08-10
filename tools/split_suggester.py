# Created by Daniel Cappel ("DRGN")
# Version 1.0
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
#		split_suggester.py [fileToSpli.s]
#					OR
#		split_suggester.py [fileToSpli.s] [mapFilePath.map]
#
# If a map file is provided, function names from it will be
# included in the generated function headers. If your data,
# text, and sdata sections are not in the same file, you may
# create a new file with them all included and input that.

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
mapFilePath = ''
if len( sys.argv ) < 2:
	print( 'Invalid input; you must provide one .s file to split.' )
	exit( 1 )
elif len( sys.argv ) == 3:
	if sys.argv[2].lower().endswith( '.map' ):
		mapFilePath = sys.argv[2]
	else:
		print( 'Invalid input; the second argument is expected to be a .map file.' )
		exit( 1 )
elif len( sys.argv ) > 3:
	print( 'Invalid input; got more than the expected one or two arguments.' )
	exit( 1 )


# For function processing
reachedDataSection = False
functionEndLikely = True
functionEndCertain = False
floatsData = OrderedDict([])
currentFunction = None
functions = []
mapNames = {}

# For sData processing
reachedSdata = False
firstValueProcessed = False
floatTypes = {}
susPadding = []
lastLabel = ''

# Running totals for section bytecounts
textBytes = 0
dataBytes = 0
sdataBytes = 0


class Function( object ):

	def __init__(self, name):
		self.name = name
		self.mapName = ''
		self.start = -1
		self.end = -1
		self.lines = []
		self.labels = []

		self._length = -1

	@property
	def length( self ):
		if self._length == -1:
			assert self.start != -1, 'Unable to calculate function length; start address not set for "{}".'.format(self.name)
			assert self.end != -1, 'Unable to calculate function length; end address not set for "{}".'.format(self.name)

			start = int( self.start, 16 )
			end = int( self.end, 16 )

			self._length = end - start
		
		return self._length

	def checkForMapName( self ):
		if mapNames and self.start != -1:
			name = mapNames.get( self.start )
			if name and not name.startswith( 'zz' ) and not name.endswith( '_' ):
				self.mapName = name


def align( x, base=32 ):
	
	""" Rounds up to nearest increment of [base] (default: 32 or 0x20). """
	
	return int( base * math.ceil(float(x) / base) )


def createFolders( folderPath ):
	try:
		os.makedirs( folderPath )

		# Primitive failsafe to prevent race condition
		attempt = 0
		while not os.path.exists( folderPath ):
			time.sleep( .3 )
			if attempt > 10:
				raise Exception( 'Unable to create folder: ' + folderPath )
			attempt += 1

	except OSError as error: # Python >2.5
		if error.errno == errno.EEXIST and os.path.isdir( folderPath ):
			pass
		else: raise


def userConfirms():

	""" Accepts input from the user. Anything starting with 
		'Y' or 'y' will return True; all else is False. """

	print( '' ) # Separates query from response

	if runningPython3:
		userInput = input()
	else:
		userInput = raw_input()
	
	return ( userInput.lower()[0] == 'y' )


# Parse the map file for function names
if mapFilePath:
	with open( mapFilePath, 'r' ) as mapFile:
		for line in mapFile:
			line = line.strip()
			if not line or line.startswith( '.' ):
				continue

			try:
				lineParts = line.split()
				funcStart = lineParts[0].upper()
				funcName = lineParts[-1]
				mapNames[funcStart] = funcName
			except:
				print( 'Unable to parse map file line: ' + line )


# Open the file to be split and parse its contents
fileToSplit = sys.argv[1]
with open( fileToSplit, 'r' ) as sourceFile:
	for line in sourceFile:
		line = line.split( '//' )[0] # Removes comments
		line = line.split( '#' )[0] # Removes comments
		line = line.strip() # Removes leading/trailing whitespace

		if not line:
			continue
		elif line.startswith( '.global ' ):
			functionEndCertain = True
			continue

		elif reachedSdata:
			if line.endswith( ':' ):
				lastLabel = line[:-1] # Strips colon
				firstValueProcessed = False
			elif line.startswith( '.4byte' ):
				stringValue = line.split()[-1]

				if firstValueProcessed:
					if floatType == 'single':
						# There may be a file boundary here.
						susPadding.append( lastLabel )

					elif floatType == 'double':
						valueBytes += bytearray.fromhex( stringValue.replace('0x', '') )
						value = struct.unpack( '>d', valueBytes )[0]
						floatsData[lastLabel] = ( lastLabel, 'double', value )
				else:
					floatType = floatTypes.get( lastLabel )

					if not floatType:
						print( 'Warning! Unable to determine a float type for ' + lastLabel )
						continue

					valueBytes = bytearray.fromhex( stringValue.replace('0x', '') )

					if floatType == 'single':
						value = struct.unpack( '>f', valueBytes )[0]
						floatsData[lastLabel] = ( lastLabel, 'single', value )
					
					firstValueProcessed = True

				sdataBytes += 4

		elif reachedDataSection:
			# Check for next section
			if line == '.section .sdata2':
				reachedSdata = True
				functions.append( currentFunction )

			# Tally byte total
			elif line.startswith( '.4byte' ):
				dataBytes += 4
			elif line.startswith( '.asciz' ):
				stringLength = len( line.split('"')[1] )
				dataBytes += align( stringLength+1, 4 )

		else: # Function processing
			# Check for next section
			if line == '.section .data':
				reachedDataSection = True
				continue

			if line.startswith( '/*' ): # Indicates a code line
				if line.endswith( 'blr' ):
					functionEndLikely = True

				# Check if this is a line referencing a float from sdata
				elif 'lbl_' in line:
					asm = line.split( '*/' )[1].lstrip()

					labelPortion = asm.split( ',' )[-1]
					label = labelPortion.split( '@' )[0].lstrip()

					if asm.startswith( 'lfs ' ):
						floatTypes[label] = 'single'
						currentFunction.labels.append( label )
					elif asm.startswith( 'lfd ' ):
						floatTypes[label] = 'double'
						currentFunction.labels.append( label )

				# Set the function's start address and the last function's end address
				if currentFunction.start == -1:
					lineParts = line.split()
					currentFunction.start = lineParts[1]
					currentFunction.checkForMapName()
					if len( functions ) > 1: # First item is None
						functions[-1].end = lineParts[1] # Previous function

				currentFunction.lines.append( line )
				textBytes += 4

			# Check if this is the start of a new function
			elif line.endswith( ':' ):
				label = line[:-1] # Removes colon
				
				# Check if the last line was THE end, or just AN end to the function
				if currentFunction and functionEndLikely and not functionEndCertain:
					for funcLine in currentFunction.lines:
						if funcLine.startswith( '/*' ): # Indicates a code line
							asm = funcLine.split( '*/' )[1].lstrip()

							# If a branch points to right after the blr, it's probably not the end of the full function
							if label in asm and asm.startswith( 'b' ):
								functionEndLikely = False
								if debugging:
									print( 'discredited function end on line', line )
									print( 'considering line', funcLine )
								break

				if functionEndLikely or functionEndCertain:
					functions.append( currentFunction )

					# Create a new function object to add properties to
					currentFunction = Function( label )
					functionEndLikely = False
					functionEndCertain = False
				else:
					currentFunction.lines.append( line )


# Sanity checks
if not reachedSdata:
	print( 'Unable to find the sdata2 section of the file!' )
	exit( 2 )
elif not floatsData:
	print( 'Unable to parse floats data from sdata2!' )
	exit( 3 )


# Account for alignment padding in byte usage totals
textBytes = align( textBytes, 8 )
dataBytes = align( dataBytes, 8 )
sdataBytes = align( sdataBytes, 8 )


# Set the last function's end address (the rest are set in the loop above)
lastCodeLine = functions[-1].lines[-1]
lineParts = lastCodeLine.split()
lineAddress = int( lineParts[1], 16 )
functions[-1].end = '{:X}'.format( lineAddress + 4 )


# Analyze padding among literals to look for file breaks
paddingBreaks = []
if susPadding:
	checkNextType = False
	for name, floatType, value in floatsData.values():
		if checkNextType:
			if floatType == 'single':
				paddingBreaks.append( name )
			checkNextType = False

		if name in susPadding:
			checkNextType = True
	if debugging:
		if paddingBreaks:
			print( 'File breaks suspected before these labels:' )
			print( paddingBreaks )
		else:
			print( 'Suspicious padding absolved.' )
elif debugging:
	print( 'No suspicious padding.' )


# Remove leading 'None' in functions list and get all function names
functions = functions[1:]
functionNames = [func.name for func in functions]


""" 	Separate functions - Pass 1

	Here, a multidimentional list is created, wherein the main list represents a list of files, 
	and each list within that will be a list of functions within that file. This pass checks for 
	float literal usage, and identifies file boundaries when new labels are used for floats that 
	were already available in sdata. File breaks determined from analyzing the padding among the 
	floats will also be applied here. """

labelsUsed = set()
fileList = [[]] # This will be a list of lists. Each list will be a list of functions for one file
for func in functions:
	# Add this to the last file if it references no float labels
	if not func.labels:
		fileList[-1].append( func )
		continue

	floatsInThisFunction = set()
	moveToNewFile = False

	for label in func.labels:
		floatInstance = floatsData.get( label )
		if not floatInstance:
			print( 'Warning! Unable to find a float for this label: ' + label )
			continue

		# Check for breaks due to usage of new instances of existing float literals
		if not moveToNewFile:
			for name, floatType, value in labelsUsed:
				if name != floatInstance[0] and floatType == floatInstance[1] and value == floatInstance[2]:
					if debugging:
						print( 'Moving {} to a new file due to float usage (using new {} {} value).'.format(func.name, floatType, value) )
					moveToNewFile = True
					if floatInstance[0] in paddingBreaks:
						paddingBreaks.remove( floatInstance[0] )
					break

		# Check for breaks due to padding
		if not moveToNewFile:
			if label in paddingBreaks:
				if debugging:
					print( 'Moving {} to a new file due to padding.'.format(func.name) )
				moveToNewFile = True
				paddingBreaks.remove( label )

		floatsInThisFunction.add( floatInstance )

	if moveToNewFile:
		# Move this function to a new list (which will be a new file)
		fileList.append( [func] )

		# Reset the labelsUsed so far in this new file to just those in this function
		labelsUsed = floatsInThisFunction
	else:
		# Add this function to the current file
		fileList[-1].append( func )

		# Add the float data collected for this function to those used in this file
		labelsUsed.update( floatsInThisFunction )


# Parse the given file for directory, filename, and extension
parentDir = os.path.dirname( fileToSplit )
filename = os.path.basename( fileToSplit ) # Includes extension
filename, ext = os.path.splitext( filename )


if debugging: # Print results so far
	print( '\nSuggesting {} files (after 1st pass):'.format(len(fileList)) )
	for i, functionList in enumerate( fileList, start=1 ):
		newFileName = filename + str(i) + ext
		print( '\n\t{}  |  {} functions'.format(newFileName, len(functionList)) )

		for func in functionList:
			print( '\t\t' + func.name )


""" 	Separate functions - Pass 2

	This pass will look at each function (starting from the last file and last function) and 
	determine if functions from the previous file are needed by it. Those files will then be 
	moved over to the current file if they are. """

currentFileIndex = -1
for functionList in reversed( fileList ):
	earliestFunction = -1

	for function in reversed( functionList ):
		# Gather a list of functions required by this current one
		requiredFunctions = set()
		for line in function.lines:
			for name in functionNames:
				# Check if a function name is in this line and it's not a label
				if name in line and not line.endswith( ':' ):
					requiredFunctions.add( name )
		
		# Exclude functions already in this file
		if requiredFunctions:
			if debugging:
				print( 'Found required functions for {}: {}'.format(function.name, requiredFunctions) )
			for funct in functionList:
				if funct.name in requiredFunctions:
					requiredFunctions.remove( funct.name )

		# If there are still required functions, check the previous file for them
		previousFileIndex = currentFileIndex - 1
		if requiredFunctions:
			# Ensure this isn't the first file (no previous file)
			if abs( previousFileIndex ) <= len( fileList ):
				if debugging:
					print( ' -> looking for these in previous file: {}'.format(requiredFunctions) )
				for functionIndex, funct in enumerate( fileList[previousFileIndex] ):
					if funct.name in requiredFunctions:
						# Remember the earliest file index and function index
						if earliestFunction == -1 or functionIndex < earliestFunction:
							if debugging:
								print( ' -> setting earliest funct to ' + str(earliestFunction) )
							earliestFunction = functionIndex
						requiredFunctions.remove( funct.name )

				if requiredFunctions and debugging:
					print( ' x  In file index {}'.format(previousFileIndex) )
					print( ' x  Unable to find these required functions for {} from the current or previous file: {}'.format(function.name, requiredFunctions) )

	# Move functions from the previous file to the current one if required functions were found
	if earliestFunction != -1:
		funcName = fileList[previousFileIndex][earliestFunction].name
		functionsToMove = fileList[previousFileIndex][earliestFunction:]
		if debugging:
			print( '\nMoving {} functions from file index {} to file index {},'.format(len(functionsToMove), previousFileIndex, currentFileIndex) )
			print( 'Starting from function at index {} ({})\n'.format(earliestFunction, funcName) )
		fileList[currentFileIndex] = functionsToMove + fileList[currentFileIndex]
		fileList[previousFileIndex] = fileList[previousFileIndex][:earliestFunction]

	currentFileIndex -= 1


# Print results
print( 'Total functions: ' + str(len(functions)) )
print( 'Total floats:    ' + str(len(floatTypes)) )
print( 'Text Section:    0x{:X} bytes'.format(textBytes) )
print( 'Data Section:    0x{:X} bytes'.format(dataBytes) )
print( 'sdata2 Section:  0x{:X} bytes'.format(sdataBytes) )
if debugging:
	print( 'All floats data:' )
	print( floatsData )
	print( '' )
	print( '\nSuggesting {} files  (after 2nd pass):'.format(len(fileList)) )
else:
	print( '\nSuggesting {} files:'.format(len(fileList)) )
for i, functionList in enumerate( fileList, start=1 ):
	newFileName = filename + str(i) + ext
	print( '\n\t{}  |  {} functions'.format(newFileName, len(functionList)) )

	for func in functionList:
		print( '\t\t' + func.name )


# Determine (and create) a directory to create the new files in
newParentDir = parentDir.replace( '\\asm\\', '\\src\\' )
if newParentDir.endswith( '\\ft\\chara' ): # Add a subfolder for characters
	charFolderName = 'ft' + filename[2].upper() + filename[3:]
	newParentDir = os.path.join( newParentDir, charFolderName )
createFolders( newParentDir )


# Ask if the user would like to create files and function headers
print( '\nWould you like to create files and function headers with these results?' )
print( 'These will be created in "{}"'.format(newParentDir) )
if not userConfirms():
	exit( 0 )


# Check for existing files
allExist = True
someExist = False
lines = []
for i, functionList in enumerate( fileList, start=1 ):
	newFileName = filename + str(i) + '.c'
	newFilePath = os.path.join( newParentDir, newFileName )

	if os.path.exists( newFilePath ):
		lines.append( '\t{} - Already exists'.format(newFileName) )
		someExist = True
	else:
		lines.append( '\t{}'.format(newFileName) )
		allExist = False


# Prompt to overwrite existing files
if allExist:
	print( '\nThe suggested files already exist.' )
	print( 'Would you like to overwrite them?' )
	overwrite = userConfirms()
elif someExist:
	print( '\nSome of the suggested files already exist.' )
	print( 'Would you like to overwrite these?' )
	print( '' )
	for line in lines:
		print( line )
	overwrite = userConfirms()
else: # No existing files
	overwrite = True


# Write output files
for i, functionList in enumerate( fileList, start=1 ):
	newFileName = filename + str(i) + '.c'
	newFilePath = os.path.join( newParentDir, newFileName )

	# Create a new name if the user doesn't wish to overwrite existing files
	if not overwrite and os.path.exists( newFilePath ):
		newFileName = filename + str(i) + ' - NEW.c'
		newFilePath = os.path.join( newParentDir, newFileName )

	with open( newFilePath, 'w' ) as cFile:
		cFile.write( '#include "{}.h"'.format(filename) )

		# Write headers for each function
		for function in functionList:
			cFile.write( '\n' )
			if function.mapName:
				cFile.write( '\n// {}'.format(function.mapName) )
			cFile.write( '\n// {} - {} (0x{:X} bytes)'.format(function.start, function.end, function.length) )
			cFile.write( '\n// ' ) # Placeholder line for scratch link

			# Write the float literals this function references
			for label in function.labels:
				name, floatType, value = floatsData.get( label )
				cFile.write( '\n// {} ({}: {})'.format(name, floatType, value) )

print( '\nFile templates created.' )