#ifndef TIMELORD_H
#define TIMELORD_H

#include <mpi.h>
unsigned long long count_work;
//static unsigned int seed;
//const unsigned int a = 1103515245;  // Multiplier
//const unsigned int c = 12345;  // Increment
//const unsigned int m = 2147483648;  // Modulus


void print_stats()
{
    int rank;
    unsigned long long total_extrawork_done;


    PMPI_Comm_rank(MPI_COMM_WORLD, &rank);
    PMPI_Allreduce(&count_work, &total_extrawork_done, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

    if(rank == 0)
    {
        printf("Total extrawork done: %lld\n", total_extrawork_done);
    }

}

inline void setup_extrawork()
{
    //seed = 123;
    count_work = 0;
}
inline void do_extrawork()
{
    //seed = (a * seed + c) % m;
    count_work++;
}


#endif
