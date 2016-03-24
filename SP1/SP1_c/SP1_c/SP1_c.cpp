//
//  main.cpp
//  SP1_c
//
//  Created by TsengKai Han on 1/22/16.
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

list<int> merge(list<int> l1, list<int> l2){
    list<int>::iterator it1 = l1.begin();
    list<int>::iterator it2 = l2.begin();
    list<int> out;
    while (1) {
        if(*it1 > *it2){
            out.push_back(*it2);
            it2++;
        }
        else{
            out.push_back(*it1);
            it1++;
        }
        if(it1 == l1.end()){
            while (it2 != l2.end()) {
                out.push_back(*it2);
                it2++;
            }
            break;
        }
        if(it2 == l2.end()){
            while (it1 != l1.end()) {
                out.push_back(*it1);
                it1++;
            }
            break;
        }
    }
    return out;
};
void mergesort(list<int> *lst){
    list<int>::iterator it_b = lst->begin();
    list<int>::iterator it_m = lst->begin();
    advance(it_m, lst->size()/2); // move from begin to mid
    list<int>::iterator it_e = lst->end();
    if(lst->size() > 1){
        list<int> l1 (it_b, it_m);
        list<int> l2 (it_m, it_e);
        mergesort(&l1);
        mergesort(&l2);
        *lst = merge(l1, l2);
    }
};

int main(int argc, const char * argv[]) {
    list<int> l1;
    l1.push_back(3);
    l1.push_back(2);
    l1.push_back(1);
    l1.push_back(4);

    print_list(l1);
    mergesort(&l1);
    print_list(l1);
    return 0;
}
