#!/bin/bash

#SBATCH -J miniamr_mpi_64_nodes_48_procs
#SBATCH -o miniamr.o%j
#SBATCH -e miniamr.e%j
#SBATCH -A TG-PEB220004
#SBATCH -p skx-normal
#SBATCH -N 32
#SBATCH --ntasks-per-node=48
#SBATCH -t 01:00:00


# module load gcc/7.1.0
# module load mkl/18.0.2

data="./timelord_results"
export OMP_NUM_THREADS=1

LD_PRELOAD=./build/libtimelord_wrapper.so ibrun ../miniAMR/ref/miniAMR.x --npx 16 --npy 12 --npz 8 > $data/miniamr_tl_${SLURM_NTASKS}.txt
