//
//  main.cpp
//  SP4
//
//  Created by TsengKai Han on 3/9/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include "BST.hpp"
#include "RBTree.hpp"

int main(int argc, const char * argv[]) {
    vector<int> v;
    for (int i = 1; i<10; i++) {
        v.push_back(i);
    }
    RBT t;
    t = readRBT();
    return 0;
}
