#include "Graph.h"
#include <iostream>


Graph::Graph():h_graph{nullptr}{}
Graph::Graph(NodeVertex * ptr):h_graph{ptr}{}

void Graph::insertVertex(std::string vName){
    //Prepend de nuestro vertice
    NodeVertex * tmpVert = new NodeVertex(vName, nullptr, nullptr);
    if (h_graph){
        tmpVert->nextVertex = h_graph;
        h_graph = tmpVert;
    }else{
        h_graph = tmpVert;
    }
}

void Graph::insertVertex(std::string cityName, std::string cityCountry, int cityPopulation){
    //Prepend de nuestro vertice
    NodeVertex * tmpVert = new NodeVertex(cityName, cityCountry, cityPopulation,  nullptr, nullptr);
    if (h_graph){
        tmpVert->nextVertex = h_graph;
        h_graph = tmpVert;
    }else{
        h_graph = tmpVert;
    }
}

void Graph::insertEdge(std::string origin, std::string destination, int weight){
    //Imporante notar que esta funcion no nos sirve para insertar vertices, solo aristas
    NodeVertex * tmpVert = h_graph;
    NodeEdge * tmpEdg = nullptr;
    tmpVert = searchVertex(origin);
    if (tmpVert){ //Aqui nos vamos hacia los lados, iterando sobre aristas y colocamos una nueva
        // Un append sobre nuestra lista de vertices y 
        tmpEdg = tmpVert->h_edge;
        if (!tmpEdg){ //En caso de que no tengamos ninguna arista en nuestra lista de aristas
            NodeVertex * dest = searchVertex(destination);
            if (dest){
                NodeEdge * aux = new NodeEdge(weight, dest, nullptr);
                tmpVert->h_edge = aux;
            }else{
                std::cout << "Destino no encontrado" << std::endl;
            }
        }else{ //Caso donde tenemos mas de una arista en nuestra lista de aristas
            //Hacemos un prepend sobre lista aristas con nuestra nueva arista            
            NodeVertex * dest = searchVertex(destination); //Buscamos el vertice de destino
            if (dest){ //Caso donde encontremos el vertice de destino, pondremos el nuevo nodo al principio(prepend)
                NodeEdge * aux = new NodeEdge(weight, dest, nullptr);
                aux->nextEdge = tmpVert->h_edge;
                tmpVert->h_edge = aux;
            }else{
                std::cout << "Destino no encontrado" << std::endl;
            }
        }
    }else{ //No tiene caso hacer mas si no existe el vertice que buscamos
        std::cout << "Origen no encontrado" << std::endl;
    }  
}


NodeVertex * Graph::searchVertex(std::string name){
    NodeVertex * temp = h_graph;
    while (temp)
    {
        if (temp->city->name == name){
            return temp;
        }    
        temp = temp->nextVertex;
    }
    return nullptr;
}

void Graph::removeEdge(std::string origin, std::string destination, int passed){
    NodeVertex * tmpVert = searchVertex(origin);
    if (tmpVert){
        NodeEdge * tmpEdg = tmpVert->h_edge;
        NodeEdge * prev = nullptr;
        if (tmpEdg && tmpEdg->target->city->name == destination){ //Caso donde la primer arista es lo que queremos eliminar
            tmpVert->h_edge = tmpEdg->nextEdge;
            delete tmpEdg;
            return;
        }
        while (tmpEdg){ //Iteraremos hasta topar con lo que queremos eliminar y lo eliminaremos
            if (tmpEdg->target->city->name == destination){
                prev->nextEdge = prev->nextEdge->nextEdge;
                delete tmpEdg;
                return;
            }
            prev = tmpEdg;
            tmpEdg = tmpEdg->nextEdge;
        }
        if (!passed)
            std::cout << "No posible eliminar arista, el destino no existe" << std::endl;
    }else{
        if (!passed)
            std::cout << "No posible eliminar arista, el origen no existe" << std::endl;
    }
}

int Graph::getNodes(NodeEdge * tmpEdge){
    int nodes = 0;
    while (tmpEdge){
        nodes++;
        tmpEdge = tmpEdge->nextEdge;
    }
    return nodes;
}

void Graph::rmFrontToBack(NodeVertex * tmpVert, int nodes){
    NodeEdge * tmpEdge = tmpVert->h_edge;
    while (nodes > 0){
        tmpEdge = tmpVert->h_edge;
        for (int i = 0; i < nodes - 1; i++){
            tmpEdge = tmpEdge->nextEdge;
        }
        removeEdge(tmpEdge->target->city->name, tmpVert->city->name, 1);
        delete tmpEdge;
        nodes--;
    }
}

void Graph::removeVertex(std::string vName){            
    NodeVertex * tmpVert = h_graph;
    NodeEdge * tmpEdge = nullptr;
    int nodes;
    if (tmpVert && tmpVert->city->name == vName){
        h_graph = tmpVert->nextVertex;
        nodes = getNodes(tmpVert->h_edge);
        rmFrontToBack(tmpVert, nodes);
        tmpVert->h_edge = nullptr;
        delete tmpVert;
        return;
    }
    NodeVertex * prevVert = nullptr;
    while (tmpVert){
        if (tmpVert->city->name == vName){
            prevVert->nextVertex = prevVert->nextVertex->nextVertex;
            nodes = getNodes(tmpVert->h_edge);
            rmFrontToBack(tmpVert, nodes);
            tmpVert->h_edge = nullptr;
            delete tmpVert;
            return;
        }
        prevVert = tmpVert;
        tmpVert = tmpVert->nextVertex;
    }
}


void Graph::showG(){
    NodeVertex * tmpVert = h_graph;
    NodeEdge * tmpEdg = nullptr;
    std::string tmpStr;
    while (tmpVert)
    {
        tmpEdg = tmpVert->h_edge;
        tmpStr = tmpEdg ? " tiene conexiones con: " : " no tiene conexiones";
        std::cout << "[";
        std::cout << "La ciudad: " << tmpVert->city->name << tmpStr;
        while (tmpEdg){
            std::cout << tmpEdg->target->city->name << " (" << tmpEdg->weight << " km)";
            if (tmpEdg->nextEdge)
                std::cout << ", ";
            tmpEdg = tmpEdg->nextEdge;
        }
        std::cout << "]" <<std::endl;
        tmpVert = tmpVert->nextVertex;
    }
}

void Graph::flushEverything(){
    NodeVertex * tmpVert = h_graph;
    NodeEdge * tmpEdge = nullptr;

    int vertexNodes = 0;
    int edgeNodes = 0;

    while (tmpVert){ //contamos la cantidad de vertices
        vertexNodes++;
        tmpVert = tmpVert->nextVertex;
    }
    while (vertexNodes){ //Comenzamos iterando sobre los vertices, hasta llegar a n - 1
        tmpVert = h_graph;
        for (int i = 0; i < vertexNodes - 1; i++){
            tmpVert = tmpVert->nextVertex;
        }

        tmpEdge = tmpVert->h_edge; //Aqui comenzamos a contar los nodos de arista en n - 1 vertices
        while (tmpEdge){
            edgeNodes++;
            tmpEdge = tmpEdge->nextEdge;
        }
        while (edgeNodes){
            tmpEdge = tmpVert->h_edge;
            for (int i = 0; i < edgeNodes - 1; i++){
                tmpEdge = tmpEdge->nextEdge;
            }
            removeEdge(tmpEdge->target->city->name, tmpVert->city->name, 1);
            delete tmpEdge;
            edgeNodes --;
        } //Aqui terminamos de borrar los nodos de las aristas de n - 1 vertex
        delete tmpVert;
        vertexNodes--;
    }
    h_graph = nullptr;
}