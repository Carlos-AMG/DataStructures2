#include "linked_list.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

LinkedList::LinkedList(std::string name, std::string course, int age){
    Node * temp = new Node(name, course, age);
    head = temp;
}
LinkedList::LinkedList():head{nullptr}{
    // LinkedList::loadData();
}
void LinkedList::InsertEnd(std::string name, std::string course, int age){
    Node * temp = new Node(name, course, age);
    if (head){
        Node * aux = Last();
        aux->setNext(temp);
        temp->setNext(nullptr);
    }else{
        head = temp;
        head->setNext(nullptr);
    }
}
void LinkedList::Remove(std::string name, bool recursive){
    Node *temp = head;
    Node *temporal = nullptr;
    if (head != nullptr){
        while(temp && (temp->getNext())){
            if ((temp->get_student()->get_name()) == name){
                head = temp->getNext();
                delete temp;
                if (recursive)
                    LinkedList::Remove(name, true);
                return;
            }else if ((temp->getNext()->get_student()->get_name()) == name){
                temporal = (temp->getNext()->getNext());
                delete (temp->getNext());
                temp->setNext(temporal);
                if (recursive)
                    LinkedList::Remove(name, true);
                return;
            }
            temp = temp->getNext();
        }
        if ((head->get_student()->get_name()) == name){
            delete head;
            head = nullptr;
        }else if(recursive){
            return;
        }else{
            std::cout << "Imposible eliminar tal elemento, no existe" << std::endl;
        }
    }else{
        std::cout << "Lista vacia..." << std::endl;
    }
}
Node * LinkedList::Search(std::string name){
    Node * aux = head;
    Node * data = nullptr;
    int counter = 0;
    if (head){
        while(aux){
            if ((aux->get_student()->get_name()) == name){
                data = aux;
                counter++;
            }
            aux = aux->getNext();
        }
        return data;
    }
    return nullptr;
}
void LinkedList::Empty(){
    int nodes = 0;
    Node *aux = head;
    while(aux){
        nodes++;
        aux = aux->getNext();
    }
    while (nodes > 0){
        aux = head;
        for (size_t i = 0; i < nodes - 1; i++)
        {
            aux = aux->getNext();
        }
        delete aux;
        nodes--;
    }
    head = nullptr;
}

Node * LinkedList::First(){
    if (head){
        return head;
    }else{
        return nullptr;
    }
}
Node * LinkedList::Last(){
    Node * aux = head;
    while (aux){
        if ((aux->getNext()) == nullptr)
        {
            return aux;
        }
        aux = aux->getNext();   
    }
    return nullptr;
}
Node * LinkedList::PrevNext(std::string name, bool choice){
    Node * temp = head;
    Node * temporal = nullptr;
    Node * prev = nullptr;
    Node * next = nullptr;
    bool flag = false;
    if (head != nullptr){
        while (temp && (temp->getNext())){
            if ((temp->get_student()->get_name()) == name){ //caso donde el primer nodo contiene nuestro dato
                prev = nullptr;
                next = temp->getNext();
                if(choice)
                    return prev;
                else
                    return next;
            }else if((temp->getNext()->get_student()->get_name()) == name){ //caso donde el nodo que contiene nuestro elemento esta en cualquier parte menos el inicio
                prev = temp;
                next = temp->getNext()->getNext();
                if(choice)
                    return prev;
                else
                    return next;
            }
            temp = temp->getNext();
        }
        if ((head->get_student()->get_name()) == name){ //caso donde solo hay un nodo y contiene nuestro dato
            return nullptr;
        } else
            return nullptr; //caso donde no esta nuestro dato
        
    }else{
        return nullptr; //caso donde la lista esta vacia
    }
}
int LinkedList::Size(){
    int nodes = 0;
    Node *aux = head;
    while(aux){
        nodes++;
        aux = aux->getNext();
    }
    return nodes;
}
void LinkedList::Show(){
    Node * aux = head;
    Student * st;
    if (head)
    {
        while (aux)
        {
            st = aux->get_student();
            std::cout <<"Name: " <<  st->get_name() << ", course: " << st->get_course() << ", age: " << st->get_age() << std::endl;
            aux = aux->getNext();
        }
    }else{
        std::cout << "La lista esta vacia" << std::endl;
    }
}

void LinkedList::InsertStart(std::string name, std::string course, int age){
    Node *temp = new Node(name, course, age);
    if(head == nullptr)
        head = temp;
    else{
        temp->setNext(head);
        head = temp;
    }
}

bool LinkedList::isEmpty(){
    if (head){
        return false;
    }else{
        return true;
    }
}

void LinkedList::PopFirst(){
    Node * aux = head;
    if (head == nullptr){
        return;
    }
    if (head->getNext()){
        head = head->getNext();
        aux->setNext(nullptr);
    }else{
        head = nullptr;
    }
    
    delete aux;
}

void LinkedList::PopLast(){
    Node * aux = head;
    Node * toDel;
    if (head){
        if (head->getNext() == nullptr){
            toDel = head;
            head = nullptr;
        }else{
            while (aux->getNext()->getNext() != nullptr){
                aux = aux->getNext();
            }
            toDel = aux->getNext();
            aux->setNext(nullptr);
        }
        delete toDel;
    }
}


// LinkedList::~LinkedList(){
//     std::ofstream file;
//     file.open("file01.txt", std::ios::trunc);
//     Node * aux = head;
//     Student * st;
//     bool flag1 = false;
//     if (file.is_open())
//         flag1 = true;
//     if (head && flag1)
//     {
//         while (aux)
//         {
//             st = aux->get_student();
//             file << st->get_name() << "|" << st->get_course() << "|" << st->get_age() << "*" << std::endl;
//             aux = aux->getNext();
//         }
//     }
//     file.close();
// }

using namespace std;
void LinkedList::loadData(){
    string line;
    string line2;
    string temp;
    ifstream myfile("file01.txt");
    vector <string> row;
    if (myfile.is_open()){
        while (getline(myfile, line, '*') && getline(myfile, temp, '\n'))
        {
            row.clear();
            stringstream sline(line);
            while (getline(sline, line2, '|')){
                row.push_back(line2);
            }
            LinkedList::InsertEnd(row[0], row[1], stoi(row[2]));
        }
        myfile.close();
    }
}