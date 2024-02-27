#include <mpi.h>
#include "utils.h"


int main(int argc, char** argv) {
    int rank, size;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    double program_start, program_end;
    double iteration_begin[N];
    double iteration_end[N];
    auto deadlines = generatePoissonDeadline(1.0);

    MPI_Barrier(comm);

    long long local, global;

    program_start = MPI_Wtime();

    for(int i = 0 ; i < N ; i++)
    {
        iteration_begin[i] = MPI_Wtime();
        local = 0;
        while((MPI_Wtime() - iteration_begin[i])  < deadlines[i]){
            local++;
        }

        MPI_Allreduce(&local, &global, 1, MPI_LONG_LONG, MPI_SUM, comm);
        iteration_end[i] = MPI_Wtime();
    }

    program_end = MPI_Wtime();

    //=== Statistics ====//
    double *rbuf_begin = NULL;
    double *rbuf_end   = NULL;
    double global_program_start, global_program_end;
    if ( rank == 0 ) {
        rbuf_begin = (double*)malloc(sizeof(double) * N * size);
        rbuf_end = (double*)malloc(sizeof(double) * N * size);
    }
    // program execution time
    MPI_Reduce(&program_start, &global_program_start, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
    MPI_Reduce(&program_end,   &global_program_end, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
    // iteration execution time
    MPI_Gather(iteration_begin, N, MPI_DOUBLE, rbuf_begin,   N, MPI_DOUBLE, 0, comm);
    MPI_Gather(iteration_end,   N, MPI_DOUBLE, rbuf_end,   N, MPI_DOUBLE, 0, comm);

    MPI_Barrier(comm);

    if(rank == 0 )
    {
        double execution_time = global_program_end - global_program_start;
        printf("%.9f", execution_time);
        printf(" seconds\n");

    }


    MPI_Finalize();

    return 0;
}