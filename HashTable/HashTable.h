#include <string>
#include <vector>
#include "student.h"

#pragma once

//70% treshold, once passed we duplicate our table
class HashTable {
public:
    int size;
    // int index;
    double percentage;
    std::vector <int> vect;
    
    HashTable();
    HashTable(int size1);
    int __hash(std::string key);
    int getIndex(std::string key);
    void printTable();
    void setItem(std::string key, std::string className, std::string name); 
    void modifyItem(int index, std::string passwd, std::string className, std::string name);
    void removeItem(std::string key);
    void writeItem(int index, std::string key, std::string className, std::string name);
    void writeItem(int index);
    Student getItem(std::string key);
    //helpers, will help with collisions
    void calcPercentage();
    void doubleTable();
    void storeTable();
    ~HashTable();
};