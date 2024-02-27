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

export I_MPI_JOB_ABORT_SIGNAL=15
export I_MPI_JOB_SIGNAL_PROPAGATION=1
export I_MPI_FABRICS=tcp

export I_MPI_WAIT_MODE=0
export I_MPI_THREAD_YIELD=2



max_iter=3


# LAMMPS

#for ((iter=1; iter<=$max_iter; iter=iter+1))
#do
    ## ------------------------------------------------------------------------------
    #LD_PRELOAD=./build/libtimelord_wrapper.so ibrun ../../lammps/build/lmp -in ../../lammps/bench/in.lj > $data/lammps_tl_${SLURM_NTASKS}_"${iter}".txt
#done

# HPCCG
for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    LD_PRELOAD=./build/libtimelord_wrapper.so ibrun ../../HPCCG/test_HPCCG 100 100 100 > $data/hpccg_tl_${SLURM_NTASKS}_"${iter}".txt
done

# HPL

#for ((iter=1; iter<=$max_iter; iter=iter+1))
#do
    #LD_PRELOAD=./build/libtimelord_wrapper.so ibrun ../../hpl-2.3/bin/Linux_Intel64/xhpl > $data/hpl_tl_${SLURM_NTASKS}_"${iter}".txt
#done

# miniAMR
for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    # ------------------------------------------------------------------------------
    LD_PRELOAD=./build/libtimelord_wrapper.so ibrun ../../miniAMR/ref/miniAMR.x --npx 16 --npy 16 --npz 12 > $data/miniamr_tl_${SLURM_NTASKS}_"${iter}".txt
done

# miniFE

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    (time LD_PRELOAD=./build/libtimelord_wrapper.so ibrun ../../miniFE/mkl/src/miniFE.x -nx 1024 -ny 512 -nz 192) > $data/minife_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
done

# SWFFT

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    (time LD_PRELOAD=./build/libtimelord_wrapper.so ibrun ../../SWFFT/build/TestDfft 100 768 768 768) > $data/swfft_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
done



