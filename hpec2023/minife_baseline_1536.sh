#!/bin/bash

#SBATCH -J minife_mpi_32_nodes_48_procs
#SBATCH -o minife.o%j
#SBATCH -e minife.e%j
#SBATCH -A TG-PEB220004
#SBATCH -p skx-normal
#SBATCH -N 32
#SBATCH --ntasks-per-node=48
#SBATCH -t 01:00:00


# module load gcc/7.1.0
# module load mkl/18.0.2

data="./timelord_results"
export OMP_NUM_THREADS=1

(time ibrun ../miniFE/mkl/src/miniFE.x -nx 60 -ny 60 -nz 60) > $data/minife_baseline_${SLURM_NTASKS}.txt 2>&1
