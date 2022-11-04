#include "Car.h"

void Car::setModel(std::string model){
    this->model = model;
}
void Car::setYear(int year){
    this->year = year;
}
void Car::setPrice(double price){
    this->price = price;
}
std::string Car::getModel(){
    return model;
}
int Car::getYear(){
    return year;
}
double Car::getPrice(){
    return price;
}
Car::Car(): model{"none"}, year{0}, price{0.0}{}
Car::Car(std::string model, int year, double price): model{model}, year{year}, price{price}{}