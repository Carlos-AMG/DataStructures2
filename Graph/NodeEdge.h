#pragma once
class NodeVertex;
class Graph;
class NodeEdge{
    friend class NodeVertex;
    friend class Graph;
    int weight;
    NodeEdge * nextEdge;
    NodeVertex * target;
public:
    NodeEdge();
    NodeEdge(int weight, NodeVertex * target, NodeEdge * nextEdge);
    friend void storeData(Graph & g);
};

