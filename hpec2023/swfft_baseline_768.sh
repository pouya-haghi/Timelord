#!/bin/bash

#SBATCH -J swfft_mpi_64_nodes_48_procs
#SBATCH -o swfft.o%j
#SBATCH -e swfft%j
#SBATCH -A TG-PEB220004
#SBATCH -p skx-normal
#SBATCH -N 16
#SBATCH --ntasks-per-node=48
#SBATCH -t 01:00:00


# module load gcc/7.1.0
# module load mkl/18.0.2

data="./timelord_results"
export OMP_NUM_THREADS=1

(time ibrun ../SWFFT/build/TestDfft 100 768 768 768) > $data/swfft_baseline_${SLURM_NTASKS}.txt 2>&1
