#!/bin/bash

#SBATCH -J swfft
#SBATCH -o swfft.o%j
#SBATCH -e swfft.e%j
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

max_iter=1

# SWFFT

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred/build/libtimelord_wrapper.so ibrun /work2/07431/tg867305/stampede2/HPEC2023/gitrepo/timelord-swfft/build/TestDfft 100 768) > $data/swfft_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
done



