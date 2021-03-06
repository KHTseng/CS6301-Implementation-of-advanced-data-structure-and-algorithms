//
//  main.cpp
//  SP1_d
//
//  Created by TsengKai Han on 1/22/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include <iostream>
#include <list>
#include <stack>
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
    stack<list<int>> stack1;
    stack<list<int>> stack2;
    ////splite list
    for (list<int>::iterator it = lst->begin(); it != lst->end();) {
        list<int> temp(it, ++it);
        stack1.push(temp);
    }
    ////merge
    while (stack1.size() > 1) {
        while (stack1.size() > 1) {
            list<int> temp1 = stack1.top();
            stack1.pop();
            list<int> temp2 = stack1.top();
            stack1.pop();
            stack2.push(merge(temp1, temp2));
        }
        while (stack2.size() > 1) {
            list<int> temp1 = stack2.top();
            stack2.pop();
            list<int> temp2 = stack2.top();
            stack2.pop();
            stack1.push(merge(temp1, temp2));
        }
    }
    *lst = stack1.empty() ? stack2.top() : stack1.top();
};

int main(int argc, const char * argv[]) {
    list<int> l1;
    l1.push_back(3);
    l1.push_back(2);
    l1.push_back(5);
    l1.push_back(4);
    l1.push_back(1);
    
    print_list(l1);
    mergesort(&l1);
    print_list(l1);
    
    return 0;
}
