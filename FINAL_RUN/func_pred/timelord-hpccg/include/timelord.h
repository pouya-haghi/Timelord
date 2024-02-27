#ifndef TIMELORD_H
#define TIMELORD_H

#include <mpi.h>
#include "unordered_map"
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>




#define DELTA 500



double interval(struct timespec start, struct timespec end);

class PREDICTOR {
    private:
    double slope, intercept, dx, dy, mu_x, mu_y, var_x, cov_xy, n, last_call_time;

    public:
    struct timespec call_time;
    PREDICTOR(): slope(0), intercept(0), dx(0), dy(0), mu_x(0), mu_y(0), var_x(0), cov_xy(0), n(0), last_call_time(0){};
    void regress(double sync_time){
        if(last_call_time > 0){
            sync_time = sync_time * 1000.0;
            n += 1;
            dx = last_call_time - mu_x;
            dy = sync_time - mu_y;
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
        double out = ((double)((slope * last_call_time + intercept) - (1.96 * cov_xy))*1000.0);
        out = out < DELTA ? 0 : out - DELTA;
        // std::cout << "Predicted sleep time: " << out << "s\n";
        // std::cout << "Work time: " << last_call_time << "s\n";
        // std::cout << "N: " << n << "\n";
        //std::cout << "Intercept: " << intercept << "\n";
        //std::cout << "Slope: " << slope << "\n";
        // std::cout << "Cov_xy: " << cov_xy << "\n";
        return out;
    }

    void function_called(struct timespec time_now){     
        
        if(call_time.tv_sec == 0){
            call_time = time_now;       
            return;
        }
        last_call_time = interval(call_time, time_now);
        call_time = time_now;
    }
};

static std::unordered_map<long unsigned int, PREDICTOR*> *predictor_map = new std::unordered_map<long unsigned int, PREDICTOR*>;



#endif
