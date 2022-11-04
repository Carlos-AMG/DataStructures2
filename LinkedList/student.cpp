#include "student.h"
#include <string>
Student::Student(std::string name, std::string course, int age): name{name}, course{course}, age{age}{
}

void Student::set_name(std::string name){
    this->name = name;
}
void Student::set_course(std::string course){
    this->course = course;
}
void Student::set_age(int age){
    this->age = age;
}
std::string Student::get_name(){
    return name;
}
std::string Student::get_course(){
    return course;
}
int Student::get_age(){
    return age;
}