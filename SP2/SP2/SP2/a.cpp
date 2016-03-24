//
//  a.cpp
//  SP2
//
//  Created by TsengKai Han on 1/30/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include <stdio.h>
#include <list>
#include "graph.cpp"
#include <stack>
using namespace std;

list<Vertex> toplogicalOrder1(Graph g){
    list<Vertex> ans;
    vector<int> numComeing(g.numNodes+1, 0); // 0 not used
    
    for (int i = 1; i < g.verts.size(); i++) {// update numComing
        numComeing[i] = int(g.verts[i].revAdj.size());
    }
    while (ans.size() != g.verts.size()-1) {
        int tempAns = int(ans.size());
        for (int i = 1; i < g.verts.size(); i++) {
            if (numComeing[i] == 0 && g.verts[i].seen == 0) {// no coming edge
                ans.push_back(g.verts[i]);
                g.verts[i].seen = 1;
                for (list<Edge>::iterator it = g.verts[i].Adj.begin(); it != g.verts[i].Adj.end(); it++) {//update numComing
                    numComeing[it->otherEnd(g.verts[i]).name]--;
                    if (numComeing[it->otherEnd(g.verts[i]).name]< 0) {//check undirected edge
                        ans.clear();
                        return ans;
                    }
                }
            }
        }
        if (tempAns == ans.size()) {//check cycle
            ans.clear();
            return ans;
        }
    }
    return ans;
}

stack<Vertex> toplogicalOrder2(Graph g) {
    stack<Vertex> ans, wrong;
    stack<int> dfs;
    vector<int> numComeing(g.numNodes+1, 0); // 0 not used
    
    for (int i = 1; i < g.verts.size(); i++) {// update numComing
        numComeing[i] = int(g.verts[i].revAdj.size());
    }
    for (int i = 1; i < g.verts.size(); i++) {// push noncoming into stack
        if (numComeing[i] == 0) {
            g.verts[i].seen = 1;
            dfs.push(i);
        }
    }
    while (!dfs.empty()) {
        int v = dfs.top();
        dfs.pop();
        ans.push(g.verts[v]);
        for (list<Edge>::iterator it = g.verts[v].Adj.begin(); it != g.verts[v].Adj.end(); it++) {//update numComing
            numComeing[it->otherEnd(v).name]--;
            if (numComeing[it->otherEnd(v).name] < 0) {//check undirected edge
                return wrong;
            }
            if (numComeing[it->otherEnd(v).name] == 0) {//push nocoming into stack
                dfs.push(it->otherEnd(v).name);
            }
        }
    }
    if (ans.size() != g.numNodes) {// cycle
        return wrong;
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    ////create graph
    Graph g;
    g = g.readGraph(1);
    //toplogicalOrder
    list<Vertex> ans1;
    stack<Vertex> ans2;
    ans1 = toplogicalOrder1(g);
    ans2 = toplogicalOrder2(g);
    for (list<Vertex>::iterator it = ans1.begin(); it != ans1.end(); it++) {
        cout<<it->name<<" ";
    }
    cout<<endl;
    while (!ans2.empty()) {
        cout<<ans2.top().name<<" ";
        ans2.pop();
    }
    
    cout<<endl;
    return 0;
}