//
//  bTree.hpp
//  indices
//
//  Created by Oscar Sandoval on 5/11/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef bTree_h
#define bTree_h
#include <iostream>
#include <utility>
#include <exception>
#include <string>
#include <fstream>
template<typename T>
class BTree {
public:
    //Exception Declaration (Tree)
    class Exception : public std::exception {
    private:
        std::string msg;
        
    public:
        explicit Exception(const char* message) : msg(message) {}
        explicit Exception(const std::string &message) : msg(message) {}
        
        virtual ~Exception() throw () {}
        
        virtual const char* what() const throw () {
            return msg.c_str();
        }
    };
    //Node Declaration
    class Node
    {
    public:
        //Exception Declaration (Node)
        class Exception : public std::exception {
        private:
            std::string msg;
            
        public:
            explicit Exception(const char* message) : msg(message) {}
            explicit Exception(const std::string &message) : msg(message) {}
            
            virtual ~Exception() throw () {}
            
            virtual const char* what() const throw () {
                return msg.c_str();
            }
        };
    private:
        T* dataPtr;
        Node* left;
        Node* right;
        Node* father;
    public:
        Node();
        Node(const T& e);
        Node(const T& e,Node*&);
        ~Node();
        
        T* getDataPtr();
        
        T& getData();
        void setData(const T& e);
        
        Node*& getRight();
        void setRight(Node*& p);
        Node*& getLeft();
        void setLeft(Node*& p);
        Node*& getFather();
        void setFather(Node*& p);
       
    };
    
private:
    Node* root;
    unsigned size;
    void insertData(Node*& r, const T& e,Node*& f);
    
    Node*& getLowest(Node*& r);
    Node*& getHighest(Node*& r);
    
    Node*& findData(Node*& r, const T& e);
    
    void parsePreOrder(Node*& r);
    void parseInOrder(Node*& r);
    void parsePostOrder(Node*& r);
    
    int getBalanceFactor(Node*& r);
    
    void simpleLeftRotation(Node*& r);
    void simpleRightRotation(Node*& r);
    void doubleLeftRotation(Node*& r);
    void doubleRightRotation(Node*& r);
    
    void doBalancing(Node*& r);
    
    void copyAll(Node*& from, Node*& to);
    
    int getHeight(Node*& r);
    
    void deleteAll(Node*& r);
    
    void saveTree(Node*& r,List<T>&);
    
    bool isValidInsert(Node*& r,T&);
    
    void getLowestRaking(Node*& r, T& d);
    
    void printTree(Node*&, int);
    
    void getElements(List<T>&,Node*&);
    
public:
    BTree();
    BTree(BTree& t);
    ~BTree();
    
    unsigned Size();
    
    bool isEmpty() const;
    bool isLeaf(Node*& r) const;
    
    void insertData(const T& e);
    void deleteData(Node*& r);
    
    Node*& findData(const T& e);
    
    T& retrieve(Node*& p);
    
    void parsePreOrder();
    void parseInOrder();
    void parsePostOrder();
    
    int getHeight();
    
    BTree& operator = (BTree& t);
    
    void deleteAll();
    
    bool isValidInsert(T&);
    
    T  getLowestRaking();
    
    void printTree();
    
    void getElements(List<T>&);
};

//Node Implementation
template<typename T>
BTree<T>::Node::Node() : dataPtr(nullptr), left(nullptr), right(nullptr),father(nullptr) {}

template<typename T>
BTree<T>::Node::Node(const T &e) : dataPtr(new T(e)), left(nullptr), right(nullptr),father(nullptr)
{
    if (dataPtr == nullptr) {
        throw Exception("Memoria no disponible, Node");
    }
}

template<typename T>
BTree<T>::Node::Node(const T &e,Node*& p) : dataPtr(new T(e)), left(nullptr), right(nullptr),father(p)
{
    if (dataPtr == nullptr) {
        throw Exception("Memoria no disponible, Node");
    }
}

template<typename T>
BTree<T>::Node::~Node()
{
    delete dataPtr;
}

template<class T>
T* BTree<T>::Node::getDataPtr() {
    return dataPtr;
}

template<typename T>
T& BTree<T>::Node::getData()
{
    return *dataPtr;
}

template<typename T>
void BTree<T>::Node::setData(const T& e)
{
    if (dataPtr == nullptr) {
        if ((dataPtr = new T(e)) == nullptr) {
            throw Exception("Memoria no disponible, setData");
        }
    } else {
        *dataPtr = e;
    }
}

template<typename T>
typename BTree<T>::Node*& BTree<T>::Node::getLeft()
{
    return left;
}

template<typename T>
typename BTree<T>::Node*& BTree<T>::Node::getFather(){
    return father;
}

template<typename T>
void BTree<T>::Node::setLeft(Node*& p)
{
    left = p;
}

template<typename T>
typename BTree<T>::Node*& BTree<T>::Node::getRight()
{
    return right;
}


template<typename T>
void BTree<T>::Node::setRight(Node*& p)
{
    right = p;
}
template<typename T>
void BTree<T>::Node::setFather(Node*& p){
    father = p;
}

//#endif // BTREE_H

//Tree implementation

template<typename T>
void BTree<T>::insertData(BTree::Node *&r, const T &e,BTree::Node *&f)
{
    if (r == nullptr) { //Inserción en hoja, todas las hojas estan alanceada
        try {
            if ((r = new Node(e,f)) == nullptr) {
                throw Exception("Memoria no disponible, insertData");
            }
        } catch (typename Node::Exception e) {
            throw Exception(e.what());
        }
        size++;
        return;
    }
    Node* aux(r);
        //Innsercion en un subarbol (recursivamente)
    if (e < r->getData()) {
        insertData(r->getLeft(), e,aux);
    } else {
        insertData(r->getRight(), e,aux);
    }
    //Se termina la recursividad
    doBalancing(r);
    
}

template <typename T>
unsigned BTree<T>::Size(){
    return size;
}

template<typename T>
typename BTree<T>::Node *&BTree<T>::getLowest(BTree::Node *&r)
{
    if (r == nullptr || r->getLeft() == nullptr) {
        return r;
    }
    
    return getLowest(r->getLeft());
}

template<typename T>
typename BTree<T>::Node *&BTree<T>::getHighest(BTree::Node *&r)
{
    if (r == nullptr || r->getRight() == nullptr) {
        return r;
    }
    
    return getHighest(r->getRight());
}

template<typename T>
typename BTree<T>::Node *&BTree<T>::findData(BTree::Node *&r, const T &e)
{
    if (r == nullptr || e == r->getData()) {
        if(r!=nullptr){
            r->getData().setRaking(r->getData().getRaking()+1);
        }
        return r;
    }
    
    if (e < r->getData()) {
        return findData(r->getLeft(), e);
    }
    
    return findData(r->getRight(), e);
}

template<typename T>
void BTree<T>::parsePreOrder(BTree::Node *&r)
{
    if (r == nullptr) {
        return;
    }
    
    std::cout << r->getData() << ", ";
    parsePreOrder(r->getLeft());
    parsePreOrder(r->getRight());
}

template<typename T>
void BTree<T>::parseInOrder(BTree::Node *&r)
{
    if (r == nullptr) {
        return;
    }
    
    parseInOrder(r->getLeft());
    std::cout << r->getData() << ", ";
    parseInOrder(r->getRight());
}

template<typename T>
void BTree<T>::parsePostOrder(BTree::Node *&r)
{
    if (r == nullptr) {
        return;
    }
    
    parsePostOrder(r->getLeft());
    parsePostOrder(r->getRight());
    std::cout << r->getData() << ", ";
}

template<typename T>
int BTree<T>::getBalanceFactor(BTree::Node *&r)
{
    return getHeight(r->getRight()) - getHeight(r->getLeft());
}

template<typename T>
void BTree<T>::simpleLeftRotation(BTree::Node *&r)
{
    Node* aux1(r->getRight());
    Node* aux2(aux1->getLeft());
//    aux1->setFather(r);
    r->setRight(aux2);
    if(aux2!=nullptr)
        aux2->setFather(r);
    aux1->setLeft(r);
    r->setFather(aux1);
    r = aux1;
}

template<typename T>
void BTree<T>::simpleRightRotation(BTree::Node *&r)
{
    Node* aux1(r->getLeft());
    Node* aux2(aux1->getRight());
    r->setLeft(aux2);
    if(aux2!=nullptr)
        aux2->setLeft(r);
    aux1->setRight(r);
    r->setFather(aux1);
    r = aux1;
}

template<typename T>
void BTree<T>::doubleLeftRotation(BTree::Node *&r)
{
    simpleRightRotation(r->getRight());
    simpleLeftRotation(r);
}

template<typename T>
void BTree<T>::doubleRightRotation(BTree::Node *&r)
{
    simpleLeftRotation(r->getLeft());
    simpleRightRotation(r);
}

template<typename T>
void BTree<T>::doBalancing(BTree::Node *&r)
{
    switch (getBalanceFactor(r)) {
        case 2:
            if (getBalanceFactor(r->getRight()) == 1) {
                //            std::cout << "RSI: " << r->getData() << std::endl;
                simpleLeftRotation(r);
            } else {
                //            std::cout << "RDI: " << r->getData() << std::endl;
                doubleLeftRotation(r);
            }
            break;
        case -2:
            if (getBalanceFactor(r->getLeft()) == -1) {
                //            std::cout << "RSD: " << r->getData() << std::endl;
                simpleRightRotation(r);
            } else {
                //            std::cout << "RDD: " << r->getData() << std::endl;
                doubleRightRotation(r);
            }
            break;
        default:
            break;
    }
}

template<typename T>
void BTree<T>::copyAll(Node*& from, Node*& to)
{
    if (from == nullptr) {
        return ;
    }
    
    try {
        if ((to = new Node(from->getData()) == nullptr)) {
            throw Exception("Memoria no disponible, copyAll");
        }
    } catch (typename Node::Exception e) {
        throw Exception(e.what());
    }
    
    copyAll(from->getLeft(), to->getLeft());
    copyAll(from->getRight(), to->getRight());
}

template<typename T>
int BTree<T>::getHeight(BTree::Node *&r)
{
    if (r == nullptr) {
        return 0;
    }
    
    int leftHeight(getHeight(r->getLeft()));
    int rightHeight(getHeight(r->getRight()));
    
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

template<typename T>
void BTree<T>::deleteAll(BTree::Node *&r)
{
    if (r == nullptr) {
        return;
    }
    deleteAll(r->getLeft());
    deleteAll(r->getRight());
    delete r;
    
    r = nullptr;
}

template<typename T>
BTree<T>::BTree() : root(nullptr),size(0) {}

template<typename T>
BTree<T>::BTree(BTree &t) : root(nullptr)
{
    copyAll(t.root, root);
}

template<typename T>
BTree<T>::~BTree()
{
    List<T> list;
    saveTree(root,list);
    deleteAll(root);
}

template <typename T>
void BTree<T>::saveTree(Node *&r,List<T>& list){
    if(r == nullptr){
        if(list.size()>-1){
            ofstream archive("/Users/oscarsandoval/Desktop/indices/Tree.txt",ios::out);
            for(int i=0;i<=list.size();++i){
                archive.write((char*)&list[i], sizeof(T));
            }
            archive.close();
        }
        return;
    }
    saveTree(r->getLeft(), list);
    list.insertData(list.getLastPos(),r->getData());
    saveTree(r->getRight(), list);
}
template<typename T>
bool BTree<T>::isEmpty() const
{
    return root == nullptr;
}

template<typename T>
bool BTree<T>::isLeaf(BTree::Node *&r) const
{
    return r != nullptr && r->getLeft() == r->getRight();
    
}

template<typename T>
void BTree<T>::insertData(const T &e)
{
    insertData(root, e,root);
}

template<typename T>
void BTree<T>::deleteData(BTree::Node *&r)
{
    if(r==nullptr){
        throw Exception("Oaa");
    }
      Node* aux(nullptr);
    if(isLeaf(r)){
        if(r->getFather()!=nullptr){
            if(r->getFather()->getData()<r->getData()){
                r->getFather()->setRight(aux);
            }else{
                r->getFather()->setLeft(aux);
            }
        }
        delete r;
        r = nullptr;
        return;
    }
   else if(r->getRight()==nullptr){
        delete r;
        r = r->getLeft();
        
    }
    else if(r->getLeft()==nullptr){
        delete r;
        r = r->getRight();
   
    }else{
        Node* h(getLowest(r->getRight()));
        cout<<h->getFather()->getData();cin.get();
       // h->getFather()->setLeft(au);
        if(h->getFather()->getData()<r->getData()){
            h->getFather()->setRight(aux);
        }else{
             h->getFather()->setLeft(aux);
        }
        r->setData(h->getData());
        delete h;
        h = nullptr;
    }
    doBalancing(r);
}

template<typename T>
typename BTree<T>::Node *&BTree<T>::findData(const T &e)
{
    return findData(root, e);
}

template<typename T>
T &BTree<T>::retrieve(BTree::Node *&r)
{
    if (r == nullptr) {
        throw Exception("Posición invalida, retrieve");
    }
    
    return r->getData();
}

template<typename T>
void BTree<T>::parsePreOrder()
{
    parsePreOrder(root);
}

template<typename T>
void BTree<T>::parseInOrder()
{
    parseInOrder(root);
}

template<typename T>
void BTree<T>::parsePostOrder()
{
    parsePostOrder(root);
}

template<typename T>
int BTree<T>::getHeight()
{
    return getHeight(root);
}

template<typename T>
BTree<T> &BTree<T>::operator = (BTree &t)
{
    deleteAll();
    
    copyAll(t.root, root);
    
    return *this;
}

template<typename T>
void BTree<T>::deleteAll()
{
    deleteAll(root);
    size = 0;
}

template <typename T>
bool BTree<T>::isValidInsert(Node *&r,T& data){
    if(r==nullptr){
        return true;
    }
    if(r->getData()==data){
        return false;
    }
    isValidInsert(r->getLeft(), data);
    isValidInsert(r->getRight(), data);
    return false;
}

template <typename T>
bool BTree<T>::isValidInsert(T & data){
    return isValidInsert(root, data);
}

template <typename T>
T BTree<T>::getLowestRaking(){
    T aux(root->getData());
    getLowestRaking(root, aux);
    return aux;

}

template <typename T>
void BTree<T>::getLowestRaking(Node *&r, T&d){
    if(r == nullptr){
        return;
    }
    if(r->getData().getRaking() < d.getRaking()){
        d = r->getData();
    }
    getLowestRaking(r->getLeft(), d);
    getLowestRaking(r->getRight(), d);
}

template <typename T>
void BTree<T>::printTree(){
    printTree(root, 0);
}

template <typename T>
void BTree<T>::printTree(Node *& r, int c){
    if(r==nullptr){
        return;
    }
    printTree(r->getRight(), c+1);
    for(int i = 0;i<c;i++){
        cout<<"   ";
    }
    cout<<r->getData().getKey()<<"/"<<r->getData().getRaking()<<endl;
    printTree(r->getLeft(), c+1);
}

template <typename T>
void BTree<T>::getElements(List<T> &l){
    getElements(l, root);
}

template <typename T>
void BTree<T>::getElements(List<T> & l , Node *& r){
    if (r == nullptr) {
        return;
    }
    l.insertData(l.getLastPos(), r->getData());
    getElements(l,r->getLeft());
    getElements(l,r->getRight());
   
    
}
#endif /* bTree_h */
