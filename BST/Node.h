#include "Car.h"
#pragma once
class BST;
class Node{
private:
    Car * vehicle;
    Node * left;
    Node * right;
    friend class BST;
public:
    Node();
    Node(std::string model, int year, double price);
    ~Node();
    void setVehicleData(std::string, int, double);
    void setVehicle(Car *);
    void setLeft(Node *);
    void setRight(Node *);
    Car * getVehicle();
    Node *& getLeft();
    Node *& getRight();
    friend void storeData(Node *, std::ofstream &);
};