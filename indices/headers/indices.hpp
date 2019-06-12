//
//  indices.hpp
//  indices
//
//  Created by Oscar Sandoval on 2/9/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef indices_hpp
#define indices_hpp
#include <iostream>
#include "list.hpp"
#include "bTree.hpp"
class Indices{
private:
    long address;
    int key;
    int raking;
public:
    Indices();
    
    Indices(BTree<Indices>&);
    //Setters
    void setAddress(long);
    void setKey(std::string);
    void setRaking(int);
    //Getters
    long getAddress();
    std::string getKey();
    int getRaking();
//Sobre carga de operadores
    bool operator > (Indices&)const;
    bool operator < (const Indices&)const;
    bool operator >= (const Indices&)const;
    bool operator <= (const Indices&)const;
    bool operator == (const Indices&)const;
    Indices operator = (const Indices&);
    void save(List<Indices>&);
    void remove(std::string);
    friend std::ostream& operator << (std::ostream& os, Indices& c){
        os<<"Curp : "<<c.getKey()<<endl;
        os<<"Direccion : "<<c.getAddress()<<endl<<endl;
        return os;
    }
};

#endif /* indices_hpp */
