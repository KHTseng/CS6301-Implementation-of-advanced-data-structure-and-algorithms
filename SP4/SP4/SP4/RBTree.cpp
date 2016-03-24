//
//  RBT.cpp
//  SP4
//
//  Created by TsengKai Han on 3/10/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include "RBTree.hpp"

// Find x in subtree rooted at node t.  Returns node where search ends.
RBEntry* RBT::find(RBEntry *t, int x){
    RBEntry *pre = t;
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
bool RBT::contains(int x){
    RBEntry *node = find(root, x);
    return node == NULL ? false : (node->element == x);
}

// Add x to tree.  If tree contains a node with same key, replace element by x.
// Returns true if x is a new element added to tree.
bool RBT::add(int x){
    if(size == 0) {
        root = new RBEntry(x, NULL, NULL, NULL);
        root->color = true;//root is black
    } else {
        RBEntry *node = find(root, x);
        if(node->element == x) {//have the same key
            return false;
        }
        RBEntry *newNode = new RBEntry(x, NULL, NULL, node);
        if(node->element > x) {//new one is smaller
            node->left = newNode;
            newNode->child = true;
        } else {
            node->right = newNode;
            newNode->child = false;
        }
        if (!newNode->parent->color) {//parent is red, then repair
            repair(newNode);//repair
        }
    }
    size++;
    return true;
}

//Repair RBTree
void RBT::repair(RBEntry *node){
    if (node == root) {//if is root, turn it to black
        node->color = true;
        return;
    }
    if (node->parent->color) {
        return;
    }
    if (node->parent->parent->left != NULL && node->parent->parent->right != NULL &&!node->parent->parent->left->color && !node->parent->parent->right->color) {//parent and its sibling is red
        node->parent->parent->left->color = true;
        node->parent->parent->right->color = true;
        node->parent->parent->color = false;//grand parent turn into red
        repair(node->parent->parent);//repair grand parent
    }
    else if (!node->parent->color){//parent is red and its sibling is black.
        if (node->child == node->parent->child) {//is aligned with grandparent
            RBEntry* t3, *ggparent;
            //fix color
            node->parent->color = true;
            node->parent->parent->color = false;
            if (node->child) {//left left case
                t3 = node->parent->right;
                ggparent = node->parent->parent->parent;
                //fix t3
                node->parent->parent->left = t3;
                if (t3 != NULL) {
                    t3->parent = node->parent->parent;
                    t3->child = true;//left child
                }
                //fix ggparent
                if (ggparent == NULL) {//ggparent is root
                    root = node->parent;
                }
                else if (node->parent->parent->child) {//gparnebt is left child
                    ggparent->left = node->parent;
                    node->parent->child = true;
                }
                else{//gparent is right child
                    ggparent->right = node->parent;
                    node->parent->child = false;
                }
                //fix gparent
                node->parent->right = node->parent->parent;
                node->parent->right->parent = node->parent;
                node->parent->right->child = false;
                
                node->parent->parent = ggparent;
            }
            else{//right right case
                t3 = node->parent->left;
                ggparent = node->parent->parent->parent;
                //fix t3
                node->parent->parent->right = t3;
                if (t3 != NULL) {
                    t3->parent = node->parent->parent;
                    t3->child = false;//left child
                }
                //fix ggparent
                if (ggparent == NULL) {//ggparent is root
                    root = node->parent;
                }
                else if (node->parent->parent->child) {//gparnebt is left child
                    ggparent->left = node->parent;
                    node->parent->child = true;
                }
                else{//gparent is right child
                    ggparent->right = node->parent;
                    node->parent->child = false;
                }
                //fix gparent
                node->parent->left = node->parent->parent;
                node->parent->left->parent = node->parent;
                node->parent->left->child = true;
                
                node->parent->parent = ggparent;
            }
        }
        else{//is not aligned with grandparent
            if (node->child == true) {//right left case
                RBEntry *t3 = node->right, *gparent = node->parent->parent;
                //fix t3
                node->parent->left = t3;
                t3->parent = node->parent;
                t3->child = true;
                //fix gparent
                gparent->right = node;
                node->parent = gparent;
                node->child = false;
                //fix node
                node->parent->parent = node;
                node->parent->child = false;
                node->right = node->parent;
                //repair
                repair(node->right);
            }
            else{//left right case
                RBEntry *t3 = node->left, *gparent = node->parent->parent;
                //fix t3
                node->parent->right = t3;
                t3->parent = node->parent;
                t3->child = false;
                //fix gparent
                gparent->left = node;
                node->parent = gparent;
                node->child = true;
                //fix node
                node->parent->parent = node;
                node->parent->child = true;
                node->left = node->parent;
                //repair
                repair(node->left);
            }
        }
    }
}
// Remove x from tree.  Return x if found, otherwise return null
int RBT::remove(int x) {
    int rv = NULL;
    if(size > 0) {
        RBEntry *node = find(root, x);
        if(node->element == x) {
            rv = node->element;
            remove(node);
            size--;
        }
    }
    return rv;
}

// Called when node has at most one child.  Returns that child.
RBEntry* RBT::oneChild(RBEntry *node) {
    return node->left == NULL? node->right : node->left;
}

// Remove a node from tree
void RBT::remove(RBEntry *node) {
    if(node->left != NULL && node->right != NULL) {
        removeTwo(node, 0);
    } else {
        removeOne(node);
    }
}

// remove node that has at most one child
void RBT::removeOne(RBEntry *node) {
    if(node == root) {
        root = oneChild(root);
    } else {
        RBEntry *p = node->parent;
        if(p->left == node) {
            p->left = oneChild(node);
        } else {
            p->right = oneChild(node);
        }
    }
}

// remove node that has two children
void RBT::removeTwo(RBEntry *node, bool r_l) {
    //case 1. minRight
    if(r_l){
        RBEntry *minRight = node->right;
        while(minRight->left != NULL) {
            minRight = minRight->left;
        }
        node->element = minRight->element;
        removeOne(minRight);
    }
    //case 2. maxLeft
    else{
        RBEntry *maxLeft = node->left;
        while(maxLeft->right != NULL) {
            maxLeft = maxLeft->right;
        }
        node->element = maxLeft->element;
        removeOne(maxLeft);
    }
}

// Create an array with the elements using in-order traversal of tree
vector<int> RBT::toArray(){
    vector<int> arr;
    arr.resize(size);
    inOrder(root, &arr, 0);
    return arr;
}

// Recursive in-order traversal of tree rooted at "node".
// "index" is next element of array to be written.
// Returns index of next RBEntry of arr to be written.
int RBT::inOrder(RBEntry *node, vector<int> *arr, int index) {
    if(node != NULL) {
        index = inOrder(node->left, arr, index);
        (*arr)[index++] = node->element;
        index = inOrder(node->right, arr, index);
    }
    return index;
}

//print tree
void RBT::printTree() {
    cout<<("[" + to_string(size) + "]");
    printTree(root);
    cout<<endl;
}

// Inorder traversal of tree
void RBT::printTree(RBEntry *node) {
    if(node != NULL) {
        printTree(node->left);
        cout<<(" " + to_string(node->element));
        printTree(node->right);
    }
}

//return array with level order
vector<RBEntry*> RBT::levelOrederArray(){
    vector<RBEntry*> arr;
    queue<RBEntry*> q;//BFS
    q.push(root);
    while (!q.empty()) {
        RBEntry* node = q.front();
        q.pop();
        if (node != NULL) {
            arr.push_back(node);
            q.push(node->left);
            q.push(node->right);
        }
    }
    return arr;
}

//method of construction by sorted array
RBEntry* RBT::sortArrConstruct(vector<int> arr){
    if (arr.size() == 1) {//end condition 1
        RBEntry *node = new RBEntry(arr[0], NULL, NULL, NULL);
        return node;
    }
    else if (arr.size() == 2){//end condition 2
        RBEntry *node_p = new RBEntry(arr[0], NULL, NULL, NULL);
        RBEntry *node_c = new RBEntry(arr[1], NULL, NULL, NULL);
        node_p->right = node_c;
        return node_p;
    }
    else{//gerenal condition
        RBEntry *node = new RBEntry(arr[arr.size()/2], NULL, NULL, NULL);
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

//build RBT by concole input
RBT readRBT(){
    RBT t;
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
            vector<RBEntry*> arr = t.levelOrederArray();
            cout<<"Final: ";
            for(int i=0; i<t.size; i++) {
                cout<<(to_string(arr[i]->element) + "(" + to_string(arr[i]->color) + ")" + " ");
            }
            cout<<endl;
            return t;
        }
    }
    return t;
}
