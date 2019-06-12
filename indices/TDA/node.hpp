//
//  node.hpp
//  indices
//
//  Created by Oscar Sandoval on 2/9/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef node_h
#define node_h
#include <exception>
class NodeException : public std::exception {
private:
    std::string msg;
public:
    explicit NodeException(const char* message) : msg(message) {}
    explicit NodeException(const std::string& message) :msg(message) {}
    virtual ~NodeException() throw () {}
    virtual const char* what() const throw () {
        return msg.c_str();
    }
};

template <class T>
class Node {
public:
    Node();
    Node(const T&);
    ~Node();
    
    T& getData();
    T* getDataPtr();
    
    Node <T>* getPrev();
    Node<T>* getNext();
    
    void setData(const T&);
    void setDataPtr(T*);
    
    void setPrev(Node<T>*);
    void setNext(Node<T>*);
private:
    T* dataPtr;
    Node<T>* prev;
    Node<T>* next;
};

template <class T>
Node<T>::Node() {
    prev = nullptr;
    next = nullptr;
    dataPtr = nullptr;
}

template <class T>
Node<T>::Node(const T& e) : Node() {
    dataPtr = new T(e);
    
    if(dataPtr == nullptr) {
        throw NodeException("Memoria no disponible al crear nodo");
    }
}

template <class T>
Node<T>::~Node() {
    delete dataPtr;
}

template <class T>
T& Node<T>::getData() {
    return *dataPtr;
}

template <class T>
T* Node<T>::getDataPtr() {
    return dataPtr;
}

template <class T>
Node<T>* Node<T>::getPrev() {
    return prev;
}

template <class T>
Node<T>* Node<T>::getNext() {
    return next;
}

template <class T>
void Node<T>::setData(const T& e) {
    if(dataPtr == nullptr) {
        dataPtr = new T(e);
        if(dataPtr == nullptr) {
            NodeException("Error en SET DATA");
        }
        return;
    }
    
    *dataPtr = e;
}

template <class T>
void Node<T>::setDataPtr(T* ptr) {
    dataPtr = ptr;
}

template <class T>
void Node<T>::setPrev(Node<T>* ptr) {
    prev = ptr;
}

template <class T>
void Node<T>::setNext(Node<T>* ptr) {
    next = ptr;
}

#endif /* node_h */
