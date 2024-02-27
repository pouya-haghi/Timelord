#include <sched.h>
#include <omp.h>
#include "iostream"
#include <csignal>
#include <unistd.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include <mpi.h>

//Iteration counts
unsigned long long int iterations = 0;

//Function to handle the termination signal
void signalHandler(int signal) {
    
    //std::cout << "\nMy Iterations: "<< iterations << std::endl;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    unsigned long long int sum = 0;      // Variable to store the sum
    // std::cout << "\nReceived termination signal" << std::endl;
    MPI_Allreduce(&iterations, &sum, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);
    if(rank == 0)
        printf("Total extrawork done: %lld\n", sum);
    sleep(1);
    MPI_Finalize();
    //MPI_Abort(MPI_COMM_WORLD, 2);
    exit(1);
}


int main(int argc, char* argv[]) {

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Install signal handler
    std::signal(SIGTERM, signalHandler);
    std::signal(SIGINT, signalHandler);


    pid_t pid = getpid(); // Get the process ID of the current process

    int result;
    struct sched_param params;
    params.sched_priority = 0; // Unused for SCHED_IDLE

    //Change the scheduling
    result = sched_setscheduler(pid, SCHED_IDLE, &params);
    if (result == -1)
    {
        std::cout << "Failed to set scheduling policy. Error: " << errno << std::endl;
        return 1;
    }
    
    //Begin extra work
    while(true) {
        iterations++;
    }

    return 0;
}
