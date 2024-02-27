#!/bin/bash

# #HPCCG
# sbatch --exclusive /work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/hpccg_run_768.sh
# sbatch --exclusive /work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/hpccg_run_1536.sh
# sbatch --exclusive /work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/hpccg_run_3072.sh

#LAMPPS
sbatch --exclusive /work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/lemp_run_768.sh
# sbatch --exclusive /work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/lemp_run_1536.sh
# sbatch --exclusive /work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/lemp_run_3072.sh

# #Mini AMR
# sbatch --exclusive /work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/mamr_run_768.sh
# sbatch --exclusive /work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/mamr_run_1536.sh
# sbatch --exclusive /work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/mamr_run_3072.sh

# #MiniFE
# sbatch --exclusive /work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/minife_run_768.sh
# sbatch --exclusive /work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/minife_run_1536.sh
# sbatch --exclusive /work2/07431/tg867305/stampede2/HPEC2023/FINAL_RUN/os_preempt/minife_run_3072.sh

# # ./job.sh