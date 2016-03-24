//
//  main.cpp
//  SP1
//
//  Created by TsengKai Han on 1/21/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include <iostream>
#include <list>
using namespace std;

void print_list(list<int> lst){
    for (list<int>::iterator it = lst.begin(); it != lst.end(); it++) {
        cout<<*it<<" ";
    }
    cout<<endl;
}

template <class T>
list<T> intersect(list<T> l1, list<T> l2){
    list<int>::iterator x1 = l1.begin();
    list<int>::iterator x2 = l2.begin();
    list<T> out;
    while (x1 != l1.end() && x2 != l2.end()) {
        if (*x1 > *x2) {
            x2++;
        }
        else if(*x1 < *x2){
            x1++;
        }
        else{
            out.push_back(*x1);
            x1++;
            x2++;
        }
    }
    return out;
}

template <class T>
list<T> list_union(list<T> l1, list<T> l2){
    list<int>::iterator x1 = l1.begin();
    list<int>::iterator x2 = l2.begin();
    list<T> out;
    
    while (x1 != l1.end() && x2 != l2.end()) {
        if (*x1 > *x2) {
            out.push_back(*x2);
            x2++;
        }
        else if(*x1 < *x2){
            out.push_back(*x1);
            x1++;
        }
        else{
            out.push_back(*x1);
            x1++;
            x2++;
        }
    }
    if (x1 == l1.end()) {
        for (; x2 != l2.end(); x2++) {
            out.push_back(*x2);
        }
    }
    if (x2 == l2.end()) {
        for (; x1 != l1.end(); x1++) {
            out.push_back(*x1);
        }
    }
    return out;
}

template <class T>
list<T> list_diff(list<T> l1, list<T> l2){
    list<int>::iterator x1 = l1.begin();
    list<int>::iterator x2 = l2.begin();
    list<T> out;
    
    while (x1 != l1.end() && x2 != l2.end()) {
        if (*x1 < *x2) {
            out.push_back(*x1);
            x1++;
        }
        else if(*x1 > *x2){
            x2++;
        }
        else{
            x1++;
            x2++;
        }
    }
    if (x1 != l1.end()) {
        for (; x1 != l1.end(); x1++) {
            out.push_back(*x1);
        }
    }
    return out;
}

int main(int argc, const char * argv[]) {
    list<int> l1,l2,out;
    l1.push_back(1);
    l1.push_back(3);
    l1.push_back(5);
    l2.push_back(1);
    l2.push_back(2);
    l2.push_back(3);
    out = intersect(l1, l2);
    print_list(out);
    out = list_union(l1, l2);
    print_list(out);
    out = list_diff(l1, l2);
    print_list(out);
    return 0;
}
