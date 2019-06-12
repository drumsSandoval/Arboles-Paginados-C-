//
//  indices.cpp
//  indices
//
//  Created by Oscar Sandoval on 2/9/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//
#include "indices.hpp"
#include <fstream>

Indices::Indices():raking(0){
    
}

Indices::Indices(BTree<Indices>& tree):raking(0){

    
}
//Setters
void Indices::setAddress(long address){
    this->address=address;
}

void Indices::setKey(std::string keyj){
    key = stoi(keyj);
}

std::string Indices::getKey(){
    string myStr;
    myStr = to_string(key);
    return myStr;
}

long Indices::getAddress(){
    return address;
}

bool Indices::operator>(Indices &i)const{
    return key>i.key;
}

bool Indices::operator<(const Indices &i)const{
    return key<i.key;
}

bool Indices::operator<=(const Indices &i)const{
    return key<=i.key;
}

bool Indices::operator>=(const Indices &i)const{
    return key>=i.key;
}

Indices Indices::operator=(const Indices &i){
    key =i.key;
    address=i.address;
    raking = i.raking;
    return *this;
}

bool Indices::operator==(const Indices &i)const{
    return key == i.key;
}

void Indices::save(List<Indices>& list){
    ofstream archive("/Users/oscarsandoval/Desktop/indices/indices.txt",ios::out);
    int i=0;
    while(i<=list.size()){
        archive.write((char*)&list[i],sizeof(Indices));
        i++;
    }
    archive.close();
}

void Indices::setRaking(int r){
    raking=r;
}

int Indices::getRaking(){
    return raking;
}

void Indices::remove(std::string indice){
    ifstream archive("/Users/oscarsandoval/Desktop/indices/indices.txt");
    ofstream aux("/Users/oscarsandoval/Desktop/indices/aux.txt",ios::out);
    while(!archive.eof()){
        archive.read((char*)&*this, sizeof(Indices));
        if(archive.eof())break;
        if(indice == getKey()){
            
        }else{
            aux.write((char*)&*this, sizeof(Indices));
        }
    }
    archive.close();
    aux.close();
    std::remove("/Users/oscarsandoval/Desktop/indices/indices.txt");
    rename("/Users/oscarsandoval/Desktop/indices/Aux.txt","/Users/oscarsandoval/Desktop/indices/indices.txt");
}
