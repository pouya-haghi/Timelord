import os
import re
from collections import defaultdict
import numpy as np

def parse( filename):
    res = {}
    with open(filename) as f:
        lines = f.readlines()
        original, new =[], []
        for line in lines:
            if 'original' in line:
                original.append(float(line.split()[-2]))
            if 'new' in line:
                new.append(float(line.split()[-2]))
    return np.array(original), np.array(new)
    

# Create a dictionary to hold the lists
lists = defaultdict(list)

# Loop over the files in the current directory
for file in os.listdir('.'):
    # Check if the file matches the pattern "file_procs_trial.txt"
    match = re.match(r'collective_([0-9]+)_([0-9]+)\.txt', file)
    if match:
        # Extract the proc and trial numbers
        proc, trial = match.groups()

        # Add the file to the corresponding list
        lists[(proc, trial)].append(file)


groups = {'768': [], '1536': [], '3072': []}

for key in lists:
    proc, trial =key
    groups[proc].append(lists[key])

mpi = ['Allreduce', 'Alltoall', 'Gather', 'Allgather', 'Scatter', 'Reduce', 'Bcast']

for proc in groups:

    print("processes:",  proc)
    original = np.zeros(7)
    new = np.zeros(7)
    for fil in groups[proc]:
        res  = parse(fil[0])
        original += res[0]
        new += res[1]
    original = original / 3
    new = new / 3
    print("original")
    for call, time in zip(mpi, original):
        print(call, time)
    print()
    print("new")
    for call, time in zip(mpi, new):
        print(call, time)

    print()
