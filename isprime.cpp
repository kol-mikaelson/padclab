//
// Created by aero7 on 08-11-2024.
//
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

int main(){
    int N = 200;
    int count = 0;
    for (int i = 0;i<N;i++){
        if (isprime(i) and isprime(i+2)){
            count+= 1;
        }
    }
}
