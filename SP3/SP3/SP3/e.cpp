//
//  e.cpp
//  SP3
//
//  Created by TsengKai Han on 2/19/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

////select kth biggest element's index
int select(vector<int> &arr, int left, int right, int k){
    int i = left+1, j = right;
    int pivot = (rand()%(right - left + 1)) + left;
    swap(arr[left], arr[pivot]);//move pivot to the left
    ////partition
    while (i <= j) {
        while (arr[i] < arr[left])
            i++;
        while (arr[j] > arr[left])
            j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    swap(arr[left], arr[j]);//swap pivot and biggest of smaller
    ////recursive
    if (right - j >= k) {// k is in the bigger
        return select(arr, j+1, right, k);
    }
    else if (right - j + 1 == k){//pivot is k
        return j;
    }
    else{
        return select(arr, left, j-1, k - (right - j + 1));
    }
}
////take a part
void part(vector<int> A, int x){
    int i = 0;
    int j = int(A.size())-1;
    while (j>i) {
        if (A[i]<=x) {
            i++;
        }
        else if (A[j] > x){
            j--;
        }
        else{
            swap(A[i], A[j]);
            i++;
            j--;
        }
    }
}
////kthQuantiles
void kthQuantiles(vector<int> A, vector<int> *result, int k){
    if (k == 1) {
        return;
    }
    else{
        int n = int(A.size());
        int i = k/2;//half k(mid)
        int x = A[select(A, 0, int(A.size())-1, n - (i*n/k) + 1)];//find mid val in A
        part(A, x);//partition A by x
        vector<int>::iterator mid = A.begin();
        advance(mid, i*n/k);//iterator of mid
        vector<int> left(A.begin(), mid);//left = begin ~ k/2
        vector<int> right(mid, A.end());//left = begin ~ k/2
        kthQuantiles(left, result, k/2);
        result->push_back(x);//value
        kthQuantiles(right, result, ceil(k/2));
    }
}

int main(){
    ////create array
    vector<int> A;
    vector<int> result;
    for (int i = 0; i < 8; i++) {
        A.push_back(8 - i);
    }
    ////kth
    kthQuantiles(A, &result, 4);
    ////output
    for (int i = 0; i<result.size(); i++) {
        cout<<result[i]<<" ";
    }
    cout<<endl;
    return 0;
}
/*
 sample input: 8 7 6 5 4 3 2 1 
 k = 4
 
 output: 2 4 6
 */
 

