#include <iostream>
#include <cstring>
#include "student.h"

Student::Student(): className {"null"}, name {"null"}, passwd {"null"}, initialized{false}{}

Student::Student (std::string className, std::string name, std::string passwd): initialized{true}{
    strcpy(this->className, className.c_str());
    strcpy(this->name, name.c_str());
    strcpy(this->passwd, passwd.c_str());
}

using namespace std;
void Student::showStudent(){
    cout << "\tStudent data" << endl;
    cout << "name: " << name << endl;
    cout << "class: " << className << endl;
    cout << "passwd: " << passwd << endl;
}
