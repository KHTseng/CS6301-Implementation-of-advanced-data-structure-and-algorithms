//
//  main.cpp
//  SP2
//
//  Created by TsengKai Han on 1/30/16.
//  Copyright © 2016 TsengKai Han. All rights reserved.
//

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <stack>
using namespace std;

class Vertex;
class Edge;

class Vertex{
public:
    int name; // name of the vertex
    bool seen; // flag to check if the vertex has already been visited
    Vertex *parent; // parent of the vertex
    int distance; // distance to the vertex from the source vertex
    list<Edge> Adj, revAdj; // adjacency list; use LinkedList or ArrayLis
    int component_number;
    
    Vertex(){}
    ~Vertex() {}
    Vertex(int n) {
        name = n;
        seen = false;
        parent = NULL;
        Adj = list<Edge>();
        revAdj = list<Edge>();   /* only for directed graphs */
        component_number = 0;
    }
};

class Edge{
public:
    Vertex Head; // head vertex
    Vertex Tail; // tail vertex
    int Weight;// weight of the arc
    
    Edge(){}
    ~Edge() {}
    Edge(Vertex u, Vertex v, int w) {
        Head = u;
        Tail = v;
        Weight = w;
    }
    
    Vertex otherEnd(Vertex u) {
        // if the vertex u is the head of the arc, then return the tail else return the head
        if (Head.name == u.name) {
            return Tail;
        } else {
            return Head;
        }
    }
};

class Graph{
public:
    vector<Vertex> verts;
    vector<Edge> edges;
    int numNodes;
    
    Graph(){};
    ~Graph() {};
    Graph(int size){
        numNodes = size;
        //verts = vector<Vertex>(size + 1);
        // create an array of Vertex objects
        for (int i = 0; i <= size; i++){
            verts.push_back(Vertex(i)); //// vertex 0 is not used!!
        }
    }
    void addEdge(int a, int b, int weight) {
        Edge e = Edge(verts[a], verts[b], weight);
        edges.push_back(e);
        verts[a].Adj.push_back(e);
        verts[b].Adj.push_back(e);
    }
    void addDirectedEdge(int a, int b, int weight) {
        Edge e = Edge(verts[a], verts[b], weight);
        verts[a].Adj.push_back(e);
        verts[b].revAdj.push_back(e);
    }
    Graph readGraph(bool directed) {
        // read the graph related parameters
        int n; // number of vertices in the graph
        int m; // number of edges in the graph
        
        cin>>n>>m;
        // create a graph instance
        Graph g(n);
        for (int i = 0; i < m; i++) {
            int u;
            int v;
            int w;
            cin>>u>>v>>w;
            if(directed) {
                g.addDirectedEdge(u, v, w);
            } else {
                g.addEdge(u, v, w);
            }
        }
        return g;
    }
};