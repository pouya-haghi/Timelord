#!/bin/bash

#SBATCH -J colletive_mpi_64_nodes_48_procs
#SBATCH -o collect.o%j
#SBATCH -e collect.e%j
#SBATCH -A TG-PEB220004
#SBATCH -p skx-normal
#SBATCH -N 64
#SBATCH --ntasks-per-node=48
#SBATCH -t 01:00:00


# module load gcc/7.1.0
# module load mkl/18.0.2

data="./collection"
export OMP_NUM_THREADS=1

max_iter=3


# LAMMPS

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    # ------------------------------------------------------------------------------
    ibrun ./collective_test > $data/collective_${SLURM_NTASKS}_"${iter}".txt 2>&1
done
