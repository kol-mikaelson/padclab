//
// Created by aero7 on 08-11-2024.
//
#include "iostream"
#include "chrono"
#include "omp.h"
using namespace std;
bool inside(double x,double y){
    if ((x*x + y*y) <=1){
        return true;
    } else return false;
}
int main(){
    double total = 10000000;
    double coun = 0;
    double randx,randy;
    auto start = chrono::high_resolution_clock::now();
    for (int i =0; i< total;++i){
        randx = static_cast<double>(rand())/RAND_MAX;
        randy = static_cast<double>(rand())/RAND_MAX;
        if (randx < 0){
            randx *= -1;
        }
        if (randy < 0){
            randy *= -1;
        }
        if (inside(randx,randy)){
            ++coun;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    double pi_est = 4.0* (coun/total);
    cout << pi_est << endl;
    cout<<(end-start).count() << endl;
}
