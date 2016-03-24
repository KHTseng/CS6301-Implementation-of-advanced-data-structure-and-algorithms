//
//  AVLTree.hpp
//  SP4
//
//  Created by TsengKai Han on 3/12/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#ifndef AVLTree_hpp
#define AVLTree_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

//template <class T>
class AVLEntry {
public:
    int element, height;
    AVLEntry *left, *right, *parent;
    AVLEntry(int x, AVLEntry *l, AVLEntry *r, AVLEntry *p) {
        element = x;
        left = l;
        right = r;
        parent = p;
        height = 0;
    }
};

//template <class T>
class AVLT {
public:
    //varible
    AVLEntry *root;
    int size;
    //constructor
    AVLT(){
        root = NULL;
        size = 0;
    }
    AVLT(vector<int> arr){
        root = sortArrConstruct(arr);
        size = int(arr.size());
    }
    //methods
    AVLEntry* find(AVLEntry *t, int x);
    bool contains(int x);
    bool add(int x);
    int remove(int x);
    AVLEntry* oneChild(AVLEntry *node);
    void remove(AVLEntry *node);
    void removeOne(AVLEntry *node);
    void removeTwo(AVLEntry *node, bool r_l);
    vector<int> toArray();
    int inOrder(AVLEntry *node, vector<int> *arr, int index);
    void printTree();
    void printTree(AVLEntry *node);
    vector<int> levelOrederArray();
    AVLEntry* sortArrConstruct(vector<int> arr);
    bool verifyAVLTree();
};

AVLT readAVLT();

#endif /* AVLTree_hpp */
