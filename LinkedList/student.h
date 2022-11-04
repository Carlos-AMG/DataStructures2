#pragma once
#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    std::string course;
    int age;
public:
    Student(std::string name, std::string course, int age);
    void set_name(std::string name);
    void set_course(std::string course);
    void set_age(int age);
    std::string get_name();
    std::string get_course();
    int get_age();
};