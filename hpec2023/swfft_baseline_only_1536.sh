#!/bin/bash

#SBATCH -J lammps_mpi_64_nodes_48_procs
#SBATCH -o lammps.o%j
#SBATCH -e lammps.e%j
#SBATCH -A TG-PEB220004
#SBATCH -p skx-normal
#SBATCH -N 32
#SBATCH --ntasks-per-node=48
#SBATCH -t 01:00:00


# module load gcc/7.1.0
# module load mkl/18.0.2

data="./timelord_results"
export OMP_NUM_THREADS=1

max_iter=3


# SWFFT

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    (time ibrun ../SWFFT/build/TestDfft 100 768 768 768) > $data/swfft_baseline_${SLURM_NTASKS}_"${iter}".txt 2>&1
done



