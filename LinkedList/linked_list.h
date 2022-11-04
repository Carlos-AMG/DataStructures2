#include "node.h"
#pragma once


class LinkedList{
    Node * head;
public:
    LinkedList(std::string name, std::string course, int age);
    LinkedList();
    // ~LinkedList();
    void loadData(); //Hardcodeds
    Node * First();
    Node * Last();
    void PopFirst();
    void PopLast();
    Node * PrevNext(std::string name, bool choice = true);
    Node * Search(std::string name);
    void InsertStart(std::string name, std::string course, int age);
    void Remove(std::string name, bool recursive = false);
    void Empty();
    int Size();
    void Show();
    bool isEmpty();
    void InsertEnd(std::string name, std::string course, int age);
};