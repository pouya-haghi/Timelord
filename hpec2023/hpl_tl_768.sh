#!/bin/bash

#SBATCH -J hpl_mpi_64_nodes_48_procs
#SBATCH -o hpl.o%j
#SBATCH -e hpl%j
#SBATCH -A TG-PEB220004
#SBATCH -p skx-normal
#SBATCH -N 16
#SBATCH --ntasks-per-node=48
#SBATCH -t 01:00:00


# module load gcc/7.1.0
# module load mkl/18.0.2

data="./timelord_results"
export OMP_NUM_THREADS=1



LD_PRELOAD=./build/libtimelord_wrapper.so ibrun ../hpl-2.3/bin/Linux_Intel64/xhpl > $data/hpl_tl_${SLURM_NTASKS}.txt
