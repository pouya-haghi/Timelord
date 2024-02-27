#!/bin/bash

#SBATCH -J lammps_os_32_nodes_48_procs
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
export I_MPI_WAIT_MODE=0
export I_MPI_THREAD_YIELD=3
export I_MPI_THREAD_SLEEP=10

time ibrun ../lammps/build/lmp -in ../lammps/bench/in.lj > $data/lammps_os_${SLURM_NTASKS}_baseline_yield.txt
