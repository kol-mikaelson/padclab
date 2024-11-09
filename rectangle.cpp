//
// Created by aero7 on 08-11-2024.
//
#include "iostream"
#include "omp.h"
#include "chrono"
using namespace std;
const double steps = 1000;
const double PI = 3.14159265358979323846;

double calculate_pi() {
    double sum = 0.0;
    double step = 1.0 / steps;

#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < (int)steps; ++i) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    return step * sum;
}

void print_results(double result,long long duration){
    cout<<"estimated value of pi is "<< result << endl;
    cout << "Time taken" << duration << endl;
}

int main(){
    cout<<"Actual value of pi is "<< PI << endl;
    auto start = chrono::high_resolution_clock::now();
    double result = calculate_pi();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = stop - start;
    print_results(result, duration.count());
}
