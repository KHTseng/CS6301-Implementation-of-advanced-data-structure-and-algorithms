//
//  c.cpp
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

void transpose(Graph *g){
    for (vector<Vertex>::iterator it = g->verts.begin(); it != g->verts.end(); it++) {
        list<Edge> temp;
        temp = it->Adj;
        it->Adj = it->revAdj;
        it->revAdj = temp;
    }
}

void dfs1(int v, stack<int> &s, Graph *g){
    g->verts[v].seen = 1;
    for (list<Edge>::iterator it = g->verts[v].Adj.begin(); it != g->verts[v].Adj.end(); it++) {
        if (g->verts[it->Tail.name].seen == 0) {
            dfs1(it->Tail.name, s, g);
        }
    }
    s.push(v);
}

void dfs2(int v, int C_num, Graph *g){
    g->verts[v].seen = 0;// visited
    g->verts[v].component_number = C_num;//set component number
    for (list<Edge>::iterator it = g->verts[v].Adj.begin(); it != g->verts[v].Adj.end(); it++) {
        if (g->verts[it->Head.name].seen == 1) {//not visited // head because transpose
            dfs2(it->Head.name, C_num, g);
        }
    }
}

int SCC(Graph *g){
    stack<int> dfs;
    for (int i = 1; i <= g->numNodes; i++) {//0 not used
        if (g->verts[i].seen == 0) {
            dfs1(i, dfs, g);
        }
    }
    int component_number = 0;
    transpose(g);
    
    while (!dfs.empty()) {
        int v = dfs.top();
        dfs.pop();
        if (g->verts[v].seen == 1) { //not visited
            component_number++;
            dfs2(v, component_number, g);
        }
    }
    return component_number;
}

int main(){
    Graph g;
    g = g.readGraph(1);
    cout<<SCC(&g);
    cout<<endl;
    
    return 0;
}