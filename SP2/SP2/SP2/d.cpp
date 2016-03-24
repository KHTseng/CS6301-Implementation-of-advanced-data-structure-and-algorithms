//
//  d.cpp
//  SP2
//
//  Created by TsengKai Han on 2/1/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include <stdio.h>
#include "graph.cpp"
#include <queue>
#include <vector>
using namespace std;

vector<Vertex> oddLengthCycle(Graph *g){
    vector<Vertex> ans;
    vector<int> level(g->numNodes+1, 0);//record level of vertex
    queue<int> bfs, num;
    bfs.push(1);
    num.push(1);
    g->verts[1].seen = 1;
    ////record level
    while (!bfs.empty()) {
        int v = bfs.front();
        int c = num.front();
        bfs.pop();
        num.pop();
        level[v] = c;//update level
        //g->verts[v].seen = 1; //update seen
        for (list<Edge>::iterator it = g->verts[v].Adj.begin(); it != g->verts[v].Adj.end(); it++) {
            if (g->verts[it->otherEnd(g->verts[v]).name].seen == 0) {//unvisited
                bfs.push(it->otherEnd(g->verts[v]).name);
                g->verts[it->otherEnd(g->verts[v]).name].seen = 1;//update seen
                num.push(c+1);
                g->verts[it->otherEnd(g->verts[v]).name].parent = &g->verts[v];//update parent
            }
        }
    }
    ////find edge
    int u = 0,v = 0;//same level edge's vertex
    for (int i = 1; i <= g->numNodes; i++) {
        for (list<Edge>::iterator e = g->verts[i].Adj.begin(); e != g->verts[i].Adj.end(); e++) {
            if (level[i] == level[e->otherEnd(g->verts[i]).name]) {
                u = i;
                v = e->otherEnd(g->verts[i]).name;
                goto found;//found the edge
            }
        }
    }
found:
    if (u == 0 || v == 0) {// bipartite
        return ans;
    }
    ////find cycle
    stack<Vertex> temp;//
    while(1){
        if (u == v) {
            ans.push_back(g->verts[u]);
            break;
        }
        ans.push_back(g->verts[u]);
        temp.push(g->verts[v]);
        u = g->verts[u].parent->name;
        v = g->verts[v].parent->name;
    }
    while (!temp.empty()) {
        ans.push_back(temp.top());
        temp.pop();
    }
    return ans;
}

/*int main(){
    Graph g(7);
    g = g.readGraph(0);
    cout<<"done"<<endl;
    vector<Vertex> ans;
    ans = oddLengthCycle(&g);
    
    for (vector<Vertex>::iterator it = ans.begin(); it != ans.end(); it++) {
        cout<<it->name<<" ";
    }
    return 0;
}*/