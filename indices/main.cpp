//
//  main.cpp
//  indices
//
//  Created by Oscar Sandoval on 2/9/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#include "aspirantes.hpp"
int main(int argc, const char * argv[]) {
    //List<Indices> list;
    BTree<Indices> tree;
    Indices a;
    /*
    for(int i = 0;i<6;i++){
        a.setKey(to_string(i));
        tree.insertData(a);
    }
    tree.printTree();
    
    cin.get();*/
    Aspirantes aspirantes(tree);
    bool band;
    string myStr;
    do{
        cout<<"\t\t\tMenu : "<<endl
        <<"\t1)Agregar"<<endl
        <<"\t2)Imprimir TDA"<<endl
        /*"\t3)Consultar"<<endl*/
        /*
        <<"\t4)Mostrar Ordenado"<<endl
        <<"\t5)Modificar"<<endl
         */
        <<"\t3)Buscar"<<endl
        <<"\t4)Mostrar todos los registros"<<endl
        <<"\t5)Mostrar indices  "<<endl
        <<"\t6)Eliminar"<<endl
        /*"\t7)Activar Aspirante"endl*/
        <<"\t7)Salir"<<endl
        <<"\tElige una opcion : ";
        getline(cin, myStr);
        if(myStr=="1"){
            system("clear");
            cout<<"Agregar aspirante : "<<endl
            <<"Nombre del aspirante  : ";
            getline(cin,myStr);
            for(int i = 0;myStr[i];++i)
                myStr[i] = toupper(myStr[i]);
            aspirantes.setName(myStr);
            do{
                band=false;
                cout<<"Curp : ";
                getline(cin,myStr);
                for(int i = 0;myStr[i];++i)
                    myStr[i] = toupper(myStr[i]);
                try{
                aspirantes.setCurp(myStr);
                }catch(invalid_argument& ex){
                    system("clear");
                    cerr<<ex.what()<<endl;
                    band=true;
                }
            }while(band==true);
            do{
                band=false;
                cout<<"Edad : ";
                getline(cin,myStr);
                try{
                    aspirantes.setAge(myStr);
                }catch(invalid_argument& ex){
                    system("clear");
                    cerr<<ex.what()<<endl;
                    band=true;
                }
            }while(band==true);
            do{
                band=false;
                cout<<"Puesto : ";
                getline(cin,myStr);
                try{
                    aspirantes.setStall(myStr);
                }catch(invalid_argument& ex){
                    system("clear");
                    cerr<<ex.what()<<endl;
                    band=true;
                }
            }while(band==true);
            aspirantes.insert(tree);
            myStr="1";
        }
        else if(myStr=="2"){
            system("clear");
            //list.printData();
            tree.printTree();
            //Imprimir Arbol
            
        }
        else if(myStr=="3"){
            system("clear");
            cout<<"\t\tConsultar"<<endl
            <<"Curp de aspirante : ";
            getline(cin,myStr);
            for(int i = 0;myStr[i];++i)
                myStr[i] = toupper(myStr[i]);
            try{
                aspirantes.search(tree, myStr);
            }catch(invalid_argument& ex){
                system("clear");
                cerr<<ex.what()<<endl;
            }
        }
        else if(myStr=="4"){
            system("clear");
            aspirantes.print();
        }
        else if(myStr=="5"){
            system("clear");
            aspirantes.printIndices();
        }
        else if(myStr=="6"){
            system("clear");
            cout<<"\t\t\tEliminar Aspirante"<<endl;
            cout<<"Curp : ";
            getline(cin,myStr);
            for(int i = 0;myStr[i];++i)
                myStr[i] = toupper(myStr[i]);
            try{
                aspirantes.remove(tree, myStr);
            }catch(invalid_argument& ex){
                system("clear");
                cout<<ex.what()<<endl;
            }
        }
        /*
        else if(myStr=="4"){
            system("clear");
            band=false;
            List<Aspirante> list2;
            try{
                aspirantes.Sort(list2);
            }catch(invalid_argument& ex){
                band=true;
                system("clear");
                cerr<<ex.what()<<endl;
            }
            if(band==false){
                list2.desendentPrint();
                list2.deleteAll();
            }
        }
        else if(myStr=="5"){
            system("clear");
            cout<<"\t\t\tModificar : "<<endl
            <<"Curp del aspirante : ";
            getline(cin, myStr);
            for(int i = 0;myStr[i];++i)
                myStr[i] = toupper(myStr[i]);
            try{
                aspirantes.modify(list,myStr);
            }catch(invalid_argument& ex){
                system("clear");
                cout<<"No se encontro ningun resultado"<<endl;
            }
        }
        else if(myStr=="6"){
            system("clear");
            cout<<"\t\t\tEliminar Aspirante"<<endl;
            cout<<"Curp : ";
            getline(cin,myStr);
            for(int i = 0;myStr[i];++i)
                myStr[i] = toupper(myStr[i]);
            string aux;
            do{
                band=false;
                cout<<"1)Eliminacion Logica"<<endl
                <<"2)Eliminacion Fisica"<<endl
                <<"3)Regresar"<<endl
                <<"Elige una opcion : ";
                getline(cin,aux);
                if(aux=="1"){
                    try{
                        aspirantes.logicRemove(list,myStr);
                    }catch(invalid_argument& ex){
                        system("clear");
                        cout<<"Aspirante no encontrado"<<endl;
                    }
                }
                else if(aux=="2"){
                    try{
                        aspirantes.remove(list, myStr);
                    }catch(invalid_argument& ex){
                        system("clear");
                        cout<<"Aspirante no encontrado"<<endl;
                    }
                }
                else if(aux=="3"){
                    system("clear");
                }
                else{
                    system("clear");
                    band=true;
                }
            }while(band==true);
        }
        else if(myStr=="7"){
            system("clear");
            cout<<"\t\tActivar Aspirante"<<endl
            <<"Curp del aspirante : ";
            getline(cin,myStr);
            for(int i = 0;myStr[i];++i)
                myStr[i] = toupper(myStr[i]);
            try{
                aspirantes.active(list,myStr);
            }catch(invalid_argument& ex){
                system("clear");
                cout<<"Usuario no encontrado"<<endl;
            }
        }*/
        else if(myStr=="7"){
            //aspirantes.save(list);
            cout<<"Adios vaquero"<<endl;
        }
    }while(myStr!="7");
    return 0;
}
