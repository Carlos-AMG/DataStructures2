#include "Node.h"
#pragma once
class Node;
class Car;
class BST{
private:
    Node * root;
    friend class Node;
    friend class Car;
public:
    void insertData(Node *&, Car * const&); //const car to avoid making copies
    void insertData(Node *&, std::string model, int year, double price); //const car to avoid making copies
    int getHeight(Node*) const;
    void preorderParse(Node*) const;
    void inorderParse(Node *) const;
    void postorderParse(Node *) const;
    void setRoot(Node *);
    void deleteSubTree(Node *, Node *);
    void deleteTree(Node *);
    void printTree(Node *, int);
    void printTreeInterface(Node *);
    Node * deleteData(Node * , Car *);
    Node * getLowest(Node*) const;
    Node * getHighest(Node*) const;
    Node * findDataPtr(Node *, Car *) const;
    Node * findDataPtr(Node *, double price) const;
    Node * findMin(Node *) const;
    Node *& getRoot();
    Node * deleteData2(Node * pos, double price);
    BST();
    // Node * deleteData2(Node * pos, Car * car);

    // friend void loadData(BST * );
};