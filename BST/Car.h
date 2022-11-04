#include <string>
#include <iostream>
#include <fstream>

#pragma once
class BST;
class Node;
class Car{
private:
    std::string model;
    int year;
    double price; //Ordenaremos segun el precio
    friend class BST;
public:
    void setModel(std::string);
    void setYear(int);
    void setPrice(double);
    std::string getModel();
    int getYear();
    double getPrice();
    Car();
    Car(std::string, int, double);
    friend void storeData(Node *, std::ofstream &);
};