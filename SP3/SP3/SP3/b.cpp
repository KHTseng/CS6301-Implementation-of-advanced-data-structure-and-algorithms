//
//  b.cpp
//  SP3
//
//  Created by TsengKai Han on 2/16/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

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
////multi pivot
void quickSort_multi(vector<int> &arr, int left, int right){
    srand(time(NULL));
    int p = (rand()%(right - left + 1)) + left;
    int p1 = arr[p];//small
    int r = (rand()%(right - left + 1)) + left;
    while (r == p) {
        r = (rand()%(right - left + 1)) + left;
    }
    int p2 = arr[r];//big
    if (p1 > p2) {//if small > big
        swap(p1, p2);
        swap(p, r);
    }
    if (right - left == 1) {// array only have two element
        if (p > r) {//sort two element
            swap(arr[p], arr[r]);
        }
        return;
    }
    ////move two pivot to front and end (specital event with pivot is at front or end already)
    if (r == left && p == right) {
        swap(arr[p], arr[r]);
    }
    else if (r == left){
        swap(arr[right], arr[r]);
        swap(arr[left], arr[p]);
    }
    else{
        swap(arr[left], arr[p]);
        swap(arr[right], arr[r]);
    }
    int i = left + 1, j = right - 1, l = left + 1;
    ////partition
    while (j >= i) {
        if (p1 <= arr[i] && p2 >= arr[i]) {//case 1
            i++;
        }
        else if(p1 > arr[i]){//case 2
            swap(arr[i], arr[l]);
            l++;
            i++;
        }
        else if (arr[j] > p2){//case 3
            j--;
        }
        else if (arr[i] > p2 && arr[j] <p1){//case 4
            swap(arr[i], arr[j]);
            swap(arr[i], arr[l]);
            l++;
            i++;
            j--;
        }
        else if(arr[i] > p2 && arr[j] >= p1 && arr[j] <= p2){//case 5
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    ////swap pivot back to their postion
    swap(arr[left], arr[l-1]);
    swap(arr[j+1], arr[right]);
    ////recursive
    if (left < l-2) {
        quickSort_multi(arr, left, l-2);
    }
    if(p1 != p2 && l < j){
        quickSort_multi(arr, l, j);
    }
    if (j+2 < right) {
        quickSort_multi(arr, j+2, right);
    }
}

int main(int argc, const char * argv[]) {
    clock_t timer;
    vector<int> arr;
    srand(time(NULL));
    ////create input
    for (int i = 0; i < 30000; i++) {
        arr.push_back(rand()%10);
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
    cout<<"One pivot time cost: "<<clock() - timer<<" ms"<<endl;
    /*cout<<"sorted array: ";
    for (int i = 0; i < arr.size(); i++) {
        cout<<arr[i]<<" ";
    }*/
    cout<<endl;
    
    ////quicksort with multi pivot
    timer = clock();
    quickSort_multi(arr1, 0, int(arr1.size())-1);
    cout<<"Two pivot time cost: "<<clock() - timer<<" ms"<<endl;
    /*cout<<"sorted with two pivot: ";
    for (int i = 0; i < arr1.size(); i++) {
        cout<<arr1[i]<<" ";
    }*/
    cout<<endl;
    
    return 0;
}
/*
 sample input: random 3000 number range 0 to 10
 output:
 One pivot time cost: 3950 ms
 Two pivot time cost: 1969 ms

*/