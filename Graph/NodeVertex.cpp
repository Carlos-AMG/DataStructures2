#include "NodeVertex.h"

NodeVertex::NodeVertex(): vertexName{" "}, h_edge{nullptr}, nextVertex{nullptr}{}

NodeVertex::NodeVertex(std::string name, NodeEdge * edge, NodeVertex * vertex): 
vertexName{name}, h_edge{edge}, nextVertex{vertex}{}
NodeVertex::NodeVertex(std::string name, std::string country, int population , NodeEdge * edge, NodeVertex * vertex): 
city{new City(name, country, population)}, h_edge{edge}, nextVertex{vertex}, vertexName{"None"}{}
NodeVertex::~NodeVertex(){
    delete city;
}