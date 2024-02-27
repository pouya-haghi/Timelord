#!/bin/bash

#SBATCH -J lammps_mpi_64_nodes_48_procs
#SBATCH -o lammps.o%j
#SBATCH -e lammps.e%j
#SBATCH -A TG-PEB220004
#SBATCH -p skx-normal
#SBATCH -N 16
#SBATCH --ntasks-per-node=48
#SBATCH -t 01:00:00


# module load gcc/7.1.0
# module load mkl/18.0.2

data="./timelord_results"
export OMP_NUM_THREADS=1

export I_MPI_JOB_ABORT_SIGNAL=15
export I_MPI_JOB_SIGNAL_PROPAGATION=1
export I_MPI_FABRICS=tcp

export I_MPI_WAIT_MODE=0
export I_MPI_THREAD_YIELD=2



max_iter=3


# LAMMPS

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    # ------------------------------------------------------------------------------
    (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred/build/libtimelord_wrapper.so ibrun /work2/07431/tg867305/stampede2/HPEC2023/lammps/build/lmp -in /work2/07431/tg867305/stampede2/HPEC2023/gitrepo/timelord-lammps/bench/in.lj) > $data/lammps_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
done

# HPCCG
for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred/build/libtimelord_wrapper.so ibrun /work2/07431/tg867305/stampede2/HPEC2023/HPCCG/test_HPCCG 100 100 100) > $data/hpccg_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
done
# miniAMR
for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    # ------------------------------------------------------------------------------
    (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred/build/libtimelord_wrapper.so /work2/07431/tg867305/stampede2/HPEC2023/miniAMR/ref/miniAMR.x --npx 16 --npy 8 --npz 6) > $data/miniamr_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
done

# miniFE

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred/build/libtimelord_wrapper.so ibrun /work2/07431/tg867305/stampede2/HPEC2023/miniFE/mkl/src/miniFE.x -nx 1024 -ny 512 -nz 192) > $data/minife_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
done

# SWFFT

#for ((iter=1; iter<=$max_iter; iter=iter+1))
#do
    #(time LD_PRELOAD=/work2/07431/tg867305/stampede2/HPEC2023/hpec_os/build/libtimelord_wrapper.so ibrun ../../SWFFT/build/TestDfft 100 768 768 768) > $data/swfft_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
#done



