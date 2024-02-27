#!/bin/bash

#SBATCH -J 3akshlmp
#SBATCH -o akshaya_2.o%j
#SBATCH -e akshaya_2.e%j
#SBATCH -A TG-PEB220004
#SBATCH -p skx-normal
#SBATCH -N 64
#SBATCH --ntasks-per-node=48
#SBATCH -t 01:00:00


# module load gcc/7.1.0
# module load mkl/18.0.2

data="/work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/timelord_results"
export OMP_NUM_THREADS=1

export I_MPI_JOB_ABORT_SIGNAL=15
export I_MPI_JOB_SIGNAL_PROPAGATION=1
export I_MPI_FABRICS=tcp



max_iter=5
for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    # (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred/build/libtimelord_wrapper.so ibrun /work2/07431/tg867305/stampede2/timelord-miniamr/miniAMR.x --npx 16 --npy 16 --npz 12) > $data/miniamr_tl_${SLURM_NTASKS}_"${iter}"_x.txt 2>&1
    # (time ibrun /work2/07431/tg867305/stampede2/timelord-miniamr/miniAMR.x --npx 16 --npy 16 --npz 12) > $data/miniamr_tl_${SLURM_NTASKS}_"${iter}"_b.txt 2>&1
    # (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred/build/libtimelord_wrapper.so ibrun /work2/07431/tg867305/stampede2/HPEC2023/HPCCG/test_HPCCG 100 100 64) > $data/hpccg_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
    # (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred/build/libtimelord_wrapper.so ibrun /work2/07431/tg867305/stampede2/HPEC2023/lammps/build/lmp -in /work2/07431/tg867305/stampede2/HPEC2023/gitrepo/timelord-lammps/bench/in.lj) > $data/lammps_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
    # (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred/build/libtimelord_wrapper.so ibrun /work2/07431/tg867305/stampede2/HPEC2023/miniFE/mkl/src/miniFE.x -nx 1024 -ny 512 -nz 192) > $data/minife_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
    (time ibrun /work2/07431/tg867305/stampede2/HPEC2023/miniFE/mkl/src/miniFE.x -nx 1024 -ny 512 -nz 192) > $data/minife_tl_${SLURM_NTASKS}_"${iter}"_b.txt 2>&1
done
