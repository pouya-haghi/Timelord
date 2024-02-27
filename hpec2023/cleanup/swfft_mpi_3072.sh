#!/bin/bash

#SBATCH -J lammps_mpi_64_nodes_48_procs
#SBATCH -o lammps.o%j
#SBATCH -e lammps.e%j
#SBATCH -A TG-PEB220004
#SBATCH -p skx-normal
#SBATCH -N 64
#SBATCH --ntasks-per-node=48
#SBATCH -t 01:00:00


# module load gcc/7.1.0
# module load mkl/18.0.2

data="./timelord_results"
export OMP_NUM_THREADS=1
export I_MPI_PIN_PROCESSOR_LIST=allcores
export I_MPI_WAIT_MODE=0
export I_MPI_THREAD_YIELD=3
export I_MPI_THREAD_SLEEP=10

LD_PRELOAD=./build/libtimelord_wrapper.so ibrun ../SWFFT/build/TestDfft 100 768 768 768 > $data/lammps_mpi_${SLURM_NTASKS}_large.txt
