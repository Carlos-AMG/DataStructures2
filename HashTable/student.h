#include <string>
#pragma once

class Student{
public:
    bool initialized;
    char name [255];
    char className [255];
    char passwd [255];
    Student();
    Student (std::string className, std::string name, std::string passwd);
    void showStudent();
};