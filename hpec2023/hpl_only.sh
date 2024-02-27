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


# HPL

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    ibrun ../hpl-2.3/bin/Linux_Intel64/xhpl > $data/hpl_baseline_${SLURM_NTASKS}_"${iter}".txt
done

