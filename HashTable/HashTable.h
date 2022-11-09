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
    std::vector <bool> vect;
    
    HashTable();
    HashTable(int size1);
    int __hash(std::string key);
    void printTable();
    void setItem(std::string key, std::string className, std::string name); //Key es el passwd
    void setItem2(std::string key, std::string className, std::string name); 
    void writeItem(int index, std::string key, std::string className, std::string name, std::fstream & output);
    Student getItem(std::string key, bool flag = true);
    //helpers, will help with collisions
    void calcPercentage();
    void doubleTable();
    void storeTable();
    ~HashTable();
};