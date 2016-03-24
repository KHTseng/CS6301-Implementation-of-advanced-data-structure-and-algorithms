//
//  BST.hpp
//  SP4
//
//  Created by TsengKai Han on 3/9/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#ifndef BST_hpp
#define BST_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

//template <class T>
class Entry {
public:
    int element;
    Entry *left, *right, *parent;
    Entry(int x, Entry *l, Entry *r, Entry *p) {
        element = x;
        left = l;
        right = r;
        parent = p;
    }
};

//template <class T>
class BST {
public:
    //varible
    Entry *root;
    int size;
    //constructor
    BST(){
        root = NULL;
        size = 0;
    }
    BST(vector<int> arr){
        root = sortArrConstruct(arr);
        size = int(arr.size());
    }
    //methods
    Entry* find(Entry *t, int x);
    bool contains(int x);
    bool add(int x);
    int remove(int x);
    Entry* oneChild(Entry *node);
    void remove(Entry *node);
    void removeOne(Entry *node);
    void removeTwo(Entry *node, bool r_l);
    vector<int> toArray();
    int inOrder(Entry *node, vector<int> *arr, int index);
    void printTree();
    void printTree(Entry *node);
    vector<int> levelOrederArray();
    Entry* sortArrConstruct(vector<int> arr);
};

BST readBST();
#endif /* BST_hpp */
