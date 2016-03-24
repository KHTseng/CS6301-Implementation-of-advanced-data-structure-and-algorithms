//
//  c.cpp
//  SP3
//
//  Created by TsengKai Han on 2/18/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;
////quicksort
void quickSort(vector<int> &arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(rand()%(right - left + 1)) + left];
    
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    };
    
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}
////merge
void merge(vector<int> &arr, int left, int mid, int right){
    int i = left, j = mid+1;
    vector<int> copy;
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {//i < j
            copy.push_back(arr[i]);
            i++;
        }
        else{//j < i
            copy.push_back(arr[j]);
            j++;
        }
    }
    if (i == mid+1) {//i is end
        for (; j <= right; j++) {
            copy.push_back(arr[j]);
        }
    }
    else if (j == right+1) {//j is end
        for (; i <= mid; i++) {
            copy.push_back(arr[i]);
        }
    }
    ////copy to arr
    for (int i = 0; i < copy.size(); i++) {
        arr[left + i] = copy[i];
    }
}

////mergesort
void mergesort(vector<int> &arr, int left, int right){
    int mid;
    if (left < right)
    {
        mid=(left+right)/2;
        mergesort(arr,left,mid);
        mergesort(arr,mid+1,right);
        merge(arr,left, mid, right);
    }
    return;
}

////main
int main(){
    clock_t timer;
    vector<int> arr;
    //srand(time(NULL));
    ////create array
    int p = 1048576;//array size
    for (int i = 0; i < p; i++) {
        arr.push_back(rand()%100);
    }
    /*cout<<"Ordinary array: ";
     for (int i = 0; i < arr.size(); i++) {
     cout<<arr[i]<<" ";
     }*/
    cout<<endl;
    vector<int> arr1 = arr;
    
    ////quicksort
    timer = clock();
    quickSort(arr, 0, int(arr.size())-1);
    cout<<"Quicksort time cost: "<<clock() - timer<<" ms"<<endl;
    /*cout<<"sorted: ";
     for (int i = 0; i < arr.size(); i++) {
     cout<<arr[i]<<" ";
     }
    cout<<endl;*/
    
    ////mergesort
    timer = clock();
    mergesort(arr1, 0, int(arr1.size())-1);
    cout<<"Mergesort time cost: "<<clock() - timer<<" ms"<<endl;
    /*cout<<"sorted: ";
     for (int i = 0; i < arr1.size(); i++) {
     cout<<arr1[i]<<" ";
     }
    cout<<endl;*/

    return 0;
}
/* 
 sample input: 1048576 random number range form 0 to 99
 output: 
 Quicksort time cost: 168055 ms
 Mergesort time cost: 2027604 ms
*/