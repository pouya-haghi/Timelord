#include "timelord.h"

int timelord(MPI_Request *request, int *completed, MPI_Status *status, int file_id, int call_id, int call_type);


/* 
    START OF MPI_COLLECTIVE_ROUTINES
*/

int TL_MPI_Barrier(MPI_Comm comm, int file_id, int call_id);

int TL_MPI_Wait(MPI_Request *request,MPI_Status *status, int file_id, int call_id );

// Alltoall

int TL_MPI_Alltoall(const void *sendbuf, int sendcount,
    MPI_Datatype sendtype, void *recvbuf, int recvcount,
    MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id);

int TL_MPI_Alltoallv(const void *sendbuf, const int sendcounts[],
    const int sdispls[], MPI_Datatype sendtype,
    void *recvbuf, const int recvcounts[],
    const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id);

int TL_MPI_Alltoallw(const void *sendbuf, const int sendcounts[],
    const int sdispls[], const MPI_Datatype sendtypes[],
    void *recvbuf, const int recvcounts[], const int rdispls[],
    const MPI_Datatype recvtypes[], MPI_Comm comm, int file_id, int call_id);

int TL_MPI_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[],
    const int sdispls[], MPI_Datatype sendtype,
    void *recvbuf, const int recvcounts[],
    const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id);

int TL_MPI_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[],
    const MPI_Aint sdispls[], const MPI_Datatype sendtypes[],
    void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[],
    const MPI_Datatype recvtypes[], MPI_Comm comm, int file_id, int call_id);


// Gather

int TL_MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm, int file_id, int call_id);

int TL_MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype,
    int root, MPI_Comm comm, int file_id, int call_id);


// Allgather
int TL_MPI_Allgather(const void *sendbuf, int  sendcount,
     MPI_Datatype sendtype, void *recvbuf, int recvcount,
     MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id);

int TL_MPI_Allgatherv(const void *sendbuf, int sendcount,
    MPI_Datatype sendtype, void *recvbuf, const int recvcounts[],
    const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id);

int TL_MPI_Neighbor_allgather(const void *sendbuf, int  sendcount,
    MPI_Datatype sendtype, void *recvbuf, int recvcount,
     MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id);

int TL_MPI_Neighbor_allgatherv(const void *sendbuf, int sendcount,
    MPI_Datatype sendtype, void *recvbuf, const int recvcounts[],
    const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int file_id, int call_id);

// Scatter
int TL_MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm, int file_id, int call_id);

int TL_MPI_Scatterv(const void *sendbuf, const int sendcounts[], const int
    displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount,
    MPI_Datatype recvtype, int root, MPI_Comm comm, int file_id, int call_id);

// Reduce
int TL_MPI_Reduce(const void *sendbuf, void *recvbuf, int count,
               MPI_Datatype datatype, MPI_Op op, int root,
               MPI_Comm comm, int file_id, int call_id);

int TL_MPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[],
    MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int file_id, int call_id);

// Allreduce
int TL_MPI_Allreduce(const void *sendbuf, void *recvbuf, int count,
                  MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int file_id, int call_id);


// Broadcast
int TL_MPI_Bcast(void *buffer, int count, MPI_Datatype datatype,
    int root, MPI_Comm comm, int file_id, int call_id);

// Scan
int TL_MPI_Scan(const void *sendbuf, void *recvbuf, int count,
             MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int file_id, int call_id);



/* 
    END OF MPI_COLLECTIVE_ROUTINES
*/