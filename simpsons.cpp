//
// Created by aero7 on 08-11-2024.
//
#include "iostream"
#include "omp.h"
#include "chrono"
const double PI = 3.14159265358979323846;
double f(double x){
    return 4.0/(1+(x*x));
}
double simpsonsrule(int n){
    double h = 1.0/n;
    double sum = f(0) +f(1);
#pragma omp parallel for reduction(+:sum)
    for(int i = 1;i< n;i++){
        double x = i*h;
        if (i%2 == 0){
            sum += 2*f(x);
        }
        else{
            sum += 4*f(x);
        }
    }
    return (h/3)*sum;
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    double pi100 = simpsonsrule(100);
    double pi500 = simpsonsrule(500);
    double pi1000 = simpsonsrule(1000);
    auto end = std::chrono::high_resolution_clock ::now();
    std::cout<< pi100<<std::endl<<pi500<<std::endl<<pi1000<<std::endl;
    std::cout<<(end-start).count();
}
