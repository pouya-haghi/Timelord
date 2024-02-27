#!/bin/bash

#SBATCH -J hpcg32
#SBATCH -o hpcg32.o%j
#SBATCH -e hpcg32.e%j
#SBATCH -A TG-PEB220004
#SBATCH -p skx-normal
#SBATCH -N 32
#SBATCH --ntasks-per-node=48
#SBATCH -t 01:00:00


# module load gcc/7.1.0
# module load mkl/18.0.2

data="/work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/timelord_results"
export OMP_NUM_THREADS=1

export I_MPI_JOB_ABORT_SIGNAL=15
export I_MPI_JOB_SIGNAL_PROPAGATION=1
export I_MPI_FABRICS=tcp

max_iter=10
for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    (time ibrun /work2/07431/tg867305/stampede2/HPEC2023/HPCCG/test_HPCCG 100 100 64) > $data/hpccg_tl_${SLURM_NTASKS}_"${iter}"_baseline.txt 2>&1
done

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    # ------------------------------------------------------------------------------
    (time LD_PRELOAD=/work2/07431/tg867305/stampede2/HPEC2023/hpec2023/build/libtimelord_wrapper.so ibrun /work2/07431/tg867305/stampede2/HPEC2023/HPCCG/test_HPCCG 100 100 64) > $data/hpccg_tl_${SLURM_NTASKS}_"${iter}"_tl_func.txt 2>&1
done

export I_MPI_WAIT_MODE=0
export I_MPI_THREAD_YIELD=2

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    (time ibrun /work2/07431/tg867305/stampede2/HPEC2023/HPCCG/test_HPCCG 100 100 64) > $data/hpccg_tl_${SLURM_NTASKS}_"${iter}"_yield.txt 2>&1
done

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred/build/libtimelord_wrapper.so ibrun /work2/07431/tg867305/stampede2/HPEC2023/HPCCG/test_HPCCG 100 100 64) > $data/hpccg_tl_${SLURM_NTASKS}_"${iter}"_os_preempt.txt 2>&1
done

for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    (time LD_PRELOAD=/work2/07431/tg867305/stampede2/timelord_pred/build/libtimelord_wrapper.so ibrun /work2/07431/tg867305/stampede2/HPEC2023/gitrepo/timelord-hpccg/test_HPCCG 100 100 64) > $data/hpccg_tl_${SLURM_NTASKS}_"${iter}"_tlp.txt 2>&1
done

