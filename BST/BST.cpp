#include "BST.h"
#include <algorithm>
#include <iostream>

void BST::insertData(Node *& pos, Car * const& car){
    if (pos == nullptr){
        Node * aux = new Node();
        aux->setVehicle(car);
        pos = aux;
        return;
    }
    if (pos->getVehicle()->getPrice() < car->getPrice()){
        insertData(pos->getRight(), car);
    }else{
        insertData(pos->getLeft(), car);   
    }
}

void BST::insertData(Node *& pos, std::string model, int year, double price){
    if (pos == nullptr){
        Node * aux = new Node(model, year, price);
        pos = aux;
        return;
    }
    if (pos->getVehicle()->getPrice() < price){
        insertData(pos->getRight(), model, year, price);
    }else{
        insertData(pos->getLeft(), model, year, price);   
    }
}

Node * BST::findMin(Node * pos) const{
    if(pos == NULL)
        return NULL;
    else if(pos->getLeft() == NULL)
        return pos;
    else
        return findMin(pos->getLeft());
}

int BST::getHeight(Node* pos) const{
    if (pos == nullptr){
        return -1;
    }
    return 1 + std::max(getHeight(pos->getLeft()), getHeight(pos->getRight()));
}

Node * BST::getLowest(Node* pos) const{
    if (pos == nullptr || pos->getLeft() == nullptr){
        return pos;
    }
    return getLowest(pos->getLeft());
}

Node * BST::getHighest(Node* pos) const{
    if (pos == nullptr || pos->getRight() == nullptr){
        return pos;
    }
    return getHighest(pos->getRight());
}

Node * BST::findDataPtr(Node * pos, Car *car) const{
    if (pos == nullptr){
        return pos;
    }
    if (pos->getVehicle() == car){ //Compara solo direcciones, tal vez tendremos que cambiarla
        return pos;
    }
    if (pos->getVehicle()->getPrice() < car->getPrice()){
        findDataPtr(pos->getRight(), car);
    }else{
        findDataPtr(pos->getLeft(), car);
    }
}

Node * BST::findDataPtr(Node * pos, double price) const{
    if (pos == nullptr){
        return pos;
    }
    if (pos->getVehicle()->price == price){ //Compara solo direcciones, tal vez tendremos que cambiarla
        return pos;
    }
    if (pos->getVehicle()->price < price){
        findDataPtr(pos->getRight(), price);
    }else{
        findDataPtr(pos->getLeft(), price);
    }
}

Node * BST::deleteData(Node * pos, Car * car){
    if (pos == nullptr){
        return pos;
    }
    if (car->getPrice() < pos->getVehicle()->getPrice()){
        pos->setLeft(deleteData(pos->getLeft(), car));
    }else if (car->getPrice() > pos->getVehicle()->getPrice()){
        pos->setRight(deleteData(pos->getRight(), car));
    }else{
        if (pos->getLeft() == nullptr && pos->getRight() == nullptr){
            return pos->getLeft(); //Return null
        }else if (pos->getLeft() == nullptr){
            Node * temp = pos->getRight();
            delete pos;
            return temp;
        }else if (pos->getRight() == nullptr) {
            Node * temp = pos->getLeft();
            delete pos;
            return temp;
        }
        Node * temp = findMin(pos->getRight());
        pos->getVehicle()->setModel(temp->getVehicle()->getModel());
        pos->getVehicle()->setYear(temp->getVehicle()->getYear());
        pos->getVehicle()->setPrice(temp->getVehicle()->getPrice());

        pos->setRight(deleteData(pos->getRight(), temp->getVehicle())); //Aqui crasheaba, no pasa de esta linea porque?!!
    }
    return pos;
}

Node * BST::deleteData2(Node * pos, double price){
    if (pos == nullptr){
        return pos;
    }
    if (price < pos->vehicle->price){
        pos->left = deleteData2(pos->left, price);
    }else if (price > pos->vehicle->price){
        pos->right = deleteData2(pos->right, price);
    }else{
        if (pos->left == nullptr && pos->right == nullptr){
            return nullptr;
        }else if (pos->left == nullptr){
            Node * temp = pos->right;
            std::cout << "pos->" << temp->vehicle->price << std::endl;
            delete pos;
            return temp;
        }else if (pos->right == nullptr){
            Node * temp = pos->left;
            delete pos;
            return temp;
        }
        Node * temp = findMin(pos->right);
        pos->vehicle->model = temp->vehicle->model;
        pos->vehicle->year = temp->vehicle->year;
        pos->vehicle->price = temp->vehicle->price;

        pos->right = deleteData2(pos->right, temp->vehicle->price);
    }
    return pos;
}


void BST::inorderParse(Node *pos) const{
    if (pos == nullptr){
        return;
    }
    inorderParse(pos->getLeft());
    std::cout << "Model: " << pos->getVehicle()->getModel() << " Year: " << pos->getVehicle()->getYear() << " Price:" << pos->getVehicle()->getPrice() << std::endl;
    inorderParse(pos->getRight());
}

void BST::preorderParse(Node *pos) const{
    if (pos == nullptr){
        return;
    }
    std::cout << "Model: " << pos->getVehicle()->getModel() << " Year: " << pos->getVehicle()->getYear() << " Price:" << pos->getVehicle()->getPrice() << std::endl;
    preorderParse(pos->getLeft());
    preorderParse(pos->getRight());
}

void BST::postorderParse(Node *pos) const{
    if (pos == nullptr){
        return;
    }
    postorderParse(pos->getLeft());
    postorderParse(pos->getRight());
    std::cout << "Model: " << pos->getVehicle()->getModel() << " Year: " << pos->getVehicle()->getYear() << " Price:" << pos->getVehicle()->getPrice() << std::endl;
}

void BST::deleteTree(Node * pos){
    if (pos == nullptr){
        return;
    }
    deleteTree(pos->left);
    deleteTree(pos->right);
    delete pos;
}

void BST::deleteSubTree(Node * left, Node * right){
    deleteTree(left);
    deleteTree(right);
}

void BST::printTree(Node * root, int space){
    if (root == nullptr){
        return;
    }
    space += 10; //10 es el espacio por default

    printTree(root->right, space);
    std::cout << '\n';
    for (int i = 10; i < space; i++){
        std::cout << " ";
    }
    std::cout << root->vehicle->price << '\n';
    printTree(root->left, space);
}

void BST::printTreeInterface(Node *){
    printTree(root, 0);
}



BST::BST():root{nullptr}{};
Node *& BST::getRoot(){
    return root;
}

void BST::setRoot(Node * root){
    this->root = root;
}




// Node * BST::deleteData2(Node * pos, Car * car){
//     if (pos == nullptr){
//         return pos;
//     }
//     if (car->price < pos->vehicle->price){
//         pos->left = deleteData2(pos->left, car);
//     }else if (car->price > pos->vehicle->price){
//         pos->right = deleteData2(pos->right, car);
//     }else{
//         if (pos->left == nullptr && pos->right == nullptr){
//             return pos->left;
//         }else if (pos->left == nullptr){
//             Node * temp = pos->right;
//             delete pos;
//             return temp;
//         }else if (pos->right == nullptr){
//             Node * temp = pos->left;
//             delete pos;
//             return temp;
//         }
//         Node * temp = findMin(pos->right);
//         pos->vehicle->model = temp->vehicle->model;
//         pos->vehicle->year = temp->vehicle->year;
//         pos->vehicle->price = temp->vehicle->price;

//         pos->right = deleteData2(pos->right, temp->vehicle);
//     }
//     return pos;
// }