#include "linked_list.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

bool Validate();
void LoadData(LinkedList & list);
void StoreData(LinkedList & list);

using namespace std;
int main(){
    bool continuar = true;
    int choice;
    Node * aux = nullptr;
    LinkedList lista;
    LoadData(lista);
    Student * st = nullptr;
    bool flag1 = false;

    int age;
    string name;
    string course;

    while (continuar){
        system("CLS");
        cout << "----Menu----" << endl;

        cout << "1)Print\n2)Prepend\n3)Append\n4)PopFirst\n5)PopLast\n6)Remove\n7)Search by name\n8)IsEmpty?" << endl;
        cout << "9)First\n10)Last\n11)Previous\n12)Next\n13)ListSize\n14)EmptyList\n15)Exit" << endl;
        // cout << "1) Crear Lista\n2) Insertar elemento al final de la lista\n3) Eliminar elemento\n4) Eliminar todas las instancias de un elemento"<< endl;
        // cout << "5) Buscar elemento en la lista\n6) Vaciar lista\n7) Inicializar lista\n8) Primer elemento de la lista\n9) Ultimo elemento de la lista" << endl;
        // cout << "10) Elemento anterior de un elemento\n11) Elemento siguiente de un elemento\n12) Tamano de la lista\n13) Mostrar lista" << endl;
        // cout << "14) Checar si lista es vacia\n15) Insertar elemento al principio de la lista\n16) Salir del programa" << endl;
        cout << "Introduzca su eleccion: ";
        cin >> choice;
        flag1 = Validate();
        if (flag1){
            switch (choice){
                case 1:
                    cout << "\tPrinting" << endl;
                    lista.Show();
                    cin.get();
                    break;
                case 2:
                    cout << "\tPrepend" << endl;
                    cout << "Introduce el nombre: ";
                    cin >> name;
                    cout << "Introduce el curso: ";
                    cin >> course;
                    cout << "introduce la edad: ";
                    cin >> age;
                    lista.InsertStart(name, course, age);
                    break;
                case 3:
                    cout << "\tAppend" << endl;
                    cout << "Introduce el nombre: ";
                    cin >> name;
                    cout << "Introduce el curso: ";
                    cin >> course;
                    cout << "introduce la edad: ";
                    cin >> age;
                    lista.InsertEnd(name, course, age);
                    break;
                case 4: 
                    cout << "\tPopFirst" << endl;
                    lista.PopFirst();
                    cin.get();
                    break;
                case 5:
                    cout << "\tPopLast" << endl;
                    lista.PopLast();
                    cin.get();
                    break;
                case 6:
                    cout << "\tRemove" << endl;
                    cout << "Introduzca el nombre a borrar: ";
                    cin >> name;
                    lista.Remove(name);
                    cin.get();
                    cin.get();
                    break;
                case 7:
                    cout << "\tSearch by name" << endl;
                    cout << "Introduzca el nombre a buscar: ";
                    cin >> name;
                    aux = lista.Search(name);
                    if (!aux){
                        cout << "Lista vacia o no se encontro" << endl;
                        cin.get();
                        cin.get();
                        break;
                    }
                    st = aux->get_student();
                    std::cout <<"Name: " <<  st->get_name() << ", age: " << st->get_age() << ", course: " << st->get_course() << std::endl;
                    cin.get();
                    cin.get();
                    break;
                case 8:
                    cout << "\tIsEmpty?" << endl;
                    cout << (lista.isEmpty() ? "La lista esta vacia " : "La lista no esta vacia") << endl;
                    cin.get();
                    break;
                case 9:
                    cout << "\tFirst" << endl;
                    aux = lista.First();
                    st = aux ? aux->get_student() : nullptr;
                    if (!st){
                        cout << "Lista vacia" << endl;
                        cin.get();
                        break;
                    }
                    std::cout <<"Name: " <<  st->get_name() << ", age: " << st->get_age() << ", course: " << st->get_course() << std::endl;
                    cin.get();
                    break;
                case 10:
                    cout << "\tlast" << endl;
                    aux = lista.Last();
                    st = aux ? aux->get_student() : nullptr;
                    if (!st){
                        cout << "Lista vacia" << endl;
                        cin.get();
                        break;
                    }
                    std::cout <<"Name: " <<  st->get_name() << ", age: " << st->get_age() << ", course: " << st->get_course() << std::endl;
                    cin.get();
                    break;
                case 11:
                    cout << "\tPrevious" << endl;
                    cout << "Introduzca el nombre a buscar: ";
                    cin >> name;
                    aux = lista.PrevNext(name);
                    if (!aux){
                        cout << "Lista vacia o no se encontro" << endl;
                        cin.get();
                        cin.get();
                        break;
                    }
                    st = aux->get_student();
                    std::cout <<"Name: " <<  st->get_name() << ", age: " << st->get_age() << ", course: " << st->get_course() << std::endl;
                    cin.get();
                    cin.get();
                    break;
                case 12:
                    cout << "\tNext" << endl;
                    cout << "Introduzca el nombre a buscar: ";
                    cin >> name;
                    aux = lista.PrevNext(name, false);
                    if (!aux){
                        cout << "Lista vacia o no se encontro" << endl;
                        cin.get();
                        cin.get();
                        break;
                    }
                    st = aux->get_student();
                    std::cout <<"Name: " <<  st->get_name() << ", age: " << st->get_age() << ", course: " << st->get_course() << std::endl;
                    cin.get();
                    cin.get();
                    break;
                case 13:
                    cout << "\tListSize" << endl;
                    cout << "Tamanho lista: " << lista.Size() << endl;
                    cin.get();
                    break;
                case 14:
                    cout << "\tEmptyList" << endl;
                    lista.Empty();
                    cin.get();
                    break;
                // case 100: 
                //     cout << "Experimental" << endl;
                //     LoadData(lista);
                //     cin.get();
                //     break;
                case 15:
                    cout << "Saliendo..." << endl;
                    continuar = false;
                    cin.get();
                    StoreData(lista);
                    break;
            }
        }
    }
    return 0;
}

void LoadData(LinkedList & list){
    string line;
    string word;
    string temp;
    ifstream myfile("file01.txt");
    if (!list.isEmpty())
        list.Empty();
    vector <string> row;
    if (myfile.is_open()){
        while (getline(myfile, line, '*') && getline(myfile, temp, '\n'))
        {
            row.clear();
            stringstream sline(line);
            while (getline(sline, word, '|')){
                row.push_back(word);
            }
            list.InsertEnd(row[0], row[1], stoi(row[2]));
        }
        myfile.close();
    }
}

void StoreData(LinkedList & list){
    std::ofstream file;
    file.open("file01.txt", std::ios::trunc);
    Node * aux = list.First();
    Student * st;
    bool flag1 = false;
    if (file.is_open())
        flag1 = true;
    if (list.First() && flag1)
    {
        while (aux)
        {
            st = aux->get_student();
            file << st->get_name() << "|" << st->get_course() << "|" << st->get_age() << "*" << std::endl;
            aux = aux->getNext();
        }
    }
    file.close(); 
}






bool Validate(){
    bool flag;
    flag = std::cin.fail();
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (flag)
        return false;
    else 
        return true;
}