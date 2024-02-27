#include <mpi.h>
#include <stdio.h>
#define N 100000

// Your allreduce function
int MPI_Allreduce_custom(const void *sendbuf, void *recvbuf, int count, 
                          MPI_Datatype datatype, MPI_Op op, MPI_Comm comm){
    MPI_Request request;
    int ret = MPI_Iallreduce(sendbuf, recvbuf, count, datatype, op, comm, &request);
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    return ret;
}

int MPI_Alltoall_custom(const void *sendbuf, int sendcount,
    MPI_Datatype sendtype, void *recvbuf, int recvcount,
    MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request;
    int ret = MPI_Ialltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                         recvtype, comm, &request);
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    return ret;
}


// Gather

int MPI_Gather_custom(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm)
{
    MPI_Request request;
    int ret = MPI_Igather(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                       recvtype, root, comm, &request);
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    return ret;
}


// Allgather
int MPI_Allgather_custom(const void *sendbuf, int  sendcount,
     MPI_Datatype sendtype, void *recvbuf, int recvcount,
     MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request;
    int ret = MPI_Iallgather(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                          recvtype, comm, &request);
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    return ret;
}

// Scatter
int MPI_Scatter_custom(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm)
{
    MPI_Request request;
    int ret = MPI_Iscatter(sendbuf, sendcount, sendtype, recvbuf, recvcount,
                        recvtype, root, comm, &request);
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    return ret;
}

// Reduce
int MPI_Reduce_custom(const void *sendbuf, void *recvbuf, int count,
               MPI_Datatype datatype, MPI_Op op, int root,
               MPI_Comm comm)
{

    MPI_Request request;
    int ret = MPI_Ireduce(sendbuf, recvbuf, count, datatype, op, root, comm, &request);
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    return ret;

}



// Broadcast
int MPI_Bcast_custom(void *buffer, int count, MPI_Datatype datatype,
    int root, MPI_Comm comm)
{
    MPI_Request request;
    int ret = PMPI_Ibcast(buffer, count, datatype, root, comm, &request);
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    return ret;
}




void report_time(double start){
    double end = MPI_Wtime();
    printf("Time elapsed: %f seconds\n", end-start);
}

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    
    // Determine the rank of the calling process in the communicator
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Initialize sendbuf
    int sendbuf = rank;

    // Initialize recvbuf. It should be large enough to hold all the data
    // that will be received.
    int recvbuf;

    // Initialize count. This is the number of elements in sendbuf.
    int count = 1;

    // Initialize datatype. In this case, we are sending integers, so 
    // we use MPI_INT.
    MPI_Datatype datatype = MPI_INT;

    // Initialize op. This is the operation that we want to perform. 
    // In this case, we want to sum the values, so we use MPI_SUM.
    MPI_Op op = MPI_SUM;

    // Initialize comm. This is the communicator that includes all the
    // processes. In this case, we use MPI_COMM_WORLD, which includes all
    // the processes in the MPI program.
    MPI_Comm comm = MPI_COMM_WORLD;

    double start_time;

// Allreduce

    start_time = MPI_Wtime();
    for(int i = 0; i < N; i++){
        // original allreduce
        MPI_Allreduce(&sendbuf, &recvbuf, count, datatype, op, comm);
    }
    if ( rank == 0){
    printf("original allreduce: ");
    report_time(start_time); 
    }

    start_time = MPI_Wtime();
    for(int i = 0; i < N; i++){
        // Your custom allreduce 
        MPI_Allreduce_custom(&sendbuf, &recvbuf, count, datatype, op, comm);
    }
    if ( rank == 0){
    printf("new allreduce: ");
    report_time(start_time); 
    }

// Alltoall

    start_time = MPI_Wtime();
    for(int i = 0; i < N; i++){
        // original allreduce
        MPI_Alltoall(&sendbuf, 1, MPI_INT, &recvbuf, 1, datatype, comm);

    }
    if ( rank == 0){
    printf("original alltoall: ");
    report_time(start_time); 
    }

    start_time = MPI_Wtime();
    for(int i = 0; i < N; i++){
        // Your custom allreduce 
        MPI_Alltoall_custom(&sendbuf, 1, MPI_INT, &recvbuf, 1, datatype, comm);

    }
    if ( rank == 0){
    printf("new alltoall: ");
    report_time(start_time); 
    }

// Gather
    start_time = MPI_Wtime();
    for(int i = 0; i < N; i++){
        // original allreduce
        MPI_Gather(&sendbuf, 1, MPI_INT, &recvbuf, 1, datatype, 0, comm);
    }
    if ( rank == 0){
    printf("original gather: ");
    report_time(start_time); 
    }

    start_time = MPI_Wtime();
    for(int i = 0; i < N; i++){
        // Your custom allreduce 
        MPI_Gather_custom(&sendbuf, 1, MPI_INT, &recvbuf, 1, datatype, 0, comm);

    }
    if ( rank == 0){
    printf("new gather: ");
    report_time(start_time); 
    }
// Allgather
    start_time = MPI_Wtime();
    for(int i = 0; i < N; i++){
        // original allreduce
        MPI_Allgather(&sendbuf, 1, datatype, &recvbuf, 1, datatype, comm);

    }
    if ( rank == 0){
    printf("original allgather: ");
    report_time(start_time); 
    }

    start_time = MPI_Wtime();
    for(int i = 0; i < N; i++){
        // Your custom allreduce 
        MPI_Allgather_custom(&sendbuf, 1, datatype, &recvbuf, 1, datatype, comm);
    }
    if ( rank == 0){
    printf("new allgather: ");
    report_time(start_time); 
    }

// Scatter
    start_time = MPI_Wtime();
    for(int i = 0; i < N; i++){
        // original allreduce
        MPI_Scatter(&sendbuf, 1, datatype, &recvbuf, 1, datatype, 0, comm);


    }
    if ( rank == 0){
    printf("original scatter: ");
    report_time(start_time); 
    }

    start_time = MPI_Wtime();
    for(int i = 0; i < N; i++){
        // Your custom allreduce 
        MPI_Scatter_custom(&sendbuf, 1, datatype, &recvbuf, 1, datatype, 0, comm);
    }
    if ( rank == 0){
    printf("new scatter: ");
    report_time(start_time); 
    }

//Reduce
    start_time = MPI_Wtime();
    for(int i = 0; i < N; i++){
        // original allreduce
        MPI_Reduce(&sendbuf, &recvbuf, 1, datatype, op, 0, comm);
    }
    if ( rank == 0){
    printf("original reduce: ");
    report_time(start_time); 
    }

    start_time = MPI_Wtime();
    for(int i = 0; i < N; i++){
        // Your custom allreduce 
        MPI_Reduce_custom(&sendbuf, &recvbuf, 1, datatype, op, 0, comm);
    }
    if ( rank == 0){
    printf("new reduce: ");
    report_time(start_time); 
    }


// bcast
    start_time = MPI_Wtime();
    for(int i = 0; i < N; i++){
        // original allreduce
        MPI_Bcast(&sendbuf, 1, datatype, 0, comm);

    }
    if ( rank == 0){
    printf("original bcast: ");
    report_time(start_time); 
    }

    start_time = MPI_Wtime();
    for(int i = 0; i < N; i++){
        // Your custom allreduce 
        MPI_Bcast_custom(&sendbuf, 1, datatype, 0, comm);
    }
    if ( rank == 0){
    printf("new bcast: ");
    report_time(start_time); 
    }



    MPI_Finalize();
    return 0;
}
