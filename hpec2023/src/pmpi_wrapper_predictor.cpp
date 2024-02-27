#include "timelord_predictor.h"
#include "iostream"

void timelord(MPI_Request *request, int *completed, MPI_Status *status, int file_id, int call_id, int call_type)
{
    struct timespec time_start, time_stop;
    clock_gettime(CLOCK_REALTIME, &time_start);
    long unsigned int call_hash = (file_id*10000000) + (call_id *10000) + call_type;
    //std::cout << "Inside Time Lord\n";
    if (predictor_map->find(call_hash) == predictor_map->end()){
        predictor_map->emplace(call_hash, new PREDICTOR());
    }
    //std::cout << "Inside Time Lord 2\n";
    int64_t sleep_time = predictor_map->at(call_hash)->predict();
    //std::cout << "Sleeping for " << sleep_time << "us\n";
    //std::cout << "Call Type: " << call_type << "\n";

    tl_do_extrawork(sleep_time);

    PMPI_Wait(request, status);    
    *completed = 1;

    clock_gettime(CLOCK_REALTIME, &time_stop);
    double time_elapsed = interval(time_start, time_stop);
    //std::cout << "Time Elapsed: " << time_elapsed << "us\n";
    predictor_map->at(call_hash)->function_called(time_stop);
    predictor_map->at(call_hash)->regress(time_elapsed);
    //std::cout << "Regressed\n";
    
}

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

int TL_MPI_Barrier(MPI_Comm comm, int file_id, int call_id)
{
    return PMPI_Barrier(comm);
}

// Alltoall

int TL_MPI_Alltoall(const void *sendbuf, int sendcount,
    MPI_Datatype sendtype, void *recvbuf, int recvcount,
    MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Ialltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                         recvtype, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 1);
    return completed; 
}

int TL_MPI_Alltoallv(const void *sendbuf, const int sendcounts[],
    const int sdispls[], MPI_Datatype sendtype,
    void *recvbuf, const int recvcounts[],
    const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Ialltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf,
                          recvcounts, rdispls, recvtype, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 2);
    return completed;
}

int TL_MPI_Alltoallw(const void *sendbuf, const int sendcounts[],
    const int sdispls[], const MPI_Datatype sendtypes[],
    void *recvbuf, const int recvcounts[], const int rdispls[],
    const MPI_Datatype recvtypes[], MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf,
                          recvcounts, rdispls, recvtypes, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 3);
    return completed;
}

int TL_MPI_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[],
    const int sdispls[], MPI_Datatype sendtype,
    void *recvbuf, const int recvcounts[],
    const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Ineighbor_alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf,
                          recvcounts, rdispls, recvtype, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 4);
    return completed;
}

int TL_MPI_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[],
    const MPI_Aint sdispls[], const MPI_Datatype sendtypes[],
    void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[],
    const MPI_Datatype recvtypes[], MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Ineighbor_alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf,
                          recvcounts, rdispls, recvtypes, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 5);
    return completed;
}


// Gather

int TL_MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Igather(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                       recvtype, root, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 6);
    return completed;
}

int TL_MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype,
    int root, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Igatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts,
                        displs, recvtype, root, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 7);
    return completed;
}


// Allgather
int TL_MPI_Allgather(const void *sendbuf, int  sendcount,
     MPI_Datatype sendtype, void *recvbuf, int recvcount,
     MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Iallgather(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                          recvtype, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 8);
    return completed;
}

int TL_MPI_Allgatherv(const void *sendbuf, int sendcount,
    MPI_Datatype sendtype, void *recvbuf, const int recvcounts[],
    const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Iallgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts,
                           displs, recvtype, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 9);
    return completed;
}

int TL_MPI_Neighbor_allgather(const void *sendbuf, int  sendcount,
    MPI_Datatype sendtype, void *recvbuf, int recvcount,
     MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Ineighbor_allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                          recvtype, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 10);
    return completed;
}

int TL_MPI_Neighbor_allgatherv(const void *sendbuf, int sendcount,
    MPI_Datatype sendtype, void *recvbuf, const int recvcounts[],
    const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Ineighbor_allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts,
                           displs, recvtype, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 11);
    return completed;

}

// Scatter
int TL_MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Iscatter(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                        recvtype, root, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 12);
    return completed;
}
int TL_MPI_Scatterv(const void *sendbuf, const int sendcounts[], const int
    displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount,
    MPI_Datatype recvtype, int root, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Iscatterv(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, &request);

    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 13);
    return completed;
}

// Reduce
int TL_MPI_Reduce(const void *sendbuf, void *recvbuf, int count,
               MPI_Datatype datatype, MPI_Op op, int root,
               MPI_Comm comm, int file_id, int call_id)
{

    MPI_Request request;
    MPI_Status status;
    PMPI_Ireduce(sendbuf, recvbuf, count, datatype, op, root, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 14);
    return completed;

}

int TL_MPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[],
    MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Ireduce_scatter(sendbuf, recvbuf, recvcounts, datatype, op, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 15);
    return completed;
}

// Allreduce
int TL_MPI_Allreduce(const void *sendbuf, void *recvbuf, int count,
                  MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Iallreduce(sendbuf, recvbuf, count, datatype, op, comm, &request);
    int completed = 0;
    std::cout << "Call ID: " << call_id << " Running Timelord\n";
    timelord(&request, &completed, &status, file_id, call_id, 16);
    return completed;
}

// Broadcast
int TL_MPI_Bcast(void *buffer, int count, MPI_Datatype datatype,
    int root, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Ibcast(buffer, count, datatype, root, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 17);
    return completed;
}

// Scan
int TL_MPI_Scan(const void *sendbuf, void *recvbuf, int count,
             MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    PMPI_Iscan(sendbuf, recvbuf, count, datatype, op, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 18);
    return completed;
}



/* 
    END OF MPI_COLLECTIVE_ROUTINES
*/
