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

max_iter=3


# LAMMPS

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    # ------------------------------------------------------------------------------
    (time ibrun ../lammps/build/lmp -in ../lammps/bench/in.lj) > $data/lammps_baseline_${SLURM_NTASKS}_"${iter}".txt 2>&1
done

# HPCCG
for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    (time ibrun ../HPCCG/test_HPCCG 100 100 64) > $data/hpccg_baseline_${SLURM_NTASKS}_"${iter}".txt 2>&1
done

# HPL

#for ((iter=1; iter<=$max_iter; iter=iter+1))
#do
#    (time ibrun ../hpl-2.3/bin/Linux_Intel64/xhpl) > $data/hpl_baseline_${SLURM_NTASKS}_"${iter}".txt
#done

# miniAMR
for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    # ------------------------------------------------------------------------------
    (time ibrun ../miniAMR/ref/miniAMR.x --npx 16 --npy 16 --npz 12) > $data/miniamr_baseline_${SLURM_NTASKS}_"${iter}".txt 2>&1
done

# miniFE

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    (time ibrun ../miniFE/mkl/src/miniFE.x -nx 1024 -ny 512 -nz 192) > $data/minife_baseline_${SLURM_NTASKS}_"${iter}".txt 2>&1
done

# SWFFT

#for ((iter=1; iter<=$max_iter; iter=iter+1))
#do
#    (time ibrun ../SWFFT/build/TestDfft 100 768 768 768) > $data/swfft_baseline_${SLURM_NTASKS}_"${iter}".txt 2>&1
#done
#


