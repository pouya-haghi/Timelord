#ifndef TIMELORD_H
#define TIMELORD_H

#include <mpi.h>
#include "unordered_map"
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>


long long count_work;


MPI_Comm *idle;

double interval(struct timespec start, struct timespec end);

class PREDICTOR {
    private:
    double slope, intercept, dx, dy, mu_x, mu_y, var_x, cov_xy, n, last_call_time;

    public:
    struct timespec call_time;
    PREDICTOR(): slope(0), intercept(0), dx(0), dy(0), mu_x(0), mu_y(0), var_x(0), cov_xy(0), n(0), last_call_time(0){};
    void regress(double laggard_time){
        if(last_call_time > 0){
            n += 1;
            dx = last_call_time - mu_x;
            dy = laggard_time - mu_y;
            var_x  += (((n-1)/n)* dx*dx - var_x ) /n;
            cov_xy += (((n-1)/n)* dx*dy - cov_xy) /n;
            mu_x += (dx / n);
            mu_y += (dy / n);
            if(var_x > 0){
                slope = cov_xy / var_x;
                intercept = mu_y - slope * mu_x;
            }else{
                slope = 0;
                intercept = 0;
            }
        }
    }

    uint32_t predict(){
        int64_t out = ((slope * last_call_time + intercept) - (1.96 * cov_xy));
        out = out < 0 ? 0 : out;
        std::cout << "Predicted sleep time: " << out << "us\n";
        std::cout << "Work time: " << last_call_time << "us\n";
        std::cout << "N: " << n << "\n";
        std::cout << "Intercept: " << intercept << "\n";
        std::cout << "Slope: " << slope << "\n";
        std::cout << "Cov_xy: " << cov_xy << "\n";
        return out;
    }

    void function_called(struct timespec time_now){     
        
        if(call_time.tv_sec == 0){
            call_time = time_now;       
            return;
        }
        last_call_time = interval(time_now, call_time);
        call_time = time_now;
    }
};

static std::unordered_map<long unsigned int, PREDICTOR*> *predictor_map = new std::unordered_map<long unsigned int, PREDICTOR*>;

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
    count_work = 0;
}
inline void tl_do_extrawork(int64_t x)
{
    printf("TIME %ld\n", x);
    count_work++;
}

#endif
