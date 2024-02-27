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
    (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred_func/build/libtimelord_wrapper_predictor.so ibrun ../gitrepo/timelord-lammps/build/lmp -in ../gitrepo/timelord-lammps/bench/in.lj) > $data/lammps_tlpred_${SLURM_NTASKS}_"${iter}".txt  2>&1
done

# HPCCG
for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred_func/build/libtimelord_wrapper_predictor.so ibrun ../gitrepo/timelord-hpccg/test_HPCCG 100 100 100) > $data/hpccg_tlpred_${SLURM_NTASKS}_"${iter}".txt  2>&1
done


# miniAMR
for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    # ------------------------------------------------------------------------------
    (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred_func/build/libtimelord_wrapper_predictor.so ibrun ../gitrepo/timelord-miniamr/miniAMR.x --npx 16 --npy 16 --npz 12) > $data/miniamr_tlpred_${SLURM_NTASKS}_"${iter}".txt  2>&1
done

# miniFE

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred_func/build/libtimelord_wrapper_predictor.so ibrun ../gitrepo/timelord-minife/src/miniFE.x -nx 1024 -ny 512 -nz 192) > $data/minife_tlpred_${SLURM_NTASKS}_"${iter}".txt 2>&1
done



