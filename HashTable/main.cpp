#include <iostream>
#include <limits>
#include "HashTable.h"
#include "student.h"
#include <vector>
#include <fstream>
#include <typeinfo>


using namespace std;
bool validate();

int main(){
    HashTable hash;
    Student temp;
    // vector <bool> vect(hash.size, false);
    string name;
    string className;
    string passwd;
    string helper;
    int index;
    int choice;
    bool continuar = true;
    bool flag1 = false;
    while (continuar){
        system("clear");
        cout << "\tMenu" << endl;
        cout << "1)Insertar Alumno\n2)Buscar alumno\n3)Modificar alumno\n4)Eliminar alumno\n5)Salir" << endl;
        cin >> choice;
        switch (choice){
            case 1: 
                cout << "\tInsertar alumno" << endl;
                cout << "Ingrese el nombre del alumno: ";
                cin >> name;
                cout << "Ingrese la materia que cursa: ";
                cin >> className;
                cout << "Ingrese la contrasena (con esta accedera y no se puede cambiar): ";
                cin >> passwd;
                temp = hash.getItem(passwd);
                if (temp.passwd == passwd){
                    cout << "Alumno ya existe con esa contrasena, intente con una diferente" << endl;
                    cin.get();
                    cin.get();
                    break;
                }
                hash.setItem(passwd, className, name);
                cout << "Insertando alumno..." << endl;
                cin.get();
                cin.get();
                break;
            case 2:
                cout << "\tBuscar alumno" << endl;
                cout << "Busque un alumno con su contrasena" << endl;
                cout << "Ingrese la contrasena: ";
                cin >> passwd;
                temp = hash.getItem(passwd);
                helper = temp.passwd;
                if (helper == passwd){
                    cout << "Alumno encontrado: " << endl;
                    temp.showStudent();
                }else{
                    cout << "Alumno no encontrado con la contrasena {" << passwd << "} asociada" << endl;
                }
                cin.get();
                cin.get();
                break;
            case 3:
                cout << "\tModificar alumno" << endl;
                cout << "Ingrese la contrasena del alumno a modificar: ";
                cin >> passwd;
                temp = hash.getItem(passwd);
                if (!temp.initialized){
                    cout << "Alumno no encontrado con la contrasena {" << passwd << "} asociada" << endl;
                    break;
                }
                cout << "Alumno encontrado, a continuacion ingrese la nueva informacion" << endl;
                cout << "Nota, no puede modificar la contrasena" << endl;
                cout << "Ingrese el nuevo nombre del alumno: ";
                cin >> name;
                cout << "Ingrese la nueva materia que cursa: ";
                cin >> className;
                index = hash.getIndex(passwd);
                hash.modifyItem(index, passwd, className, name);
                cout << "Alumno modificado con exito" << endl;
                cin.get();
                cin.get();
                break;
            case 4: 
                cout << "\tEliminar alumno" << endl;
                cout << "Ingrese la contrasena del alumno a eliminar: ";
                cin >> passwd;
                temp = hash.getItem(passwd);
                if (!temp.initialized){
                    cout << "Alumno no encontrado con la contrasena {" << passwd << "} asociada" << endl;
                    break;
                }
                // index = hash.getIndex(passwd);
                hash.removeItem(passwd);
                cout << "Alumno eliminado con exito" << endl;
                cin.get();
                cin.get();
                break;
            case 5:
                cout << "Saliendo...";
                continuar = false;
                cin.get();
                break;
        }
    }
    return 0;
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