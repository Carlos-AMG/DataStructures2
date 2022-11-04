#include <iostream>
#include <string> 
#include <sstream> 
#include <limits>
#include <vector>
#include <fstream>
#include "Graph.h"


void loadData(Graph & g);
void storeData(Graph & g);
bool validate();


using namespace std;
int main(){
    Graph g;
    loadData(g);
    bool continuar = true;
    bool flag1 = false;
    int choice;
    int weight;
    string cityName;
    string cityCountry;
    string city1, city2;
    int cityPopulation;
    
    while (continuar){
        system("cls");
        cout << "\tMenu" << endl;
        cout << "1) Cargar grafo\n2) Anadir Vertice\n3) Anadir Arista\n4) Eliminar Vertice\n5) Eliminar Arista";
        cout << "\n6) Mostrar grafo\n7) Guardar grafo\n8) Salir" << endl;
        cin >> choice;
        switch (choice){
            case 1:
                cout << "\tCargando grafo..." << endl;
                loadData(g);
                cin.get();
                cin.get();
                break;
            case 2:
                cout << "\tAnadir Vertice" << endl;
                cout << "Ingrese el nombre de la ciudad: ";
                cin >> cityName;
                cout << "Ingrese el pais de la ciudad: ";
                cin >> cityCountry;
                cout << "Ingrese la poblacion de la ciudad: ";
                cin >> cityPopulation;
                g.insertVertex(cityName, cityCountry, cityPopulation);
                cin.get();
                cin.get();
                break;
            case 3:
                cout << "\tAnadir Arista" << endl;
                cout << "Ingrese el nombre de la ciudad de origen: ";
                cin >> city1;
                cout << "Ingrese el nombre de la ciudad de destino: ";
                cin >> city2;
                cout << "Ingrese la distancia(km) entre las 2 ciudades: ";
                cin >> weight;
                g.insertEdge(city1, city2, weight);
                g.insertEdge(city2, city1, weight);
                cin.get();
                cin.get();
                break;
            case 4:
                cout << "\tEliminar Vertice" << endl;
                cout <<"Ingrese el nombre de la ciudad a eliminar: ";
                cin >> cityName;
                g.removeVertex(cityName);
                cin.get();
                break;
            case 5:
                cout << "\tEliminar Arista" << endl;
                cout <<"Ingrese el nombre de la primer ciudad: ";
                cin >> city1;
                cout << "Ingrese el nombre de la segunda ciudad: ";
                cin >> city2;
                g.removeEdge(city1, city2);
                g.removeEdge(city2, city1, 1);
                cin.get();
                break;
            case 6:
                cout << "\tMostrar grafo" << endl;
                g.showG();
                cin.get();
                cin.get();
                break;
            case 7:
                cout << "\tGuardando grafo..." << endl;
                storeData(g);
                cin.get();
                break;
            case 8:
                cout << "Saliendo...";
                continuar = false;
                //guardar aqui
                storeData(g);
                cin.get();
                break;
        }

    }
    return 0;
}

void storeData(Graph & g){
    ofstream output("./files/file01.txt", std::ios::trunc);
    NodeVertex * tmpVert = g.h_graph;
    NodeEdge * tmpEdg = nullptr;
    std::string tmpStr; 
    if (output){
        while (tmpVert)
        {
            tmpEdg = tmpVert->h_edge;
            // tmpStr = tmpEdg ? " tiene conexiones con: " : " no tiene conexiones";
            // std::cout << "[";
            // std::cout << "La ciudad: " << tmpVert->city->name << tmpStr;
            output << tmpVert->city->name << "|" << tmpVert->city->country << "|" << tmpVert->city->population << "*";
            while (tmpEdg){
                // std::cout << tmpEdg->target->city->name << " (" << tmpEdg->weight << " km)" << ", ";
                output << tmpEdg->target->city->name << "," << tmpEdg->weight;
                if (tmpEdg->nextEdge)
                    output << ",";
                tmpEdg = tmpEdg->nextEdge;
            }
            output << ";" << endl;
            // std::cout << "]" <<std::endl;
            tmpVert = tmpVert->nextVertex;
        }
        output.close();
    }else{
        cout << "No posible guardar archivo, intente de nuevo" << endl;
    }
}


void loadData(Graph & g){
    ifstream input("./files/file01.txt");
    vector <string> ciudad;
    vector <string> conexiones;
    vector <string> ciudades;
    string line;
    string city;
    string connections;
    string word;
    string temp;
    g.flushEverything();
    if (input.is_open()){
        while (getline(input, line, ';') && getline(input, temp, '\n')){ //Toma hasta ";\n" es decir, toda una linea (vertice con aristas)
            ciudad.clear();
            city = line.substr(0, line.find('*'));
            stringstream sline(city);
            while (getline(sline, word, '|')){
                ciudad.push_back(word);
            }
            g.insertVertex(ciudad[0], ciudad[1], stoi(ciudad[2]));
            ciudades.push_back(ciudad[0]);
        }
        //Tenemos que resetear el file pointer al principio para poder iterar otra vez sobre cada linea
        //y obtener las aristas de cada ciudad (ciudades[i]), puesto que si insertamos las aristas en el 
        //primer while, al usar searchVertex, nos devolvera null porque en ese punto no existen todos los vertices
        input.clear(); //Limpiamos el eofbit porque al llegar al final del archivo se activa y el seek no funcionara
        input.seekg(0, ios::beg);
        int counter = 0;
        while (getline(input, line, ';') && getline(input, temp, '\n')){
            conexiones.clear();
            connections = line.substr(line.find('*') + 1);
            stringstream sline(connections);
            int i = 1;
            while (getline(sline, word, ',')){
                conexiones.push_back(word);
                if (i % 2 == 0){
                    g.insertEdge(ciudades[counter], conexiones[0], stoi(conexiones[1]));
                    conexiones.clear();
                    // i = 1;
                    // continue;
                }
                i++;

            }
            counter++;  
        }
        input.close();
    }
}



bool Validate(){
    bool flag;
    flag = std::cin.fail();
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (flag)
        return false;
    else 
        return true;
}