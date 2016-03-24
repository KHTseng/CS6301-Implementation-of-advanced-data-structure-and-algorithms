//
//  main.cpp
//  SP3
//
//  Created by TsengKai Han on 2/16/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

long linearFibonacci(long n, long p){
    long n1 = 1;
    if (n == 1 || n == 2) {//first number
        return  n1;
    }
    long n2 = 1;
    for (int i  = 3; i <= n; i++) {
        n1 = n1 + n2;
        n1 = n1%p;
        swap(n1, n2);
    }
    return n2;
}
vector<long> powerOfArray(long n, long p){
    ////construct element array
    vector<long> n1(3,1);   // | 1 1 |
    n1.push_back(0);        // | 1 0 |
    
    if (n == 1) {
        return n1;
    }
    else{
        vector<long> half = powerOfArray(n/2, p);
        vector<long> result;
        ////result = half * half
        result.push_back((half[0]*half[0] + half[1]*half[2])%p);//first element
        result.push_back((half[0]*half[1] + half[1]*half[3])%p);//second element
        result.push_back((half[0]*half[2] + half[2]*half[3])%p);//third element
        result.push_back((half[1]*half[2] + half[3]*half[3])%p);//fourth element
        if (n%2 == 1) {//n is odd
            vector<long> result1;
            result1.push_back((result[0] + result[1])%p);
            result1.push_back(result[0]);
            result1.push_back((result[2] + result[3])%p);
            result1.push_back(result[2]);
            return result1;
        }
        return  result;
    }
}
long logFibonacci(long n, long p){
    return powerOfArray(n-1, p)[0];
}


int main(int argc, const char * argv[]) {
    clock_t timer;
    timer = clock();
    int p = 999953;
    cout<<linearFibonacci(100000, p)<<endl;
    cout<<"time cost: "<<clock() - timer<<" ms"<<endl;
    timer = clock();
    cout<<logFibonacci(100000, p)<<endl;
    cout<<"time cost: "<<clock() - timer<<" ms"<<endl;
    
    return 0;
}
/*
 sample input: 100000th Fibonacci number, p = 999953
 output: 961125
 timecost:  linear: 2435 ms
            log: 171ms
*/