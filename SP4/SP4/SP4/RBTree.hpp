//
//  RBTree.hpp
//  SP4
//
//  Created by TsengKai Han on 3/10/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#ifndef RBTree_hpp
#define RBTree_hpp

#include <stdio.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

//template <class T>
class RBEntry {//red is false, black is true
public:
    int element;
    bool color, child;//left child is true, right is false
    RBEntry *left, *right, *parent;
    RBEntry(int x, RBEntry *l, RBEntry *r, RBEntry *p) {
        element = x;
        left = l;
        right = r;
        parent = p;
        color = false;//default is red
        child = true;//default is left child
    }
};

//template <class T>
class RBT {
public:
    //varible
    RBEntry *root;
    int size;
    //constructor
    RBT(){
        root = NULL;
        size = 0;
    }
    RBT(vector<int> arr){
        root = sortArrConstruct(arr);
        size = int(arr.size());
    }
    //methods
    RBEntry* find(RBEntry *t, int x);
    bool contains(int x);
    bool add(int x);
    void repair(RBEntry *node);
    int remove(int x);
    RBEntry* oneChild(RBEntry *node);
    void remove(RBEntry *node);
    void removeOne(RBEntry *node);
    void removeTwo(RBEntry *node, bool r_l);
    vector<int> toArray();
    int inOrder(RBEntry *node, vector<int> *arr, int index);
    void printTree();
    void printTree(RBEntry *node);
    vector<RBEntry*> levelOrederArray();
    RBEntry* sortArrConstruct(vector<int> arr);
};

RBT readRBT();

#endif /* RBTree_hpp */
