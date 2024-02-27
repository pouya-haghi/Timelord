#include "timelord.h"

int MPI_Init(int *argc, char ***argv)
{
    int ret, rank;
    ret = PMPI_Init(argc, argv); 

    PMPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) printf("Timelord MPI is enabled\n");
    setup_extrawork();;

    return ret;
}

int MPI_Finalize(void)
{
    int ret;
    print_stats();
    ret = PMPI_Finalize();
    return ret;
}

/* 
    START OF MPI_COLLECTIVE_ROUTINES
*/


int MPI_Barrier(MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;

    int ret = PMPI_Ibarrier(comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;

}

int MPI_Wait(MPI_Request *request, MPI_Status *status)
{
    int completed = 0;
    PMPI_Test(request, &completed, status);
    while(!completed){
        do_extrawork();
        PMPI_Test(request, &completed, status);
    }

    return completed ? MPI_SUCCESS : MPI_ERR_PENDING;
}


// Alltoall

int MPI_Alltoall(const void *sendbuf, int sendcount,
    MPI_Datatype sendtype, void *recvbuf, int recvcount,
    MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Ialltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                         recvtype, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret; 
}

int MPI_Alltoallv(const void *sendbuf, const int sendcounts[],
    const int sdispls[], MPI_Datatype sendtype,
    void *recvbuf, const int recvcounts[],
    const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Ialltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf,
                          recvcounts, rdispls, recvtype, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}

int MPI_Alltoallw(const void *sendbuf, const int sendcounts[],
    const int sdispls[], const MPI_Datatype sendtypes[],
    void *recvbuf, const int recvcounts[], const int rdispls[],
    const MPI_Datatype recvtypes[], MPI_Comm comm)

{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf,
                          recvcounts, rdispls, recvtypes, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}

int MPI_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[],
    const int sdispls[], MPI_Datatype sendtype,
    void *recvbuf, const int recvcounts[],
    const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Ineighbor_alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf,
                          recvcounts, rdispls, recvtype, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}

int MPI_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[],
    const MPI_Aint sdispls[], const MPI_Datatype sendtypes[],
    void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[],
    const MPI_Datatype recvtypes[], MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Ineighbor_alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf,
                          recvcounts, rdispls, recvtypes, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}


// Gather

int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Igather(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                       recvtype, root, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}

int MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype,
    int root, MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Igatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts,
                        displs, recvtype, root, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}


// Allgather
int MPI_Allgather(const void *sendbuf, int  sendcount,
     MPI_Datatype sendtype, void *recvbuf, int recvcount,
     MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Iallgather(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                          recvtype, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}

int MPI_Allgatherv(const void *sendbuf, int sendcount,
    MPI_Datatype sendtype, void *recvbuf, const int recvcounts[],
    const int displs[], MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Iallgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts,
                           displs, recvtype, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}

int MPI_Neighbor_allgather(const void *sendbuf, int  sendcount,
    MPI_Datatype sendtype, void *recvbuf, int recvcount,
     MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Ineighbor_allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                          recvtype, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}

int MPI_Neighbor_allgatherv(const void *sendbuf, int sendcount,
    MPI_Datatype sendtype, void *recvbuf, const int recvcounts[],
    const int displs[], MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Ineighbor_allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts,
                           displs, recvtype, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;

}

// Scatter
int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Iscatter(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                        recvtype, root, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}
int MPI_Scatterv(const void *sendbuf, const int sendcounts[], const int
    displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount,
    MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Iscatterv(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, &request);

    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}

// Reduce
int MPI_Reduce(const void *sendbuf, void *recvbuf, int count,
               MPI_Datatype datatype, MPI_Op op, int root,
               MPI_Comm comm)
{

    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Ireduce(sendbuf, recvbuf, count, datatype, op, root, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;

}

int MPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[],
    MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Ireduce_scatter(sendbuf, recvbuf, recvcounts, datatype, op, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}

// Allreduce
int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count,
                  MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Iallreduce(sendbuf, recvbuf, count, datatype, op, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}

// Broadcast
int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype,
    int root, MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Ibcast(buffer, count, datatype, root, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}

// Scan
int MPI_Scan(const void *sendbuf, void *recvbuf, int count,
             MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    MPI_Request request;
    MPI_Status status;
    int ret = PMPI_Iscan(sendbuf, recvbuf, count, datatype, op, comm, &request);
    int completed = 0;
    PMPI_Test(&request, &completed, &status);
    while(!completed){
        do_extrawork();
        PMPI_Test(&request, &completed, &status);
    }
    return ret;
}

/* 
    END OF MPI_COLLECTIVE_ROUTINES
*/
