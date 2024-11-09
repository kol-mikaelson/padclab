//
// Created by aero7 on 08-11-2024.
//
#include "iostream"
#include "omp.h"
#include "chrono"
using namespace std;
int calculatesum(int n){
    int sum = 0;
#pragma omp parallel for reduction(+:sum)
    for (int i = 0;i<n;i++){
        sum += i;
    }
    return sum;
}
int main(){
    auto start = chrono::high_resolution_clock::now();
    calculatesum(10000000);
    auto end = chrono::high_resolution_clock::now();
    cout<< (end-start).count()<<endl;
}
