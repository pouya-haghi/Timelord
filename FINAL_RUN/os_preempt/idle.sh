#!/bin/bash
#exclusive
#SBATCH -J lemps16
#SBATCH -o lemps16.o%j
#SBATCH -e lemps16.e%j
#SBATCH -A TG-PEB220004
#SBATCH -p skx-normal
#SBATCH -N 16
#SBATCH --ntasks-per-node=48
#SBATCH -t 00:04:00


# module load gcc/7.1.0
# module load mkl/18.0.2

data="/work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/timelord_results"
export OMP_NUM_THREADS=1

export I_MPI_JOB_ABORT_SIGNAL=15
export I_MPI_JOB_SIGNAL_PROPAGATION=1
export I_MPI_FABRICS=tcp

(time ibrun /work2/07431/tg867305/stampede2/timelord_pred/build/idle) > $data/idle_tl_1_${SLURM_NTASKS}_2.txt 2>&1


