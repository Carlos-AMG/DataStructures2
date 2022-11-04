#include <string>
#pragma once

class NodeVertex;
class Graph;
class City
{
private:
    std::string name;
    std::string country;
    int population;
    friend class NodeVertex;
    friend class Graph;
public:
    City(std::string name, std::string country, int population);
    friend void storeData(Graph & g);
};
