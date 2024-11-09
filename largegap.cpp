//
// Created by aero7 on 09-11-2024.
//
#include "iostream"
#include "omp.h"
#include "chrono"
#include "vector"
using namespace std;
bool isprime(int n){
    if (n == 1){
        return false;
    }
    if (n<=3){
        return true;
    }
    if (n%2 == 0 || n% 3 == 0){
        return false;
    }
    for (int i = 5;i*i<n;i+=6){
        if (n%i == 0 || n%(i+2) == 0){
            return false;
        }

    }
    return true;
}

vector<int> find_prime(int n){
    vector<int> primes;
    for (int i = 1; i< n;i++){
        if (isprime(i)){
            primes.push_back(i);
        }
    }
    return primes;
}

int findgap(vector<int> primes){
    int max_gap = 0;
    int pos=0;
    for (int x = 1;x<primes.size();x++){
        int gap = primes[x] - primes[x-1];
        if (gap > max_gap){
            max_gap = gap;
            pos = x;
        }
    }
    cout << "Max gap is " << max_gap << " between " << primes[pos-1] << " and " << primes[pos] << endl;
}

int main(){
    vector<int> primes = find_prime(1000000);
    auto start = chrono::high_resolution_clock::now();
    findgap(primes);
    auto end = chrono::high_resolution_clock::now();
    cout<<"Time taken" << (end-start).count()<<endl;
}
