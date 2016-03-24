//
//  b.cpp
//  SP2
//
//  Created by TsengKai Han on 1/31/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include "graph.cpp"
#include <queue>
using namespace std;

int diameter(Graph t){
    queue<int> bfs, dia;//diameter
    bfs.push(1);
    int v, count = 0, ans = 1; // record vertex name, number.
    vector<bool> seen(t.numNodes+1, 0);//record visited
    while (!bfs.empty()) {//BFS1
        v = bfs.front();
        count++;
        seen[v] = 1;
        bfs.pop();
        for (list<Edge>::iterator it = t.verts[v].Adj.begin(); it != t.verts[v].Adj.end(); it++) {
            if (seen[it->otherEnd(t.verts[v]).name] == 0) {// not visited
                bfs.push(it->otherEnd(t.verts[v]).name);
            }
        }
    }
    if (count != t.numNodes) {// not a tree
        return -1;
    }
    bfs.push(v);
    dia.push(1);// count distance
    while (!bfs.empty()) {//BFS2
        v = bfs.front();
        ans = dia.front();
        seen[v] = 0;//visited
        bfs.pop();
        dia.pop();
        for (list<Edge>::iterator it = t.verts[v].Adj.begin(); it != t.verts[v].Adj.end(); it++) {
            if (seen[it->otherEnd(t.verts[v]).name] == 1) {// not visited
                bfs.push(it->otherEnd(t.verts[v]).name);
                dia.push(ans + 1);
            }
        }
    }
    return ans;
}

/*int main(){
    ////create graph
    Graph g;
    g = g.readGraph(0);

    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 4, 1);
    g.addEdge(2, 5, 1);
    g.addEdge(4, 6, 1);
    g.addEdge(5, 7, 1);
    
     7 6
     1 2 1
     1 3 1
     2 4 1
     2 5 1
     4 6 1
     5 7 1
     
 
    
    cout<<diameter(g);
    cout<<endl;
    return 0;
}*/
