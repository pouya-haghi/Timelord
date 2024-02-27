#!/bin/bash

#SBATCH -J akslmp
#SBATCH -o akshaya.o%j
#SBATCH -e akshaya.e%j
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
# export PSM2_SHAREDCONTEXTS=YES
# export PSM2_RANKS_PER_CONTEXT=2
# export PSM2_DEVICES="self,shm,hfi"


max_iter=3
for ((iter=1; iter<=$max_iter; iter=iter+1))
do
    # (time ibrun /work2/07431/tg867305/stampede2/HPEC2023/gitrepo-fair/timelord-hpccg/test_HPCCG 100 100 64) > $data/hpccg_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
    # (time ibrun /work2/07431/tg867305/stampede2/HPEC2023/gitrepo-fair/timelord-lammps/build/lmp -in /work2/07431/tg867305/stampede2/HPEC2023/gitrepo/timelord-lammps/bench/in.lj) > $data/lammps_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
    # (time ibrun /work2/07431/tg867305/stampede2/HPEC2023/gitrepo-fair/timelord-minife/src/miniFE.x -nx 1024 -ny 512 -nz 192) > $data/minife_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
    (time ibrun /work2/07431/tg867305/stampede2/HPEC2023/gitrepo-fair/timelord-miniamr/miniAMR.x --npx 16 --npy 8 --npz 6) > $data/miniamr_tl_${SLURM_NTASKS}_"${iter}".txt 2>&1
done
