#include "NodeEdge.h"
#include "NodeVertex.h"
#pragma once

class Graph{
    NodeVertex * h_graph;
public:
    //Disclaimer: Todos buscan/insertan/eliminan en base de cityName, podriamos poner mas validaciones como cityName y pais pero nah
    Graph();
    Graph(NodeVertex * ptr);
    void insertVertex(std::string vName);
    void insertVertex(std::string cityName, std::string cityCountry, int cityPopulation); //Para clase City
    void insertEdge(std::string origin, std::string destination, int weight); //Ahora con clase City
    void removeEdge(std::string origin, std::string destination, int passed = 0); //Ahora con clase City
    void removeVertex(std::string vName); //vName es el cityName, dejare el atributo del vertexName solo por recuerdo
    int getNodes(NodeEdge * tmpEdge);
    void rmFrontToBack(NodeVertex * tmpVert, int nodes);
    void showG();
    void flushEverything();
    NodeVertex * searchVertex(std::string name); //Ahora con clase City
    // void insertEdge(NodeVertex * A, NodeVertex * B, int weight);
    // NodeVertex * searchVertex(std::string name);
    // void insertVertex(std::string vName, NodeVertex *);
    friend void storeData(Graph & g);
};