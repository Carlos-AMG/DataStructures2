#include "Node.h"

Node::Node(): vehicle{new Car()}, left{nullptr}, right{nullptr}{}
Node::Node(std::string model, int year, double price): vehicle{new Car(model, year, price)}, left{nullptr}, right{nullptr}{}
Node::~Node(){delete this->vehicle;}
void Node::setVehicleData(std::string model, int age, double price){
    this->vehicle->setModel(model);
    this->vehicle->setYear(age);
    this->vehicle->setPrice(price);
}
void Node::setLeft(Node * left){
    this->left = left;
}
void Node::setRight(Node * right){
    this->right = right;
}
Car * Node::getVehicle(){
    return vehicle;
}
Node *& Node::getLeft(){
    return left;
}
Node *& Node::getRight(){
    return right;
}

void Node::setVehicle(Car * car){
    this->vehicle = car;
}
