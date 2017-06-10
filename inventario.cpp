#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <string.h>
using namespace std;

//estructuras para arbol de clientes
struct nodo{
	int id;
	int nit;
	char nombre[25];
	char direccion[25];
	nodo *der;
	nodo *izq;
	nodo *padre;	
};

//prototipos de funcioes
void menu();
nodo *nuevonodo(int,int,char,char,nodo *); //funcion para crear nodos nuevos
void insertarCliente(nodo *&,int,int,char[25],char[25],nodo *);
void mostrarClientes(nodo *);


//definicion de los arboles
nodo *arbol =NULL;

//FUNCION MAIN
int main(){
	
	menu();
	return 0;
}



//funcion para el menu
void menu(){
	int opcion=0;
	do{
	system("cls");	
	cout<<"---------------> M E N U <-------------------"<<endl;
	cout<<endl<<"	CLIENTES: "<<endl;
	cout<<"		1. Mostrar clientes"<<endl;
	cout<<"		2. Ingresar clientes"<<endl;
	cout<<endl<<"	PROVEEDORES: "<<endl;
	cout<<"		3. Mostrar proveedores"<<endl;
	cout<<"		4. Ingresar proveedores"<<endl;
	cout<<endl<<"	VENTAS:"<<endl;
	cout<<"		5. Mostar"<<endl;
	cout<<"		6. Vender"<<endl;
	cout<<endl<<"	PRODUCTOS"<<endl;
	cout<<"		7. Mostar"<<endl;
	cout<<"		8. Ingresar"<<endl;
	cout<<" 	9. SALIR"<<endl;
	cout<<endl<<"seleccione una opcion: "; cin>>opcion;
	
		switch(opcion){
			case 1:{
				//mostrar los clientes
				system("cls");
				cout<<" 		MOSTANDO CLIENTES EXISTENTES"<<endl;
				mostrarClientes(arbol);
				system("pause");
				break;
			}
			
			case 2:{
				//ingresar clientes
				int nit,id;
				//se utilizara la funcion rand para generar numeros aleatorios
				srand(time(NULL)); //inicializa la semilla en 0
				id=rand()%101;
				char nombre[25], direccion[25];
				system("cls");
				cout<<"		INGRESANDO CLIENTES"<<endl;
				cout<<"el ID del cliente es: "<<id<<endl;
				cout<<"ingrese NIT: "; cin>>nit;
				cout<<"ingrese NOMBRE: "; fflush(stdin) ; gets(nombre);
				cout<<"ingrese DIRECCION: "; gets(direccion);
				//ya tenemos todos los datos del cliente, ahora llamamos a la funcion nuevo nodo
				insertarCliente(arbol,id,nit,nombre,direccion,NULL);
				system("pause");
				break;
			}
				
		}//cierra el switch
		
	}while(opcion!=9);
} //cierra la funcion menu

//funcion para crear nodo
nodo *nuevonodo(int id, int nit, char nombre[25], char direccion[25], nodo *padre){
	
    nodo *nuevo_nodo = new nodo();
	
	nuevo_nodo->id = id;
	nuevo_nodo->nit = nit;
	//nuevo_nodo->nombre = nombre;
	strcpy(nuevo_nodo->nombre, nombre);
	//nuevo_nodo->direccion = direccion;
	strcpy(nuevo_nodo->direccion,direccion);
	nuevo_nodo->der = NULL;
	nuevo_nodo->izq = NULL;
	nuevo_nodo->padre = padre;
	
	return nuevo_nodo;
}

//Funcion para insertar elementos en el arbol
void insertarCliente(nodo *&arbol,int id, int nit, char nombre[25], char direccion[25], nodo *padre){
	if(arbol == NULL){ //Si el arbol esta vacio
		nodo *nuevo_nodo = nuevonodo(id,nit,nombre,direccion,padre);
		arbol = nuevo_nodo;
	}
	else{ //Si el arbol tiene un nodo o mas
		int valorRaiz = arbol->id; //Obtenemos el valor de la raiz
		if(id < valorRaiz){ //Si el elemento es menor a la raiz, insertamos en izq
			insertarCliente(arbol->izq,id,nit,nombre,direccion,arbol);
		}
		else{//Si el elemento es mayor a la raiz, insertamos en der
			insertarCliente(arbol->der,id,nit,nombre,direccion,arbol);
		}	
	}
}


//Funcion para mostrar el arbol clientes
void mostrarClientes(nodo *arbol){
	if(arbol == NULL){ //Si el arbol esta vacio
		return;
	}
	else{
		mostrarClientes(arbol->der);
		cout<<"identificar: "<<arbol->id<<endl;
		cout<<"NIT: "<<arbol->nit<<endl;
		cout<<"NOMBRE: "<<arbol->nombre<<endl;
		cout<<"DIRECCION: "<<arbol->direccion<<endl<<endl;
		mostrarClientes(arbol->izq);
	}
}


