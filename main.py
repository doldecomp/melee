import os
import shutil
import subprocess
import sys
import csv

import calcprogress

repoPath = os.path.join(os.getcwd(), "tempRepo")
mwcc_compiler_path = os.path.join(os.getcwd(), "mwcc_compiler")


class CommitIterationEndChecker:
    def __init__(self, commit_id, inclusive: bool):
        self.commit_id = commit_id
        self.inclusive = inclusive


class CommitData:
    def __init__(self, commit_id, commit_date, calculated_progress: calcprogress.CalculatedProgress):
        self.commit_id = commit_id
        self.commit_date = commit_date
        self.calculated_progress = calculated_progress


def exec_cmd(cmd, return_code, shell=True):
    commands = cmd if isinstance(cmd, list) else [cmd]
    process = None
    stdout = None

    for command in commands:
        process = subprocess.Popen(command, shell=shell, cwd=repoPath, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout = process.communicate()[0]
        process.wait()

    return process.returncode if return_code else stdout.decode('utf-8').strip()


def stash_changes():
    return exec_cmd('git stash push tools/mwcc_compiler/', True)


def pop_stash_changes():
    return exec_cmd('git stash pop', True)


def pull():
    return exec_cmd('git pull', True)


def checkout_master():
    return exec_cmd(['git reset --hard origin/master', 'git checkout master'], True)


def checkout_previous_commit():
    # Delete untracked files before rolling back one commit
    return exec_cmd(['git clean -d -f .', 'git checkout HEAD~'], True)


def commit_amount():
    return exec_cmd('git rev-list --count master', False)


def get_current_commit_id():
    return exec_cmd('git rev-parse HEAD', False)


def get_current_commit_date(commit_id):
    return exec_cmd('git show -s --format=%ct ' + commit_id, False)


def make_clean():
    return exec_cmd('make clean', True)


def calc_progress():
    make_clean()
    exec_cmd('make GENERATE_MAP=1 -j', True)
    return calcprogress.calc_progress()


# Clone into tempRepo
if not os.path.isdir('tempRepo') and os.system('git clone https://github.com/doldecomp/melee/ tempRepo') != 0:
    sys.exit(-1)

checkout_master()
pull()


if not os.path.isdir(os.path.join(repoPath, "tools/mwcc_compiler")):
    shutil.copytree(mwcc_compiler_path, os.path.join(repoPath, "tools/mwcc_compiler"))

old_csv_exists = os.path.isfile('result.csv')
commit_iteration_end_checker = CommitIterationEndChecker('02e4891dec6f734c672d2bdc157062c4b7fcae1b', inclusive=True)

if old_csv_exists:
    with open('result.csv', 'r', newline='') as file:
        reader = csv.reader(file)

        last_row = None
        for commitData in reader:
            if len(commitData) >= 1:
                last_row = commitData
        commit_iteration_end_checker = CommitIterationEndChecker(last_row[0], inclusive=False)

collectedData = []

while True:
    current_commit_id = get_current_commit_id()
    current_commit_date = get_current_commit_date(current_commit_id)

    if current_commit_id == commit_iteration_end_checker.commit_id and not commit_iteration_end_checker.inclusive:
        break

    print("Current Commit: " + current_commit_id)
    print("Current Commit Date: " + current_commit_date)

    progress = calc_progress()

    if progress is None:
        print("Error! Couldn't compile this commit!")
    else:
        progress.output()
        collectedData.append(CommitData(current_commit_id, current_commit_date, progress))

    if current_commit_id == commit_iteration_end_checker.commit_id and commit_iteration_end_checker.inclusive:
        break

    stash_changes()  # make sure that mwcc_compiler doesn't get cleaned up
    if checkout_previous_commit() != 0:
        break
    pop_stash_changes()

with open('result.csv', 'a' if old_csv_exists else 'w', newline='') as file:
    wr = csv.writer(file)

    for commitData in reversed(collectedData):
        wr.writerow([
            commitData.commit_id,
            commitData.commit_date,
            commitData.calculated_progress.codeCompletionPcnt,
            commitData.calculated_progress.dataCompletionPcnt,
            commitData.calculated_progress.trophyCount,
            commitData.calculated_progress.eventCount
        ])

print(collectedData)
print(len(collectedData))
print("Done!")
