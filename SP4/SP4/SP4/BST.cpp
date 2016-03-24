//
//  BST.cpp
//  SP4
//
//  Created by TsengKai Han on 3/9/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include "BST.hpp"

// Find x in subtree rooted at node t.  Returns node where search ends.
Entry* BST::find(Entry *t, int x){
    Entry *pre = t;
    while (t != NULL) {
        pre = t;
        if (t->element == x) {//find it!!
            return t;
        }
        else if (t->element > x){//too big
            t = t->left;
        }
        else{//too small
            t = t->right;
        }
    }
    return pre;
}

// Is x contained in tree?
bool BST::contains(int x){
    Entry *node = find(root, x);
    return node == NULL ? false : (node->element == x);
}

// Add x to tree.  If tree contains a node with same key, replace element by x.
// Returns true if x is a new element added to tree.
bool BST::add(int x){
    if(size == 0) {
        root = new Entry(x, NULL, NULL, NULL);
    } else {
        Entry *node = find(root, x);
        if(node->element == x) {//have the same key
            return false;
        }
        Entry *newNode = new Entry(x, NULL, NULL, node);
        if(node->element > x) {//new one is smaller
            node->left = newNode;
        } else {
            node->right = newNode;
        }
    }
    size++;
    return true;
}

// Remove x from tree.  Return x if found, otherwise return null
int BST::remove(int x) {
    int rv = NULL;
    if(size > 0) {
        Entry *node = find(root, x);
        if(node->element == x) {
            rv = node->element;
            remove(node);
            size--;
        }
    }
    return rv;
}

// Called when node has at most one child.  Returns that child.
Entry* BST::oneChild(Entry *node) {
    return node->left == NULL? node->right : node->left;
}

// Remove a node from tree
void BST::remove(Entry *node) {
    if(node->left != NULL && node->right != NULL) {
        removeTwo(node, 0);
    } else {
        removeOne(node);
    }
}

// remove node that has at most one child
void BST::removeOne(Entry *node) {
    if(node == root) {
        root = oneChild(root);
    } else {
        Entry *p = node->parent;
        if(p->left == node) {
            p->left = oneChild(node);
        } else {
            p->right = oneChild(node);
        }
    }
}

// remove node that has two children
void BST::removeTwo(Entry *node, bool r_l) {
    //case 1. minRight
    if(r_l){
        Entry *minRight = node->right;
        while(minRight->left != NULL) {
            minRight = minRight->left;
        }
        node->element = minRight->element;
        removeOne(minRight);
    }
    //case 2. maxLeft
    else{
        Entry *maxLeft = node->left;
        while(maxLeft->right != NULL) {
            maxLeft = maxLeft->right;
        }
        node->element = maxLeft->element;
        removeOne(maxLeft);
    }
}

// Create an array with the elements using in-order traversal of tree
vector<int> BST::toArray(){
    vector<int> arr;
    arr.resize(size);
    inOrder(root, &arr, 0);
    return arr;
}

// Recursive in-order traversal of tree rooted at "node".
// "index" is next element of array to be written.
// Returns index of next entry of arr to be written.
int BST::inOrder(Entry *node, vector<int> *arr, int index) {
    if(node != NULL) {
        index = inOrder(node->left, arr, index);
        (*arr)[index++] = node->element;
        index = inOrder(node->right, arr, index);
    }
    return index;
}

//print tree
void BST::printTree() {
    cout<<("[" + to_string(size) + "]");
    printTree(root);
    cout<<endl;
}

// Inorder traversal of tree
void BST::printTree(Entry *node) {
    if(node != NULL) {
        printTree(node->left);
        cout<<(" " + to_string(node->element));
        printTree(node->right);
    }
}

//return array with level order
vector<int> BST::levelOrederArray(){
    vector<int> arr;
    queue<Entry*> q;//BFS
    q.push(root);
    while (!q.empty()) {
        Entry* node = q.front();
        q.pop();
        if (node != NULL) {
            arr.push_back(node->element);
            q.push(node->left);
            q.push(node->right);
        }
    }
    return arr;
}

//method of construction by sorted array
Entry* BST::sortArrConstruct(vector<int> arr){
    if (arr.size() == 1) {//end condition 1
        Entry *node = new Entry(arr[0], NULL, NULL, NULL);
        return node;
    }
    else if (arr.size() == 2){//end condition 2
        Entry *node_p = new Entry(arr[0], NULL, NULL, NULL);
        Entry *node_c = new Entry(arr[1], NULL, NULL, NULL);
        node_p->right = node_c;
        return node_p;
    }
    else{//gerenal condition
        Entry *node = new Entry(arr[arr.size()/2], NULL, NULL, NULL);
        vector<int>::iterator it = arr.begin();
        advance(it, (arr.size()/2));
        vector<int> arrLeft(arr.begin(),it);
        advance(it, 1);
        vector<int> arrRight(it, arr.end());
        node->left = sortArrConstruct(arrLeft);
        node->right = sortArrConstruct(arrRight);
        return node;
    }
}

//build BST by concole input
BST readBST(){
    BST t;
    int next;
    while(cin>>next) {
        if(next > 0) {//add
            cout<<("Add " + to_string(next) + " : ");
            t.add(next);
            t.printTree();
        } else if(next < 0) {//remove
            cout<<("Remove " + to_string(next) + " : ");
            t.remove(-next);
            t.printTree();
        } else {//terminate
            vector<int> arr = t.levelOrederArray();
            cout<<"Final: ";
            for(int i=0; i<t.size; i++) {
                cout<<(to_string(arr[i]) + " ");
            }
            cout<<endl;
            return t;
        }		
    }
    return t;
}

