#include "BST.h"
#include <vector>
#include <limits>
#include <sstream>

using namespace std;
void loadData(BST &);
bool Validate();
void storeInterface(Node * pos);


int main(){
    BST tree;
    loadData(tree);
    bool continuar = true;
    bool flag1 = false;
    int choice;
    Node * aux = nullptr;
    string model;
    int year;
    double price;


    while (continuar){
        system("clear");
        cout << "\tMenu" << endl;
        cout << "1) Cargar arbol\n2)Anadir elemento al arbol\n3)Buscar elemento en arbol\n4)Eliminar elemento en nodo"<< endl;
        cout << "5)Preorder\n6)Inorder\n7)Postorder\n8)Guardar arbol\n9)Borrar arbol\n10)Imprimir arbol por precio\n11)Salir" << endl;
        cout << "Cual es su eleccion: ";
        cin >> choice;
        flag1 = Validate();
        if (flag1){
            switch (choice){
                case 1:
                    cout << "\tCargando arbol" << endl;
                    loadData(tree);
                    cin.get();
                    break;
                case 2:
                    cout << "\tAnadir elemento(automovil)" << endl;
                    cout << "Ingrese el modelo: ";
                    cin >> model;
                    cout << "Ingrese el anho: ";
                    cin >> year;
                    cout << "Ingrese el precio: ";
                    cin >> price;
                    tree.insertData(tree.getRoot(), model, year, price);
                    cin.get();
                    cin.get();
                    break;
                case 3:
                    cout << "\tBuscar elemento(automovil) por precio" << endl;
                    cout << "Ingresa el precio de el elemento a buscar: ";
                    cin >> price;
                    aux = tree.findDataPtr(tree.getRoot(), price);
                    if (aux){
                        cout << "Encontrado: " << endl;
                        cout << "Modelo: " << aux->getVehicle()->getModel() << endl;
                        cout << "Anho: " << aux->getVehicle()->getYear() << endl;
                        cout << "Precio: " << aux->getVehicle()->getPrice() << endl;
                    }else{
                        cout << "Vehiculo no encontrado" << endl;
                    }
                    cin.get();
                    cin.get();
                    break;
                case 4:
                    cout << "\tEliminar elemento(automovil) por precio" << endl;
                    cout << "Ingresa el precio de el elemento a eliminar: ";
                    cin >> price;
                    tree.setRoot(tree.deleteData2(tree.getRoot(), price));
                    break;
                case 5:
                    cout << "\tPreorder" << endl;
                    tree.preorderParse(tree.getRoot());
                    cin.get();
                    break;
                case 6:
                    cout << "\nInorder" << endl;
                    tree.inorderParse(tree.getRoot());
                    cin.get();
                    break;
                case 7: 
                    cout << "\nPostorder" << endl;
                    tree.postorderParse(tree.getRoot());
                    cin.get();
                    break;
                case 8:
                    cout << "\nGuardar arbol actual" << endl;
                    storeInterface(tree.getRoot());
                    cin.get();
                    break;
                case 9:
                    cout << "\tBorrando arbol" << endl;
                    // tree.deleteSubTree(tree.getRoot()->getLeft(), tree.getRoot()->getRight());
                    // tree.getRoot()->setLeft(nullptr);
                    // tree.getRoot()->setRight(nullptr);
                    tree.deleteTree(tree.getRoot());
                    tree.setRoot(nullptr);
                    cin.get();
                    break;
                case 10:
                    cout << "\tImprimir arbol por precios" << endl;
                    tree.printTree(tree.getRoot(), 0);
                    cin.get();
                    break;
                case 11: 
                    cout << "\tSaliendo" << endl;
                    continuar = false;
                    storeInterface(tree.getRoot());
                    cin.get();
                    break;
            }
        }
    }
    return 0;
}

void storeInterface(Node * pos){
    ofstream output("files/file01.txt", std::ios::trunc);
    if (output){
        storeData(pos, output);
    }else{
        cout << "No fue posible escribir";
    }
    output.close();
}

void storeData(Node * pos, ofstream & output){
    //Creo esto es lo mas optimo que estar creando cada ofstream en cada recursive call, asi nada mas
    //estamos pasando la referencia pero no se ve tan modular, creo tiene mucha responsabilidad esta funcion
    if (pos == nullptr){
        return;
    }
    output << pos->vehicle->model << "|" << pos->vehicle->year << "|" << pos->vehicle->price << "*" << endl;
    storeData(pos->left, output);
    storeData(pos->right, output);
}

void loadData(BST & tree){
    // cout << "it works" << endl;
    string line;
    string word;
    string temp;
    ifstream myfile("files/file01.txt");
    tree.deleteTree(tree.getRoot());
    tree.setRoot(nullptr);
    vector <string> row;
    if (myfile.is_open()){
        while (getline(myfile, line, '*') && getline(myfile, temp, '\n')){
            row.clear();
            stringstream sline(line);
            while (getline(sline, word, '|')){
                row.push_back(word);
            }
            tree.insertData(tree.getRoot(), row[0], stoi(row[1]), stod(row[2]));
        }
        myfile.close();
    }
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