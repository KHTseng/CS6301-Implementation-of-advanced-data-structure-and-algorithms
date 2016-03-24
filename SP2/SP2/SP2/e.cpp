//
//  e.cpp
//  SP2
//
//  Created by TsengKai Han on 2/3/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include <stdio.h>
#include "graph.cpp"
#include <queue>
using namespace std;

bool connected(Graph g){
    queue<int> bfs;
    list<int> s;//count size
    bfs.push(1);
    g.verts[1].seen = 1;
    while (!bfs.empty()) {
        int temp = bfs.front();
        s.push_back(temp);
        bfs.pop();
        for (list<Edge>::iterator it = g.verts[temp].Adj.begin(); it != g.verts[temp].Adj.end(); it++) {
            if (g.verts[it->otherEnd(g.verts[temp]).name].seen == 0) {//unvisited
                bfs.push(it->otherEnd(g.verts[temp]).name);
                g.verts[it->otherEnd(g.verts[temp]).name].seen = 1;//visited
            }
        }
    }
    if (s.size() == g.numNodes) {
        return 1;
    }
    else{
        return 0;
    }
}

int numOdd(Graph g){
    int num = 0;
    for (int i = 1; i <= g.numNodes; i++) {
        if (g.verts[i].Adj.size()%2 != 0) {
            num++;
        }
    }
    return num;
}

void eulerian(Graph g){
    if (!connected(g)) {
        cout<<"Graph is not connected."<<endl;
    }
    else{
        if (numOdd(g) == 0) {
            cout<<"Graph is Eulerian."<<endl;
        }
        else if(numOdd(g) == 2){
            vector<int> odd;
            for (int i = 1; i <= g.numNodes; i++) {
                if (g.verts[i].Adj.size()%2 != 0) {
                    odd.push_back(i);
                }
            }
            cout<<"Graph has an Eulerian Path between vertices "<<odd[0]<<" and "<<odd[1]<<" ."<<endl;
        }
        else{
            cout<<"Graph is not Eulerian.  It has "<<numOdd(g)<<" vertices of odd degree"<<endl;
        }
    }
}


int main(){
    Graph g;
    g = g.readGraph(0);
    eulerian(g);
    return 0;
}