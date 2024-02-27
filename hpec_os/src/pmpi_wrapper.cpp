#include "timelord.h"
#include "iostream"
#include <sstream>
#include <unistd.h> 
#include <signal.h>
#include <cstdlib>

int *pid;
MPI_Comm *idle;
int MPI_Init(int *argc, char ***argv)
{
    int ret, rank, size;
    ret = PMPI_Init(argc, argv); 

    PMPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    MPI_Comm parentComm;
    MPI_Comm_get_parent(&parentComm);

    pid = new int(getpid());

    if ((rank == 0) and (parentComm == MPI_COMM_NULL)){ 
        printf("Timelord MPI is enabled\n");
        idle = new MPI_Comm;
        PMPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_spawn("./idle", MPI_ARGV_NULL, size, MPI_INFO_NULL, 0, MPI_COMM_SELF, idle, MPI_ERRCODES_IGNORE); 
    }
    
    setup_extrawork();;

    return ret;
}

int MPI_Finalize(void)
{
    int ret, rank;
    PMPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm parentComm;
    MPI_Comm_get_parent(&parentComm);
//    print_stats();
    
    int first;//second;
    if (parentComm == MPI_COMM_NULL){
        first = kill(getppid(), SIGINT);
    }
    ret = PMPI_Finalize();
    //MPI_Abort(*idle ,1);
    //second = kill(*pid, SIGINT);
    return ret;
}
