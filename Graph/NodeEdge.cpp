#include "NodeEdge.h"

NodeEdge::NodeEdge(): weight(0), target(nullptr), nextEdge(nullptr){}

NodeEdge::NodeEdge(int weight, NodeVertex * target, NodeEdge * nextEdge): weight{weight}, target{target}, nextEdge{nextEdge}{}


