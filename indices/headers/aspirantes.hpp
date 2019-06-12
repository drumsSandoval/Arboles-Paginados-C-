//
//  Aspirantes.hpp
//  indices
//
//  Created by Oscar Sandoval on 2/9/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef Aspirantes_hpp
#define Aspirantes_hpp
#include "indices.hpp"
class Aspirante{
public:
    int active;
    int stall;
    int age;
    char curp[5];
    char name[20];
    string getCurp(){
        string mystr;
        for(int i =0;curp[i];i++)
            mystr+=curp[i];
        return mystr;
    }
    bool operator > (Aspirante& a)const{
        //return curp[0]<a.curp[0];
        string b;
        for(int i =0;i<5;i++)
            b+=curp[i];
        if(b>a.getCurp())
            return true;
        return false;
    }
    bool operator < (const Aspirante& a)const{
        //return curp[0]>a.curp[0];
        if(strcmp(curp,a.curp)<0)
            return true;
        return false;
    }
    bool operator >= (const Aspirante& a)const{
        //return curp[0]<=a.curp[0];
        if(strcmp(curp,a.curp)>0)
            return true;
        return false;
    }
    bool operator <= (const Aspirante& a)const{
        //return curp[0]>=a.curp[0];
        if(strcmp(curp,a.curp)<0)
            return true;
        return false;
    }
    bool operator == (const Aspirante& a)const{
        if(strcmp(curp,a.curp)==0)
            return true;
        return false;
    }
    Aspirante operator = (const Aspirante& a){
        active=a.active;
        stall=a.stall;
        age=a.age;
        strcpy(curp,a.curp);
        strcpy(name,a.name);
        return *this;
    }
    friend std::ostream& operator << (std::ostream& os, Aspirante& c){
        os<<"Nombre : "<<c.name<<endl;
        os<<"Curp : "<<c.curp<<endl;
        os<<"Edad : "<<c.age<<endl;
        os<<"Puesto : "<<c.stall<<endl;
        return os;
    }
};
class Aspirantes{
private:
    Aspirante aspirante;
    Indices indice;
    size_t size;
    
    void remove(Indices&);
public:
    Aspirantes(List<Indices>&);
    
    Aspirantes(BTree<Indices>&);
    
    ~Aspirantes();
    //Setters
    void setCurp(List<Indices>&,std::string&);
    void setCurp(std::string&);
    void setName(std::string&);
    void setAge(std::string&);
    void setStall(std::string&);
    //Validaciones
    bool isValidCurp(List<Indices>&,std::string&);
    bool isValidCurp(std::string&);
    //Getters
    std::string getCurp();
    std::string getName();
    int getAge();
    int getStall();
    /////////////////////            Metodos que llevan list ///////////////////////////////////
    //Metodos chingones
    void insert(List<Indices>&);
    void print();
    void search(List<Indices>&, std::string&);
    void Sort(List<Aspirante>&);
    void quickSort(List<Aspirante>&,int,int);
    void modify(List<Indices>&,std::string&);
    void save(List<Indices>&);
    //Eliminaciones
    void logicRemove(List<Indices>&,std::string&);
    void remove(List<Indices>&,std::string&);
    void active(List<Indices>&,std::string&);
    Aspirantes operator = (const Aspirantes&);
    //////////////////////////// METODOS CON ARBOL BINARIO ///////////////////////////////
    void insert(BTree<Indices>&);
    void search(BTree<Indices>&,std::string&);
    void remove(BTree<Indices>&,std::string&);
    
    void printIndices();
    /////////
    int getSize();
};
#endif /* Aspirantes_hpp */
