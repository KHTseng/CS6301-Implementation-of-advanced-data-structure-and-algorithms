//
//  main.cpp
//  MST
//
//  Created by TsengKai Han on 3/7/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include <iostream>
#include <queue>
#include <climits>
#include "graph.cpp"

class compare_prim1
{
    bool reverse;
public:
    compare_prim1(const bool& revparam=false)
    {reverse=revparam;}
    bool operator() (const Edge& lhs, const Edge& rhs) const
    {
        if (reverse) return (lhs.Weight>rhs.Weight);
        else return (lhs.Tail.name>rhs.Tail.name);
    }
};

////prim1
void prim1(Graph G){
    int weight = 0;
    vector<bool> seen(G.numNodes+1, false);
    ////delear p_queue
    typedef std::priority_queue<Edge,std::vector<Edge>,compare_prim1> mypq_type;
    mypq_type edge_queue(compare_prim1(true));//less is better
    mypq_type result;//record edges
    
    seen[1] = true;//pick 1 as root
    for (list<Edge>::iterator it = G.verts[1].Adj.begin(); it != G.verts[1].Adj.end(); it++) {
        edge_queue.push(*it);
    }
    
    while (!edge_queue.empty()) {
        Edge e = edge_queue.top();
        edge_queue.pop();
        if (seen[e.Head.name] && seen[e.Tail.name]) {//form a cycle
            continue;
        }
        weight = weight + e.Weight;//update weight
        int u;
        int v;
        if (seen[e.Head.name]) {//head is seen
            u = e.Head.name;
            v = e.Tail.name;
        }
        else{//tail is seen
            u = e.Tail.name;
            v = e.Head.name;
        }
        //put edge into result
        result.push(e);
        
        seen[v] = true;
        for (list<Edge>::iterator it = G.verts[v].Adj.begin(); it != G.verts[v].Adj.end(); it++) {
            if (!(seen[(*it).Head.name] && seen[(*it).Tail.name])) {// not a cycle
                edge_queue.push(*it);
            }
        }
    }
    
    ////output
    cout<<weight<<endl;
    /*while (!result.empty()) {
        cout<<"("<<result.top().Head.name<<","<<result.top().Tail.name<<")"<<endl;
        result.pop();
    }*/
}

class heap_vertex{
public:
    vector<Vertex*> arr;
    void rearrange(){
        for (int i = int(arr.size())-1; i > 0; i--) {
            if (arr[i]->distance < arr[(i-1)/2]->distance) {
                swap(arr[i], arr[(i-1)/2]);
            }
        }
    }
    void push(Vertex *v){
        arr.push_back(v);
    }
    Vertex pop(){
        Vertex v = *arr[0];
        swap(arr[0], arr.back());
        arr.erase(arr.end()-1);
        return v;
    }
};

////prim2
void prim2(Graph G){
    //initialize
    int weight = 0;
    heap_vertex heap;
    G.verts[1].distance = 0;
    heap.push(&G.verts[1]);
    for (int i = 2; i < G.numNodes+1; i++) {
        G.verts[i].distance = INT_MAX;
        heap.push(&G.verts[i]);
    }
    //mst
    while (heap.arr.size() != 0) {
        heap.rearrange();//rearrande before pop
        int u = heap.pop().name;
        G.verts[u].seen = true;
        weight = weight + G.verts[u].distance;//update weight
        for (list<Edge>::iterator it = G.verts[u].Adj.begin(); it != G.verts[u].Adj.end(); it++) {
            int v = it->otherEnd(G.verts[u]).name;
            if (!G.verts[v].seen && it->Weight < G.verts[v].distance) {
                G.verts[v].distance = it->Weight;
            }
        }
    }
    //output
    cout<<weight<<endl;
}

////Kruskal
void kruskal(Graph G){
    int weight = 0;
    ////sort edges into pqueue
    typedef std::priority_queue<Edge,std::vector<Edge>,compare_prim1> mypq_type;
    mypq_type edge_queue(compare_prim1(true));//less is better
    for (vector<Edge>::iterator it = G.edges.begin(); it != G.edges.end(); it++) {
        edge_queue.push(*it);
    }
    
    ////Kruskal
    vector<int> comp(G.numNodes+1, 0);//record component
    int compNum = 1;//number component
    while (!edge_queue.empty()) {
        Edge e = edge_queue.top();
        edge_queue.pop();
        if (comp[e.Tail.name] == comp[e.Head.name] && comp[e.Head.name] != 0) {//cycle
            continue;
        }
        weight = weight + e.Weight;
        if (comp[e.Tail.name] == comp[e.Head.name]) {//both not seen
            comp[e.Tail.name] = compNum;
            comp[e.Head.name] = compNum;
            compNum++;
        }
        else if(comp[e.Head.name] == 0){//expend
            comp[e.Head.name] = comp[e.Tail.name];
        }
        else if(comp[e.Tail.name] == 0){//expend
            comp[e.Tail.name] = comp[e.Head.name];
        }
        else{//union
            int temp = comp[e.Head.name];
            for (int i = 0; i < comp.size(); i++) {
                if (comp[i] == temp) {
                    comp[i] = comp[e.Tail.name];
                }
            }
        }
    }
    
    ////output
    cout<<weight<<endl;
}

int main(int argc, const char * argv[]) {
    Graph G;
    G = G.readGraph(0);
    cout<<"Prim1: ";
    prim1(G);
    cout<<"Prim2: ";
    prim2(G);
    cout<<"Kruskal: ";
    kruskal(G);
    return 0;
}

/*
simple input1:
5 6
1 2 5
1 3 6
1 4 4
2 5 1
3 5 3
3 4 2

output1:
 Prim1: 10
 Prim2: 10
 Kruskal: 10
 
input2:
 9 11
 1 2 1
 1 3 2
 3 5 5
 5 8 4
 3 4 6
 6 8 3
 6 7 9
 7 9 10
 9 8 11
 3 4 7
 4 6 8
 
output2:
 Prim1: 40
 Prim2: 40
 Kruskal: 40
*/