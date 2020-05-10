#ifndef BST_H
#define BST_H

#include <iostream>
#include <QPainter>

using namespace std;

template<typename T> class BST;
template<typename T>
class Node{
    friend class BST<T>;
public:
    Node();
private:
    T data;
    Node<T> *leftChild;
    Node<T> *rightChild;
    Node<T> *parent;
};

template<typename T>
class BST{
private:
    T data;
    Node<T> *leftChild;
    Node<T> *rightChild;
    Node<T> *parent;
    QPainter *painter;
    Node<T> root;
public:
    BST();
    ~BST();
    bool isEmpty() const;
    bool insertNode(const T &);
    void resetTree();
    void draw(QPainter *painter, double& scale);
};

template<typename T>
bool BST<T>::insertNode(const T &node){
    Node<T> *newNode = new Node<T>(node);
    if(this->isEmpty()){
        this->root = newNode;
        return 1;
    }

    Node<T> *currentNode = root;
    Node<T> *trailcurrentNode = root;
    while (currentNode != 0) {
        if(currentNode->data < node){
            trailcurrentNode = currentNode;
            currentNode = currentNode->rightChild;
        }
        else if(currentNode > node){
            trailcurrentNode = currentNode;
            currentNode = currentNode->leftChild;
        }
        else{
            cout << "Node đã tồn tại!";
            return 0;
        }
    }

    if(trailcurrentNode->data < node){
        trailcurrentNode->rightChild = newNode;
    }
    else{
        trailcurrentNode->leftChild = newNode;
    }
    return 1;
}

#endif // BST_H
