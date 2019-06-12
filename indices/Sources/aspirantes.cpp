//
//  Aspirantes.cpp
//  indices
//
//  Created by Oscar Sandoval on 2/9/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#include "aspirantes.hpp"
#include <stdexcept>
#include <fstream>
#include <sstream>

Aspirantes::Aspirantes(List<Indices>& list){
    system("clear");
    ifstream archive("/Users/oscarsandoval/Desktop/indices/indices.txt");
    list.deleteAll();
    if(!archive.good()){
        return;
    }
    while(!archive.eof()){
        archive.read((char*)&indice,sizeof(indice));
        if(archive.eof())break;
        list.insertData(list.getLastPos(),indice);
    }
    archive.close();
}

Aspirantes::Aspirantes(BTree<Indices>& tree):indice(tree){
    system("clear");
    ifstream archive("/Users/oscarsandoval/Desktop/indices/indices/size.txt");
    if(!archive.good()){
        size=0;
        return;
    }
    archive.read((char*)&size, sizeof(int));
    archive.close();
    archive.open("/Users/oscarsandoval/Desktop/indices/Tree.txt");
    if(!archive.good()){
        return;
    }
    List<Indices> list;
    while(!archive.eof()){
        archive.read((char*)&indice, sizeof(indice));
        if(archive.eof())break;
        list.insertData(list.getLastPos(), indice);
    }
    archive.close();
    for(int i = 0; i<=list.size();++i){
        tree.insertData(list[i]);
    }

    if(getSize()!=tree.Size()){
        system("clear");
        cout<<"Alert Constructor"<<endl;
        cin.get();
    }
}

Aspirantes::~Aspirantes(){
    if(size>0){
        ofstream archive("/Users/oscarsandoval/Desktop/indices/indices/size.txt",ios::out);
        archive.write((char*)&size, sizeof(int));
        archive.close();
    }
}

bool Aspirantes::isValidCurp(List<Indices>& list,std::string &user){
    indice.setKey(user);
    try{
        list.retrieve(list.findData(indice));
    }catch(ListException& ex){
        return true;
    }
    return false;
}

bool Aspirantes::isValidCurp(std::string & user){
    ifstream archive("/Users/oscarsandoval/Desktop/indices/indices.txt");
    if(!archive.good()){
        return true;
    }
    while(!archive.eof()){
        archive.read((char*)&indice, sizeof(indice));
        if(archive.eof())break;
        if(indice.getKey() == user){
            return false;
        }
    }
    return true;
}

//Setters
void Aspirantes::setCurp(List<Indices>& list ,std::string & curp){
    if(curp.length()>4 && curp.length()<3){
        throw invalid_argument("Curp no valido\n La curp debe contener 4 caracteres");
    }
    if(!isValidCurp(list,curp)){
        throw invalid_argument("Curp no valido");
    }
    for(int i=0;i<5;i++)
        this->aspirante.curp[i]='\0';
    for(int i=0;curp[i];i++)
        this->aspirante.curp[i]=curp[i];
}

void Aspirantes::setName(std::string & name){
    for(int i=0;i<20;i++)
        this->aspirante.name[i]='\0';
    for(int i=0;name[i];i++)
        this->aspirante.name[i]=name[i];
    
}

void Aspirantes::setCurp(std::string & curp){
    if(!isValidCurp(curp)){
        throw invalid_argument("Curp no valido");
    }
    for(int i=0;i<5;i++)
        this->aspirante.curp[i]='\0';
    for(int i=0;curp[i];i++)
        this->aspirante.curp[i]=curp[i];
}

void Aspirantes::setAge(std::string & age){
    try{
        this->aspirante.age=stoi(age);
    }catch(invalid_argument& ex){
        throw invalid_argument(ex.what());
    }
    if(aspirante.age<1||aspirante.age>99)
        throw invalid_argument("Edad no permitida\n");
}

void Aspirantes::setStall(std::string & stall){
    try{
        this->aspirante.stall=stoi(stall);
    }catch(invalid_argument& ex){
        throw invalid_argument(ex.what());
    }
}

//Getters
std::string Aspirantes::getCurp(){
    return aspirante.getCurp();
}

string Aspirantes::getName(){
    string myStr;
    for(int i=0;aspirante.name[i];i++)
        myStr+=aspirante.name[i];
    return myStr;
}

int Aspirantes::getAge(){
    return aspirante.age;
}

int Aspirantes::getStall(){
    return aspirante.stall;
}

void Aspirantes::insert(List<Indices>& list){
    ofstream archive("/Users/oscarsandoval/Desktop/indices/Aspirantes.txt",ios::app);
    indice.setAddress(archive.tellp());
    indice.setKey(getCurp());
    list.insertData(list.getLastPos(),indice);
    aspirante.active=1;
    archive.write((char*)&aspirante,sizeof(aspirante));
    archive.close();
}

void Aspirantes::print(){
    ifstream archive("/Users/oscarsandoval/Desktop/indices/Aspirantes.txt");
    if(!archive.good()){
        cout<<"No hay aspirantes registrados"<<endl;
        return;
    }
    while(!archive.eof()){
        archive.read((char*)&aspirante,sizeof(aspirante));
        if(archive.eof())break;
        if(aspirante.active==1){
            cout<<"Nombre : "<<aspirante.name<<endl;
            cout<<"Curp : "<<aspirante.curp<<endl;
            cout<<"Edad : "<<aspirante.age<<endl;
            cout<<"Puesto : "<<aspirante.stall<<endl<<endl<<endl;
        }
    }
    archive.close();
}

void Aspirantes::search(List<Indices> &list, std::string&user){
    indice.setKey(user);
    try{
       indice = list.retrieve(list.findData(indice));
    }catch(ListException & ex){
        throw invalid_argument(ex.what());
    }
    ifstream archive("/Users/oscarsandoval/Desktop/indices/Aspirantes.txt");
    archive.seekg(indice.getAddress());
    archive.read((char*)&aspirante,sizeof(aspirante));
    cout<<"\t\tAspirante encontrado : "<<endl;
    cout<<aspirante<<endl;
    archive.close();
}

void Aspirantes::modify(List<Indices> &list,string& user){
    indice.setKey(user);
    try{
        indice = list.retrieve(list.findData(indice));
    }catch(ListException& ex){
        throw invalid_argument(ex.what());
    }
    fstream archive("/Users/oscarsandoval/Desktop/indices/Aspirantes.txt",ios::in|ios::out);
    string myStr;
    archive.seekg(indice.getAddress());
    archive.read((char*)&aspirante,sizeof(Aspirante));
    if(aspirante.active==0){
        throw invalid_argument("Usuario no encontrado\n");
    }
    do{
        cout<<"\t\tModificar Aspirante"<<endl
        <<"1)Nombre"<<endl
        <<"2)Curp"<<endl
        <<"3)Edad"<<endl
        <<"4)Puesto"<<endl
        <<"5)Regresar"<<endl
        <<"Elige una opcion : ";
        getline(cin,myStr);
        if(myStr=="1"){
            cout<<"\t\tModificar Nombre : "<<endl
            <<"\tNombre actual : "<<getName()<<endl
            <<"Nuevo nombre : ";
            getline(cin,myStr);
            for(int i = 0;myStr[i];++i)
                myStr[i] = toupper(myStr[i]);
            setName(myStr);
        }
        else if(myStr=="2"){
            bool band;
            do{
                band=false;
                cout<<"\t\tModificar curp : "<<endl
                <<"\tCurp actual : "<<getName()<<endl;
                cout <<"Nueva Curp : ";
                getline(cin,myStr);
                for(int i = 0;myStr[i];++i)
                    myStr[i] = toupper(myStr[i]);
                try{
                    setCurp(list,myStr);
                }catch(invalid_argument & ex){
                    system("clear");
                    cerr<<"Curp no valida, intente de nuevo"<<endl;
                    band=true;
                }
            }while(band==true);
            indice.setKey(user);
            Node<Indices>* aux;
            try{
                aux=list.getPrevPos(list.findData(indice));
                list.deleteData(list.findData(indice));
            }catch(ListException& ex){
                cerr<<ex.what()<<"Pero ya la libro ufff!!"<<endl;
            }
            indice.setKey(getCurp());
            list.insertData(aux,indice);
        }
        else if(myStr=="3"){
            bool band;
            do{
                band=false;
                cout<<"\t\tModificar Edad : "<<endl
                <<"\tEdad actual : "<<getName()<<endl
                <<"Edad : ";
                getline(cin,myStr);
                try{
                    setAge(myStr);
                }catch(invalid_argument& ex){
                    system("clear");
                    cerr<<ex.what()<<endl;
                    band=true;
                }
            }while(band==true);
        }
        else if(myStr=="4"){
            bool band;
            do{
                band=false;
                cout<<"\t\tModificar Puesto : "<<endl
                <<"\tPuesto actual : "<<getStall()<<endl
                <<" Nuevo Puesto : ";
                getline(cin,myStr);
                try{
                    setStall(myStr);
                }catch(invalid_argument& ex){
                    system("clear");
                    cerr<<ex.what()<<endl;
                    band=true;
                }
            }while(band==true);
        }
        else if(myStr=="5"){
            break;
        }
        else{
            system("clear");
            cout<<"Ingrese un caracter valido"<<endl;
        }
    }while(myStr!="5");
    archive.seekg(indice.getAddress());
    archive.write((char*)&aspirante,sizeof(aspirante));
    archive.close();
    cout<<"Informacion actualizada"<<endl;
}

void Aspirantes::logicRemove(List<Indices>& list,string &user){
    indice.setKey(user);
    try{
        indice = list.retrieve(list.findData(indice));
    }catch(ListException& ex){
        throw invalid_argument(ex.what());
    }
    fstream archive("/Users/oscarsandoval/Desktop/indices/Aspirantes.txt",ios::in|ios::out);
    string myStr;
    archive.seekg(indice.getAddress());
    archive.read((char*)&aspirante,sizeof(Aspirante));
    if(aspirante.active==1){
        aspirante.active=0;
        archive.seekg(indice.getAddress());
        archive.write((char*)&aspirante,sizeof(aspirante));
        archive.close();
        system("clear");
        cout<<"Usuario eliminado"<<endl;
        return;
    }
    archive.close();
    system("clear");
    cout<<"Usuario no encontrado"<<endl;
}

void Aspirantes::remove(List<Indices> & list, std::string& user){
    indice.setKey(user);
    try{
        indice = list.retrieve(list.findData(indice));
    }catch(ListException& ex){
        throw invalid_argument(ex.what());
    }
    ifstream read("/Users/oscarsandoval/Desktop/indices/Aspirantes.txt");
    ofstream writer("/Users/oscarsandoval/Desktop/indices/Aux.txt",ios::out);
    list.deleteAll();
    while(!read.eof()){
        read.read((char*)&aspirante, sizeof(aspirante));
        if(read.eof())break;
        if(aspirante.curp==user){
            if(aspirante.active==1){
                cout<<"Usuario eliminado"<<endl;
            }
            else{
                indice.setKey(getCurp());
                indice.setAddress(writer.tellp());
                writer.write((char*)&aspirante,sizeof(aspirante));
                list.insertData(list.getLastPos(),indice);
            }
        }
        else{
            indice.setKey(getCurp());
            indice.setAddress(writer.tellp());
            writer.write((char*)&aspirante,sizeof(aspirante));
            list.insertData(list.getLastPos(),indice);
        }
    }
    read.close();
    writer.close();
    std::remove("/Users/oscarsandoval/Desktop/indices/Aspirantes.txt");
    rename("/Users/oscarsandoval/Desktop/indices/Aux.txt","/Users/oscarsandoval/Desktop/indices/Aspirantes.txt");
}

void Aspirantes::active(List<Indices> & list, std::string &user){
    indice.setKey(user);
    try{
        indice = list.retrieve(list.findData(indice));
    }catch(ListException& ex){
        throw invalid_argument(ex.what());
    }
    fstream archive("/Users/oscarsandoval/Desktop/indices/Aspirantes.txt",ios::in|ios::out);
    string myStr;
    archive.seekg(indice.getAddress());
    archive.read((char*)&aspirante,sizeof(Aspirante));
    if(aspirante.active==0){
        aspirante.active=1;
        archive.seekg(indice.getAddress());
        archive.write((char*)&aspirante,sizeof(aspirante));
        archive.close();
        system("clear");
        cout<<"Usuario Activado"<<endl;
        return;
    }
    archive.close();
    system("clear");
    cout<<"Usuario no encontrado "<<endl;
}

void Aspirantes::Sort(List<Aspirante>& list){
    ifstream read("/Users/oscarsandoval/Desktop/indices/Aspirantes.txt");
    list.deleteAll();
    if(!read.good()){
        throw invalid_argument("No hay aspirantes registrados\n");
    }
    while(!read.eof()){
        read.read((char*)&aspirante,sizeof(aspirante));
        if(read.eof())break;
        if(aspirante.active==1){
            list.insertData(list.getLastPos(),aspirante);
        }
    }
    read.close();
    list.Sort();
    //quickSort(list,0,list.size());
}

void Aspirantes::quickSort(List<Aspirante> &list, int extizq, int extDer){
    int i,j,pivote;
    Aspirante aux;
    if(extizq>=extDer)
        return;
    pivote=(extizq+extDer)/2;
    aux=list[pivote];
    list[pivote]=list[extDer];
    list[extDer]=aux;
    i=extizq;
    j=extDer;
    while(i<j){
        while(i<j&&list[i]<=list[extDer])
            i++;
        while(i<j&&list[j]>=list[extDer])
            j--;
        if(i<j){
            aux=list[i];
            list[i]=list[j];
            list[j]=aux;
        }
    }
    if(i<extDer){
        aux=list[i];
        list[i]=list[extDer];
        list[extDer]=aux;
    }
    quickSort(list,extizq,i-1);
    quickSort(list,i+1,extDer);
}
void Aspirantes::save(List<Indices> &list){
    indice.save(list);
}

int Aspirantes::getSize(){
    return size*0.20;
}

void Aspirantes::insert(BTree<Indices> & tree){
    ofstream archive("/Users/oscarsandoval/Desktop/indices/Aspirantes.txt",ios::app);
    indice.setAddress(archive.tellp());
    indice.setKey(aspirante.getCurp());
  //  list.insertData(list.getLastPos(),indice);
    aspirante.active=1;
    archive.write((char*)&aspirante,sizeof(aspirante));
    archive.close();
    archive.open("/Users/oscarsandoval/Desktop/indices/indices.txt",ios::app);
    archive.write((char*)&indice,sizeof(indice));
    archive.close();
    size++;
    if(getSize()>tree.Size()){
        tree.insertData(indice);
    }
}

void Aspirantes::search(BTree<Indices>& tree, std::string &user){
    indice.setKey(user);
    try{
        indice = tree.retrieve(tree.findData(indice));//list.retrieve(list.findData(indice));
    }catch(BTree<Indices>::Exception & ex){
        List<Indices> list;
        Indices remove;
        cout<<"El registro no se encuentra en el arbol de busqueda : "<<endl;
        ifstream archive("/Users/oscarsandoval/Desktop/indices/Indices.txt");
        long pos;
        while(!archive.eof()){
            pos = archive.tellg();
            archive.read((char*)&indice, sizeof(indice));
            if(archive.eof())break;
            if(indice.getKey() == user){
                cout<<"Indice agregado al Arbol : "<<endl;
                tree.getElements(list);
                remove = tree.getLowestRaking();
                tree.deleteAll();
                for(int i = 0; i<=list.size();i++){
                    if(list[i]==remove){
                        
                    }else{
                        tree.insertData(list[i]);
                    }
                }
                indice.setRaking(1);
                tree.insertData(indice);
                archive.close();
                break;
            }
        }
        if(indice.getKey() != user)
            throw invalid_argument(" No se encontro ningun registro con esa curp\n");
    }
    //Falta aumentar el raking
    ifstream archive("/Users/oscarsandoval/Desktop/indices/Aspirantes.txt");
    archive.seekg(indice.getAddress());
    archive.read((char*)&aspirante,sizeof(aspirante));
    cout<<"\t\tAspirante encontrado dentro del arbol :  : "<<endl;
    cout<<aspirante<<endl;
    archive.close();
}

void Aspirantes::remove(BTree<Indices> & tree, std::string &user){
    indice.setKey(user);
    try{
        indice = tree.retrieve(tree.findData(indice));
    }catch(BTree<Indices>::Exception & ex){
        ifstream archive("/Users/oscarsandoval/Desktop/indices/indices.txt");
        while(!archive.eof()){
            archive.read((char*)&indice, sizeof(indice));
            if(archive.eof())break;
            if(indice.getKey() == user){
                remove(indice);
                throw invalid_argument("El registro fue eliminado, no se encontraba en el arbol");
            }
        }
        archive.close();
        if(indice.getKey()!=user)
            throw invalid_argument("No se encontro ningun registro con ese curp");
    }
    ifstream archive("/Users/oscarsandoval/Desktop/indices/indices.txt");
    List<Indices> list;
    tree.getElements(list);
    tree.deleteAll();
    for(int i=0;i<=list.size();i++){
        if(list[i]==indice){
            
        }else{
            tree.insertData(list[i]);
        }
    }
    remove(indice);
    while(getSize()>tree.Size()&&!archive.eof()){
        archive.read((char*)&indice, sizeof(indice));
        if(archive.eof())break;
        if(tree.isValidInsert(indice)){
            tree.insertData(indice);
        }
    }
    if(getSize()<tree.Size()){
        Indices aux;
        list.deleteAll();
        tree.getElements(list);
        aux = tree.getLowestRaking();
        tree.deleteAll();
        for(int i=0;i<=list.size();i++){
            if(aux == list[i]){
                
            }else{
                tree.insertData(list[i]);
            }
        }
    }
}


void Aspirantes::remove(Indices & r){
    cout<<r.getKey()<<endl;cin.get();
    ifstream archive("/Users/oscarsandoval/Desktop/indices/Aspirantes.txt");
    ofstream aux("/Users/oscarsandoval/Desktop/indices/Aux.txt",ios::out);
    size--;
    string a,b;
    while(!archive.eof()){
        archive.read((char*)&aspirante, sizeof(aspirante));
        if(archive.eof())break;
        if(aspirante.getCurp()==r.getKey()){
        }
        else{
            aux.write((char*)&aspirante, sizeof(aspirante));
        }
    }
    archive.close();
    aux.close();
    std::remove("/Users/oscarsandoval/Desktop/indices/Aspirantes.txt");
    rename("/Users/oscarsandoval/Desktop/indices/Aux.txt","/Users/oscarsandoval/Desktop/indices/Aspirantes.txt");
    r.remove(r.getKey());
}

void Aspirantes::printIndices(){
    ifstream archive("/Users/oscarsandoval/Desktop/indices/indices.txt");
    if(!archive.good()){
        cout<<"No hay aspirantes registrados"<<endl;
        return;
    }
    while(!archive.eof()){
        archive.read((char*)&indice,sizeof(indice));
        if(archive.eof())break;
        cout<<indice;
    }
    archive.close();
}
