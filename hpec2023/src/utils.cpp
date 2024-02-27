#include "utils.h"

vector<double> generatePoissonDeadline(double avg)
{
    mt19937 gen(0); //fixed seed 
    vector<double> deadline;

    // generate deadline following poisson distribution
    double lambda = 1 / avg;
    exponential_distribution<double> exp(lambda);
    for(size_t i = 0 ; i < N ; i++) {
        deadline.push_back(exp(gen));
    }

    return deadline;


}