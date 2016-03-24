//
//  main.cpp
//  SP1_e
//
//  Created by TsengKai Han on 1/24/16.
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

void multiUnzip(list<int> *lst, int k){
    list<int>::iterator it = lst->begin();
    int size = int(lst->size());
    int c = 0; //count
    while (k > 1) {
        if (c % k == 0) {
            c++;
            it++;
        }
        else{
            lst->push_back(*it);
            it = lst->erase(it);
            c++;
        }
        if (c == size) {
            size = size - ((size - 1)/k) - 1;
            c = 0;
            k--;
        }
    }
}

int main(int argc, const char * argv[]) {
    list<int> l1;
    for (int i = 1; i < 21; i++) {
        l1.push_back(i);
    }
    
    print_list(l1);
    multiUnzip(&l1, 4);
    print_list(l1);
    
    return 0;
}
