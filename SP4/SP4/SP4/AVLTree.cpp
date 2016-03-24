//
//  AVLTree.cpp
//  SP4
//
//  Created by TsengKai Han on 3/12/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include "AVLTree.hpp"

// Find x in subtree rooted at node t.  Returns node where search ends.
AVLEntry* AVLT::find(AVLEntry *t, int x){
    AVLEntry *pre = t;
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
bool AVLT::contains(int x){
    AVLEntry *node = find(root, x);
    return node == NULL ? false : (node->element == x);
}

// Add x to tree.  If tree contains a node with same key, replace element by x.
// Returns true if x is a new element added to tree.
bool AVLT::add(int x){
    if(size == 0) {
        root = new AVLEntry(x, NULL, NULL, NULL);
    } else {
        AVLEntry *node = find(root, x);
        if(node->element == x) {//have the same key
            return false;
        }
        AVLEntry *newNode = new AVLEntry(x, NULL, NULL, node);
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
int AVLT::remove(int x) {
    int rv = NULL;
    if(size > 0) {
        AVLEntry *node = find(root, x);
        if(node->element == x) {
            rv = node->element;
            remove(node);
            size--;
        }
    }
    return rv;
}

// Called when node has at most one child.  Returns that child.
AVLEntry* AVLT::oneChild(AVLEntry *node) {
    return node->left == NULL? node->right : node->left;
}

// Remove a node from tree
void AVLT::remove(AVLEntry *node) {
    if(node->left != NULL && node->right != NULL) {
        removeTwo(node, 0);
    } else {
        removeOne(node);
    }
}

// remove node that has at most one child
void AVLT::removeOne(AVLEntry *node) {
    if(node == root) {
        root = oneChild(root);
    } else {
        AVLEntry *p = node->parent;
        if(p->left == node) {
            p->left = oneChild(node);
        } else {
            p->right = oneChild(node);
        }
    }
}

// remove node that has two children
void AVLT::removeTwo(AVLEntry *node, bool r_l) {
    //case 1. minRight
    if(r_l){
        AVLEntry *minRight = node->right;
        while(minRight->left != NULL) {
            minRight = minRight->left;
        }
        node->element = minRight->element;
        removeOne(minRight);
    }
    //case 2. maxLeft
    else{
        AVLEntry *maxLeft = node->left;
        while(maxLeft->right != NULL) {
            maxLeft = maxLeft->right;
        }
        node->element = maxLeft->element;
        removeOne(maxLeft);
    }
}

// Create an array with the elements using in-order traversal of tree
vector<int> AVLT::toArray(){
    vector<int> arr;
    arr.resize(size);
    inOrder(root, &arr, 0);
    return arr;
}

// Recursive in-order traversal of tree rooted at "node".
// "index" is next element of array to be written.
// Returns index of next AVLEntry of arr to be written.
int AVLT::inOrder(AVLEntry *node, vector<int> *arr, int index) {
    if(node != NULL) {
        index = inOrder(node->left, arr, index);
        (*arr)[index++] = node->element;
        index = inOrder(node->right, arr, index);
    }
    return index;
}

//print tree
void AVLT::printTree() {
    cout<<("[" + to_string(size) + "]");
    printTree(root);
    cout<<endl;
}

// Inorder traversal of tree
void AVLT::printTree(AVLEntry *node) {
    if(node != NULL) {
        printTree(node->left);
        cout<<(" " + to_string(node->element));
        printTree(node->right);
    }
}

//return array with level order
vector<int> AVLT::levelOrederArray(){
    vector<int> arr;
    queue<AVLEntry*> q;//BFS
    q.push(root);
    while (!q.empty()) {
        AVLEntry* node = q.front();
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
AVLEntry* AVLT::sortArrConstruct(vector<int> arr){
    if (arr.size() == 1) {//end condition 1
        AVLEntry *node = new AVLEntry(arr[0], NULL, NULL, NULL);
        return node;
    }
    else if (arr.size() == 2){//end condition 2
        AVLEntry *node_p = new AVLEntry(arr[0], NULL, NULL, NULL);
        AVLEntry *node_c = new AVLEntry(arr[1], NULL, NULL, NULL);
        node_p->right = node_c;
        return node_p;
    }
    else{//gerenal condition
        AVLEntry *node = new AVLEntry(arr[arr.size()/2], NULL, NULL, NULL);
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

//Verify AVLTree
bool AVLT::verifyAVLTree(){
    if (root == NULL) {
        return true;
    }
    queue<AVLEntry*> BFS;//using bfs to go through the tree
    BFS.push(root);
    while (!BFS.empty()) {
        AVLEntry *node;
        node = BFS.front();
        BFS.pop();
        if (node->left == NULL && node->right == NULL) {//no child
            continue;
        }
        else if (node->right == NULL){//only left child
            if (node->element < node->left->element) {//invalid order condition
                return false;
            }
            else if(node->left->height > 0){//invalid SVL
                return false;
            }
        }
        else if (node->left == NULL){//only right child
            if (node->element > node->right->element) {//invalid order condition
                return false;
            }
            else if(node->right->height > 0){//invalid SVL
                return false;
            }
        }
        else{//two children
            if (node->element > node->right->element || node->element < node->left->element) {//invalid order condition
                return false;
            }
            else if((node->left->height - node->right->height) > 1 || (node->right->height - node->left->height) > 1){//invalid AVL
                return false;
            }
        }
    }
    return true;
}

//build AVLT by concole input
AVLT readAVLT(){
    AVLT t;
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

