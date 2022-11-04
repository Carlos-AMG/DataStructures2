#include <string>
#include "NodeEdge.h"
#include "City.h"

#pragma once

class Graph;
class NodeVertex{
    std::string vertexName; // This one
    City * city;
    NodeEdge * h_edge;
    NodeVertex * nextVertex;
    friend class Graph;
public:
    NodeVertex();
    NodeVertex(std::string name, NodeEdge * edge, NodeVertex * vertex);
    NodeVertex(std::string name, std::string country, int population , NodeEdge * edge, NodeVertex * vertex);
    ~NodeVertex();
    friend void storeData(Graph & g);

};
