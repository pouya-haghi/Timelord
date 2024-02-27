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

    // std::string filename = "output_" + std::to_string(getpid()) + ".txt";
    std::cout << "\nMy Iterations: "<< iterations << std::endl;

    unsigned long long int sum = 0;      // Variable to store the sum
    // std::cout << "\nReceived termination signal" << std::endl;
    MPI_Allreduce(&iterations, &sum, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);
    MPI_Finalize();
    std::cout << "Total Iterations: " << std::scientific << std::setprecision(8) << sum << std::endl;
    // std::ofstream file(filename);
    // if (file.is_open()) {
    //     file << "Total Iterations: " << sum << std::endl;

    //     file.close(); // Close the file
    // }
    // else {
    //     std::cout << "Failed to open the file." << std::endl;
    // }
    exit(0);
    
}


void myErrorHandler(MPI_Comm* comm, int* errcode, ...) {
    // int rank;
    // MPI_Comm_rank(*comm, &rank);
    std::cout << "Error handled\n";
}

int main(int argc, char* argv[]) {

    int rank, size;
    std::cout << "Starting MPI with PID: " << getpid() <<  std::endl;

    MPI_Init(&argc, &argv);
    std::cout << "EW Init " <<   std::endl;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Errhandler errhandler;
    MPI_Comm_create_errhandler(myErrorHandler, &errhandler);
    MPI_Comm_set_errhandler(comm, errhandler);
    
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
    
    std::cout << "Started Calcs" << std::endl;
    //Begin extra work
    while(true) {
        iterations++;
    }

    return 0;
}
