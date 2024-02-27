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

time LD_PRELOAD=./build/libtimelord_wrapper.so ibrun ../lammps/build/lmp -in ../lammps/bench/in.lj > $data/lammps_mpi_${SLURM_NTASKS}_ew.txt
