#!/bin/bash

#SBATCH -J lammps_mpi_64_nodes_48_procs
#SBATCH -o lammps.o%j
#SBATCH -e lammps.e%j
#SBATCH -A TG-PEB220004
#SBATCH -p skx-normal
#SBATCH -N 1
#SBATCH --ntasks-per-node=48
#SBATCH -t 01:00:00


# module load gcc/7.1.0
# module load mkl/18.0.2

#export I_MPI_PIN=0
#export I_MPI_FALLBACK=1
export I_MPI_JOB_ABORT_SIGNAL=15
export I_MPI_JOB_SIGNAL_PROPAGATION=1
export I_MPI_FABRICS=tcp

export I_MPI_WAIT_MODE=0
export I_MPI_THREAD_YIELD=2


LD_PRELOAD=./build/libtimelord_wrapper.so ibrun ./build/app > log.txt


