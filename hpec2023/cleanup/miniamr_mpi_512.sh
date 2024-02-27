#!/bin/bash

#SBATCH -J miniamr_mpi_16_nodes_32_procs
#SBATCH -o miniamr.o%j
#SBATCH -e miniamr.e%j
#SBATCH -A TG-PEB220004
#SBATCH -p skx-normal
#SBATCH -N 16
#SBATCH --ntasks-per-node=32
#SBATCH -t 01:00:00


# module load gcc/7.1.0
# module load mkl/18.0.2

data="./timelord_results"
export OMP_NUM_THREADS=1
export I_MPI_PIN_PROCESSOR_LIST=allcores
export I_MPI_WAIT_MODE=0
export I_MPI_THREAD_YIELD=3
export I_MPI_THREAD_SLEEP=10

LD_PRELOAD=./build/libtimelord_wrapper.so ibrun ../miniAMR/ref/miniAMR.x --npx 8 --npy 8 --npz 8 > $data/miniamr_mpi_${SLURM_NTASKS}_large.txt
