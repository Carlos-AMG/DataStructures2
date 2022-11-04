#pragma once
#include <string>
#include "student.h"

class Node{
    Student * st1;
    Node * next;
public:
    Node(std::string name, std::string course, int age);
    void setNext(Node * ptr);
    void setData(std::string name, std::string course, int age);
    Node * getNext();
    Student * get_student();
    ~Node();
};