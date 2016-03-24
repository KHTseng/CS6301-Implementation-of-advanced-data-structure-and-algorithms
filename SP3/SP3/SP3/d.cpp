//
//  d.cpp
//  SP3
//
//  Created by TsengKai Han on 2/18/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <time.h>

using namespace std;

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
    if (right - j >= k) {// k is int the bigger
        return select(arr, j+1, right, k);
    }
    else if (right - j + 1 == k){//pivot is k
        return j;
    }
    else{
        return select(arr, left, j-1, k - (right - j + 1));
    }
}
////comparator
struct comparator {
    bool operator()(int i, int j) {
        return i > j;
    }
};
////heap-select
int select_heap(vector<int> &arr, int k){
    priority_queue<int, std::vector<int>, comparator> minHeap;
    for (int i = 0; i < k; i++) {//put k element
        minHeap.push(arr[i]);
    }
    for (int i = k; i < arr.size(); i++) {//compare new element and change
        if (minHeap.top() < arr[i]) {//new one is bigger
            minHeap.pop();
            minHeap.push(arr[i]);
        }
    }
    ////copy to arr
    for (int i = 0; i < k; i++) {
        arr[arr.size() - k + i] = minHeap.top();
        minHeap.pop();
    }
    return arr.size() - k;
}

int main(){
    clock_t timer;
    vector<int> arr;
    srand(time(NULL));
    ////create array
    for (int i = 0; i < 10000000; i++) {
        arr.push_back(rand());
    }
    vector<int> arr1 = arr;
    ////selection
    int k = 1000;
    timer = clock();
    int index = select(arr, 0, int(arr.size()) - 1, k);
    int t = clock() - timer;
    cout<<"index from: "<<index<<endl;
    cout<<"cost time is: "<<t<<endl;
    /*cout<<k<<"biggest element is: ";
    for (int i = index; i < arr.size(); i++) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;*/
    ////selection 2
    timer = clock();
    index = select_heap(arr1, k);
    t = clock() - timer;
    cout<<"index from: "<<index<<endl;
    cout<<"cost time is: "<<t<<endl;
    /*cout<<k<<"biggest element is: ";
    for (int i = index; i < arr1.size(); i++) {
        cout<<arr1[i]<<" ";
    }
    cout<<endl;*/
    return 0;
}
/*
 sample input: 10000000 random number, k = 1000
 output:
 generic versions: cost time is 286456
 heap versions: cost time is 68039
*/