#include "node.h"

Node::Node(std::string name, std::string course, int age): st1{new Student(name, course, age)}, next{nullptr}{
}
void Node::setData(std::string name, std::string course, int age){
    st1->set_name(name);
    st1->set_course(course);
    st1->set_age(age);
}
void Node::setNext(Node * ptr){
    next = ptr;
}
Student * Node::get_student(){
    return st1;
}
Node * Node::getNext(){
    return next;
}

Node::~Node(){
    delete st1;
    st1 = nullptr;
}


