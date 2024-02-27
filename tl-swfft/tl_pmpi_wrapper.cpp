#include "tl_pmpi_wrapper.hpp"
MPI_Comm *idle;

int timelord(MPI_Request *request, int *completed, MPI_Status *status, int file_id, int call_id, int call_type)
{
    struct timespec time_start, time_stop;
    clock_gettime(CLOCK_MONOTONIC, &time_start);
    long unsigned int call_hash = (file_id*10000000) + (call_id *10000) + call_type;
    // std::cout << "Inside Time Lord\n";
    if (predictor_map->find(call_hash) == predictor_map->end()){
        predictor_map->emplace(call_hash, new PREDICTOR());
    }
    // std::cout << "Inside Time Lord 2\n";
    uint32_t sleep_time = predictor_map->at(call_hash)->predict();
    // std::cout << "Sleeping for " << sleep_time << "us\n";
    // std::cout << "Call Type: " << call_type << "\n";
    usleep(sleep_time);

    int r_value = PMPI_Wait(request, status);    
    *completed = 1;

    clock_gettime(CLOCK_MONOTONIC, &time_stop);
    double sync_time = interval(time_start, time_stop);
    // std::cout << "sync_time: " << sync_time << "s\n";
    predictor_map->at(call_hash)->function_called(time_stop);
    predictor_map->at(call_hash)->regress(sync_time);
    // std::cout << "Regressed\n";
    return r_value;
}

double interval(struct timespec start, struct timespec end)
{
  struct timespec temp;
  temp.tv_sec = end.tv_sec - start.tv_sec;
  temp.tv_nsec = end.tv_nsec - start.tv_nsec;
  if (temp.tv_nsec < 0) {
    temp.tv_sec = temp.tv_sec - 1;
   temp.tv_nsec = temp.tv_nsec + 1000000000;
  }
  return (((double)temp.tv_sec) + ((double)temp.tv_nsec)*1.0e-9);
}


/* 
    START OF MPI_COLLECTIVE_ROUTINES
*/

int TL_MPI_Barrier(MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int completed = 0;
    int r_value = MPI_Ibarrier(comm, &request);
    timelord(&request, &completed, &status, file_id, call_id, 1);
    return r_value;
}

int TL_MPI_Wait(MPI_Request *request,MPI_Status *status, int file_id, int call_id ){
    int completed = 0;
    int r_value = timelord(request, &completed, status, file_id, call_id, 1);
    return r_value;
}

// Alltoall

int TL_MPI_Alltoall(const void *sendbuf, int sendcount,
    MPI_Datatype sendtype, void *recvbuf, int recvcount,
    MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Ialltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                         recvtype, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 1);
    return r_value; 
}

int TL_MPI_Alltoallv(const void *sendbuf, const int sendcounts[],
    const int sdispls[], MPI_Datatype sendtype,
    void *recvbuf, const int recvcounts[],
    const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Ialltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf,
                          recvcounts, rdispls, recvtype, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 2);
    return r_value;
}

int TL_MPI_Alltoallw(const void *sendbuf, const int sendcounts[],
    const int sdispls[], const MPI_Datatype sendtypes[],
    void *recvbuf, const int recvcounts[], const int rdispls[],
    const MPI_Datatype recvtypes[], MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf,
                          recvcounts, rdispls, recvtypes, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 3);
    return r_value;
}

int TL_MPI_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[],
    const int sdispls[], MPI_Datatype sendtype,
    void *recvbuf, const int recvcounts[],
    const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Ineighbor_alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf,
                          recvcounts, rdispls, recvtype, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 4);
    return r_value;
}

int TL_MPI_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[],
    const MPI_Aint sdispls[], const MPI_Datatype sendtypes[],
    void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[],
    const MPI_Datatype recvtypes[], MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Ineighbor_alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf,
                          recvcounts, rdispls, recvtypes, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 5);
    return r_value;
}


// Gather

int TL_MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Igather(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                       recvtype, root, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 6);
    return r_value;
}

int TL_MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype,
    int root, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Igatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts,
                        displs, recvtype, root, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 7);
    return r_value;
}


// Allgather
int TL_MPI_Allgather(const void *sendbuf, int  sendcount,
     MPI_Datatype sendtype, void *recvbuf, int recvcount,
     MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Iallgather(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                          recvtype, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 8);
    return r_value;
}

int TL_MPI_Allgatherv(const void *sendbuf, int sendcount,
    MPI_Datatype sendtype, void *recvbuf, const int recvcounts[],
    const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Iallgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts,
                           displs, recvtype, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 9);
    return r_value;
}

int TL_MPI_Neighbor_allgather(const void *sendbuf, int  sendcount,
    MPI_Datatype sendtype, void *recvbuf, int recvcount,
     MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Ineighbor_allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                          recvtype, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 10);
    return r_value;
}

int TL_MPI_Neighbor_allgatherv(const void *sendbuf, int sendcount,
    MPI_Datatype sendtype, void *recvbuf, const int recvcounts[],
    const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Ineighbor_allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts,
                           displs, recvtype, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 11);
    return r_value;

}

// Scatter
int TL_MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Iscatter(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                        recvtype, root, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 12);
    return r_value;
}
int TL_MPI_Scatterv(const void *sendbuf, const int sendcounts[], const int
    displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount,
    MPI_Datatype recvtype, int root, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Iscatterv(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, &request);

    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 13);
    return r_value;
}

// Reduce
int TL_MPI_Reduce(const void *sendbuf, void *recvbuf, int count,
               MPI_Datatype datatype, MPI_Op op, int root,
               MPI_Comm comm, int file_id, int call_id)
{

    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Ireduce(sendbuf, recvbuf, count, datatype, op, root, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 14);
    return r_value;

}

int TL_MPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[],
    MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Ireduce_scatter(sendbuf, recvbuf, recvcounts, datatype, op, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 15);
    return r_value;
}

// Allreduce
int TL_MPI_Allreduce(const void *sendbuf, void *recvbuf, int count,
                  MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Iallreduce(sendbuf, recvbuf, count, datatype, op, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 16);
    return r_value;
}

// Broadcast
int TL_MPI_Bcast(void *buffer, int count, MPI_Datatype datatype,
    int root, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Ibcast(buffer, count, datatype, root, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 17);
    return r_value;
}

// Scan
int TL_MPI_Scan(const void *sendbuf, void *recvbuf, int count,
             MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int file_id, int call_id)
{
    MPI_Request request;
    MPI_Status status;
    int r_value = PMPI_Iscan(sendbuf, recvbuf, count, datatype, op, comm, &request);
    int completed = 0;
    timelord(&request, &completed, &status, file_id, call_id, 18);
    return r_value;
}



/* 
    END OF MPI_COLLECTIVE_ROUTINES
*/