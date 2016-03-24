//
//  main.cpp
//  SP1_f
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

//template <class T>
list<int> re_non(list<int> lst){//reverse with nonrecursive
    list<int>::iterator it_f = lst.begin();
    list<int>::iterator it_b = lst.end();
    it_b --;
    int size = int(lst.size());
    for (int i = 0; i < size/2; i++) {
        int temp = *it_f;
        *it_f = *it_b;
        *it_b = temp;
        it_f++;
        it_b--;
    }
    return lst;
}

list<int> re(list<int> lst){// reverse with recursive
    list<int> out;
    int temp;
    if (!lst.empty()) {
        temp = *lst.begin();
        lst.erase(lst.begin());
        out = re(lst);
        out.push_back(temp);
        return out;
    }
    else{
        return out;
    }
}

void print_r_non(list<int> lst){
    while (!lst.empty()) {
        cout<<*--lst.end()<<" ";
        lst.erase(--lst.end());
    }
    cout<<endl;
}

void print_r(list<int> lst){
    if (!lst.empty()) {
        cout<<*--lst.end()<<" ";
        lst.erase(--lst.end());
        print_r(lst);
    }
    else{
        cout<<endl;
    }
}

int main(int argc, const char * argv[]) {
    list<int> l1;
    for (int i = 1; i < 11; i++) {
        l1.push_back(i);
    }
    print_list(l1);
    l1 = re_non(l1); //reverse
    print_list(l1);
    l1 = re(l1); //reverse
    print_list(l1);
    print_r(l1);
    print_r_non(l1);
    return 0;
}
