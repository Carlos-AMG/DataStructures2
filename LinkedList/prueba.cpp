#include "linked_list.h"
#include <iostream>
#include <cstdlib>
#include <limits>

bool Validate(int num);
using namespace std;
int main(){
    bool flag = true;
    bool continuar = false;
    int choice;
    int instances;
    Node * aux;
    string data;
    LinkedList lista;
    while (flag){
        system("CLS");
        cout << "----Menu----" << endl;
        cout << "1) Crear Lista\n2) Insertar elemento al principio de la lista\n3) Eliminar elemento\n4) Eliminar todas las instancias de un elemento"<< endl;
        cout << "5) Buscar elemento en la lista\n6) Vaciar lista\n7) Inicializar lista\n8) Primer elemento de la lista\n9) Ultimo elemento de la lista" << endl;
        cout << "10) Elemento anterior de un elemento\n11) Elemento siguiente de un elemento\n12) Tamano de la lista\n13) Mostrar lista" << endl;
        cout << "14) Checar si la lista esta vacia\n15) Insertar elemento al final de la lista\n16) Salir del programa" << endl;
        cin >> choice;
        if (choice == 1 && Validate(choice)){
            system("CLS");
            cout << "Creando lista..." << endl;
            system("pause");
            continuar = true;
            continue;
        }
        if (continuar)
        {
            switch (choice)
            {
            case 2:
                system("CLS");
                cout << "----Insertar elemento al principio lista----" << endl;
                cout << "Introduzca el elemento que desea introducir: ";
                cin >> data;
                lista.InsertStart(data);
                system("pause");
                break;
            case 3:
                system("CLS");
                cout << "----Eliminar elemento----" << endl;
                cout << "Introduzca el elemento que desea eliminar: ";
                cin >> data;
                lista.Remove(data);
                system("pause");
                break;
            case 4:
                system("CLS");
                cout << "----Eliminar todas las instancias de un elemento----" << endl;
                cout << "Introduzca el elemento que desea eliminar: ";
                cin >> data;
                lista.Remove(data, true);
                system("pause");
                break;
            case 5:
                system("CLS");
                cout << "----Buscar elemento----" << endl;
                cout << "Introduzca el elemento que desea buscar" << endl;
                cin >> data;
                instances = lista.Search(data);
                if(instances > 0){
                    cout << "El elemento se encuentra en la lista " << instances << " veces" << endl;
                }else if(instances == -1){
                    cout << "La lista esta vacia" << endl;
                }else {
                    cout << "El elemento no se encuentra en la lista" << endl;
                }
                system("pause");
                break;
            case 6:
                system("CLS");
                cout << "Vaciando la lista..." << endl;
                lista.Empty();
                system("pause");
                break;
            case 7:
                system("CLS");
                cout << "Inicializando la lista..." << endl;
                lista.Empty();
                system("pause");
                break;
            case 8:
                system("CLS");
                cout << "----Primer dato de la lista----" << endl;
                aux = lista.First();
                if(aux)
                    cout << "El primer dato de la lista es: " << aux->getData() << endl;
                else    
                    cout << "La lista esta vacia" << endl;
                system("pause");
                break; 
            case 9:
                system("CLS");
                cout << "----Ultimo dato de la lista----" << endl;
                aux = lista.Last();
                if(aux)
                    cout << "El ultimo dato de la lista es: " << aux->getData() << endl;
                else    
                    cout << "La lista esta vacia" << endl;
                system("pause");
                break; 
            case 10:
                system("CLS");
                cout << "----Elemento anterior a un elemento---" << endl;
                cout << "Ingrese el elemento: ";
                cin >> data;
                aux = lista.PrevNext(data);
                instances = lista.Search(data);
                if (aux){
                    cout << "El elemento anterior es: " << aux->getData() << endl;
                }else if(instances == -1){
                    cout << "La lista esta vacia" << endl;
                }else{
                    cout << "No existe elemento anterior para su dato" << endl;
                }
                system("pause");
                break;
            case 11:
                system("CLS");
                cout << "----Elemento siguiente a un elemento---" << endl;
                cout << "Ingrese el elemento: ";
                cin >> data;
                aux = lista.PrevNext(data, false);
                instances = lista.Search(data);
                if (aux){
                    cout << "El elemento siguiente es: " << aux->getData() << endl;
                }else if(instances == -1){
                    cout << "La lista esta vacia" << endl;
                }else{
                    cout << "No existe elemento siguiente para su dato" << endl;
                }
                system("pause");
                break;
            case 12:
                system("CLS");
                cout << "----Tamano de la lista----" << endl;
                cout << "El tamano de la lista es de " << lista.Size() << " elementos" << endl;
                system("pause");
                break;
            case 13:
                system("CLS");
                cout << "----Mostrar lista----" << endl;
                lista.Show();
                system("pause");
                break;
            case 14:
                system("CLS");
                cout << "----Checar si la lista esta vacia----" << endl;
                cout << lista.isEmpty();
                if (lista.isEmpty()){
                    cout << "La lista esta vacia" << endl;
                }else{
                    cout << "La lista no esta vacia" << endl;
                }
                break;
            case 15:
                system("CLS");
                cout << "----Insertar elemento al final de la lista----" << endl;
                cout << "Introduzca el elemento que desea introducir: ";
                cin >> data;
                lista.InsertEnd(data);
                system("pause");
                break;
            case 16:
                system("CLS");
                cout << "Saliendo..." << endl;
                flag = false;
                break;
            default:
                cout << "Por favor ingrese una opcion valida" << endl;
                system("pause");
                break;
            }
        }else{
            cout << "Por favor cree una lista antes de intentar hacer operaciones" << endl;
            system("pause"); 
        }
    }
    system("pause");
    return 0;
}

bool Validate(int num){
    bool flag;
    flag = std::cin.fail();
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (flag)
        return false;
    else 
        return true;
}