//
//  main.cpp
//  SP1_b
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

list<int> add(list<int> l1, list<int>l2, int b){
    list<int>::iterator x1 = l1.begin();
    list<int>::iterator x2 = l2.begin();
    list<int> out;
    int next = 0; //record overflow
    int n = int(l1.size() - l2.size());
    //// make them the same size
    if (n > 0) {
        for (; n > 0; n--) {
            l2.push_back(0);
        }
    }
    else if(n < 0){
        for (; n < 0; n++) {
            l1.push_back(0);
        }
    }
    ////sum
    while (x1 != l1.end() && x2 != l2.end()) {
        if (*x1 + *x2 + next < b) {
            out.push_back(*x1 + *x2 + next);
            next = 0;
        }
        else{
            out.push_back((*x1 + *x2 + next)%b);
            next = 1;
        }
        x1++;
        x2++;
    }
    if (next == 1) {
        out.push_back(1);
    }
    return out;
};

list<int> subtract(list<int> l1, list<int>l2, int b){
    list<int>::iterator x1 = l1.begin();
    list<int>::iterator x2 = l2.begin();
    list<int> out;
    int next = 0; //record overflow
    int n = int(l1.size() - l2.size());
    //// make them the same size
    if (n > 0) {
        for (; n > 0; n--) {
            l2.push_back(0);
        }
    }
    else if(n < 0){
        for (; n < 0; n++) {
            l1.push_back(0);
        }
    }
    ////sub
    while (x1 != l1.end() && x2 != l2.end()) {
        if (*x1 - *x2 + next >= 0) {
            out.push_back(*x1 - *x2 + next);
            next = 0;
        }
        else{
            out.push_back((*x1 - *x2 + next)+b);
            next = -1;
        }
        x1++;
        x2++;
    }
    return out;
}

int main(int argc, const char * argv[]) {
    list<int> l1, l2, out;
    l1.push_back(9);
    l1.push_back(3);
    l1.push_back(5);
    l2.push_back(0);
    l2.push_back(3);
    l2.push_back(5);
    out = add(l1, l2, 10);
    print_list(out);
    out = subtract(l1, l2, 10);
    print_list(out);
    return 0;
}
