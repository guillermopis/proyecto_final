#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <iomanip>
using namespace std;
using std::left;
using std::right;


struct ventas{
	int id;
	int total;
	int efectivo;
	int cambio;
	ventas *derecha;
	ventas *izquierda;
	ventas *padre;
};
//estructuras paa productos
struct productos{
	int id;
	char codigo[15];
	char descripcion[25];
	float precio_compra=0.00;
	float precio_venta=0.00;
	int existencia;
	productos *derecha;
	productos *izquierda;
	productos *padre;
};

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

//prototipos de funcioes CLIENTES
void menu();
nodo *nuevonodo(int,int,char,char,nodo *); //funcion para crear nodos nuevos
void insertarCliente(nodo *&,int,int,char[25],char[25],nodo *);
void mostrarClientes(nodo *);
bool buscarCliente(nodo *,int);
void monstrarInformacion();

//prototipos para ventas
void nuevaVenta(int,int,int,int, ventas *);
void insertarVenta(ventas *&,int,int,int,int,ventas *);
void mostrarVenta(ventas *);

//prototipos para productos
void insertarProductos(productos *&,int,char[25],char[25],float,float,int,productos *);
void mostrarProductos(productos *);
nodo *nuevoproducto(int,char[25],char[25],float,float,int, productos *); //funcion para crear nodos nuevos
bool buscarProducto( productos*,int);
//definicion de los arboles BINARIOS
nodo *arbol =NULL;
nodo *clienteEncontrado= NULL;
productos *arbolProductos = NULL;
productos *productoEncontrado =NULL; //guardara el puntero al nodo que contenga el producto buscado.
ventas * arbolVenta = NULL;
//****************************************************************************************************************************
//definicion de lista enlazada para almacenar proveedores
class nodos {
 	//dESDE OTRA CLASE SE PUEDEN acceder a estos atributos
    public:
     nodos(char nom[25], char dire[25], char produ[25], nodos *sig, nodos *ante)
     {
        strcpy(nombre,nom);
        strcpy(direccion,dire);
        strcpy(producto,produ);
        siguiente = sig;
        anterior=ante;
     }
     //Desde otra clase/funcion no de puede acceder a los atributos o metodos privados.
    private:
     char nombre[25];
     char direccion[25];
     char producto[25];
     nodos *siguiente;
     nodos *anterior;
  //Una funcion externa puede acceder a los atributos privados.
    friend class lista;
};
//PROTOTIPOS
 void mostrar();
 nodos *crearnodo(char[25],char[25],char[25],nodos *,nodos *);
 nodos *lista_proveedor = NULL; //incializa el arbol en NULL
 typedef nodos *pnodos;
class lista {
   public:
   	void insertar_prove(nodos *&,char[25],char[25],char[25],nodos *);
    void mostrar_proveedores(nodos *); //funcion para mostrar el arbol con recursividad
   
   private:
    
 };

//**************************************************************************************************************



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
				cout<<" 		MOSTRANDO CLIENTES EXISTENTES"<<endl;
				cout<<left<<setw(8)<<"ID."<<setw(15)<<"NIT"<<setw(15)<<"NOMBRE"<<setw(30)<<"DIRECCION"<<endl;
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
			}//cierra case 3
			case 3:{
				system("cls");
				cout<<"			MOSTRANDO PROVEEDORES"<<endl<<endl;
				lista Lista2;
				Lista2.mostrar_proveedores(lista_proveedor);
				system("pause");
				break;
			}//cierra el case 3
			case 4:{
				system("cls");
				char name[25], addres[25], prod[25];
				cout<<"		INGRESANDO PROVEEDORES"<<endl;
				fflush(stdin);
				cout<<endl<<"ingrese nombre: " ; gets(name);
				cout<<"ingrese direccion: "; gets(addres);
				cout<<"ingrese producto: " ; gets(prod);
				lista Lista; //una nueva instancia de la clase lista
				//Lista.insertar_prove(lista_proveedor,name,addres,prod,NULL);
				Lista.insertar_prove(lista_proveedor,name,addres,prod,NULL);
				system("pause");
				break;
			}//cierra 	case 4
			case 5:{
				system("cls");
				cout<<"				MOSTRADO VENTAS"<<endl<<endl;
				cout<<left<<setw(8)<<"ID."<<setw(15)<<"TOTAL"<<setw(15)<<"EFECTIVO"<<setw(30)<<"CAMBIO"<<endl;
				mostrarVenta(arbolVenta);
				system("pause");
				break;
			}//fin del case 5
			case 6: {
				int id_ingresado=0,subTotal=0,total=0, cantidad=0, efectivo=0,cambio=0;
				int id_produ=0;
				char opcion[3];
				system("cls");
				cout<<"			REALIZANDO VENTA"<<endl;
				cout<<"ingrese IDENTIFICADOR del cliente: "; cin>>id_ingresado;
				//llamamos la funcion para buscar si existe el nit
				if((buscarCliente(arbol,id_ingresado) )==true){
						cout<<endl<<"NIT: "<<clienteEncontrado->nit<<endl;
						cout<<"NOMBRE: "<<clienteEncontrado->nombre<<endl;
						cout<<"DIRECCION: "<<clienteEncontrado->direccion<<endl;
						//pedimos que ingrese los productos a comprar
						do{
							cout<<endl<<"ingrese el codigo del producto: "; cin>>id_produ;
							if(buscarProducto(arbolProductos,id_produ) == true){
								//si encuentra el producto dentro del arbol, mostrara la informacion de precio y existencia
								cout<<"PRECIO_VENTA 				EXISTENCIA"<<endl;
								cout<<"  "<<productoEncontrado->precio_venta<<"                                     "<<productoEncontrado->existencia<<endl;
								//ahora le preguntamos cuantos quiere
								cout<<endl<<"ingrese la cantidad a comprar: "; cin>>cantidad;
								total=total + (productoEncontrado->precio_venta * cantidad);
								cout<<"[ +++ PRODUCTO COMPRADO +++ ]"<<endl;
							}else{
								cout<<"producto no encontrado"<<endl;
							}	
							cout<<endl<<"desea agregar otro producto: s / n: "; cin>>opcion[1];
						}while(opcion[1] != 'n');
						//cuando salga del while le mostramos el resumen de la factura y guardamos la venta
						system("cls");
						cout<<"******************************* FACTURA ***********************************"<<endl;
						cout<<endl<<"NIT: "<<clienteEncontrado->nit<<endl;
						cout<<"NOMBRE: "<<clienteEncontrado->nombre<<endl;
						cout<<"DIRECCION: "<<clienteEncontrado->direccion<<endl;
						cout<<"****************************************************************************"<<endl;
						cout<<endl<<"TOTAL A PAGAR: "<<total<<endl;
						cout<<"ingrese efectivo: "; cin>>efectivo;
						if(efectivo >=total){
							cambio=efectivo-total;
						}else{
							cout<<"efectivo insuficiente"<<endl;
						}
						cout<<"CAMBIO: "<<cambio<<endl;
						cout<<endl<<"------>     GRACIAS POR SU COMPRA   <------------"<<endl;
						//guardamos la venta
						insertarVenta(arbolVenta,id_ingresado,total,efectivo,cambio,NULL);
						
				}//fin del if de busqueda de cliente
				system("pause");
				break;
			}//cierra el case 6
			
			case 7: {
				system("cls")	;
				cout<<"		MOSTRANDO PRODUCTOS EXISTENTES"<<endl<<endl;
				cout<<left<<setw(8)<<"ID."<<setw(15)<<"CODIGO"<<setw(15)<<"DESCRIPCION"<<setw(15)<<"PRECIO_v"<<setw(15)<<"EXISTENCIA"<<endl;
				mostrarProductos(arbolProductos);
				system("pause");
				break;
			}//cierra el case 7
			
			case 8: {
				//se utilizara la funcion rand para generar numeros aleatorios
				srand(time(NULL)); //inicializa la semilla en 0
				int id=rand()%201;
				
				system("cls");
				char codigo[25],descripcion[25];
				float precio_c =0.00 ,precio_v =0.00;
				int existencia;
				cout<<"			INGRESANDO PRODUCTOS "<<endl<<endl;
				cout<<"id: "<<id<<endl;
				cout<<"ingrese codigo de producto: "; fflush(stdin); gets(codigo);
				cout<<"ingrese descripcion: "; gets(descripcion);
				cout<<"ingrese precio de compra: "; cin>>precio_c;
				cout<<"ingrese precio de venta: "; cin>>precio_v;
				cout<<"ingese existencia: "; cin>>existencia;
				insertarProductos(arbolProductos,id,codigo,descripcion,precio_c,precio_v,existencia,NULL);
				system("pause");
				break;
			}//cierra el case 8	
		}//cierra el switch
		
	}while(opcion!=9);
} //cierra la funcion menu


//nueva venta

ventas *nuevaventa(int id, int total,int efectivo, int cambio, ventas *padre){
    ventas *nueva_venta = new ventas();
	
	nueva_venta->id = id;
	nueva_venta->total = total;
	nueva_venta->efectivo=efectivo;
	nueva_venta->cambio=cambio;
	nueva_venta->derecha = NULL;
	nueva_venta->izquierda = NULL;
	nueva_venta->padre = padre;
	
	return nueva_venta;
}

//Funcion para insertar elementos en el arbol ventas
void insertarVenta(ventas *&arbolVenta,int id, int total, int efectivo, int cambio, ventas *padre){
	if(arbolVenta == NULL){ //Si el arbol esta vacio
		ventas *nueva_venta = nuevaventa(id,total,efectivo,cambio,padre);
		arbolVenta = nueva_venta;
	}
	else{ //Si el arbol tiene un nodo o mas
		int valorRaiz = arbolVenta->id; //Obtenemos el valor de la raiz
		if(id < valorRaiz){ //Si el elemento es menor a la raiz, insertamos en izq
			insertarVenta(arbolVenta->izquierda,id,total,efectivo,cambio,arbolVenta);
		}
		else{//Si el elemento es mayor a la raiz, insertamos en der
			insertarVenta(arbolVenta->derecha,id,total,efectivo,cambio,arbolVenta);
		}	
	}
}
//Funcion para mostrar el arbol ventas
void mostrarVenta(ventas *arbolVenta){
	if(arbolVenta == NULL){ //Si el arbol esta vacio
		return;
	}
	else{
		mostrarVenta(arbolVenta->derecha);
		cout<<left<<setw(8)<<arbolVenta->id<<setw(15)<<arbolVenta->total<<setw(15)<<arbolVenta->efectivo<<setw(30)<<arbolVenta->cambio<<endl;			
		//cout<<"identificador: "<<arbol->id<<endl;
		//cout<<"NIT: "<<arbol->nit<<endl;
		//cout<<"NOMBRE: "<<arbol->nombre<<endl;
		//cout<<"DIRECCION: "<<arbol->direccion<<endl<<endl;
		mostrarVenta(arbolVenta->izquierda);
	}
}


//Funcion para buscar un elemento en el arbol productos
bool buscarProducto(productos *arbolProductos,int n){
	if(arbolProductos == NULL){ //si el arbol esta vacio
		return false;
	}
	else if(arbolProductos->id == n){ //Si el nodo es igual al elemento
		productoEncontrado=arbolProductos;	
		return true;
	}
	else if(n < arbolProductos->id){
		return buscarProducto(arbolProductos->izquierda,n);
	}
	else{
		return buscarProducto(arbolProductos->derecha,n);
	}
}

//Funcion para buscar un elemento en el arbol clientes
bool buscarCliente(nodo *arbol,int n){
	if(arbol == NULL){ //si el arbol esta vacio
		return false;
	}
	else if(arbol->id == n){ //Si el nodo es igual al elemento
		clienteEncontrado=arbol;	
		return true;
	}
	else if(n < arbol->id){
	
		return buscarCliente(arbol->izq,n);
		
	}
	else{
		return buscarCliente(arbol->der,n);
	}
}


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
		cout<<left<<setw(8)<<arbol->id<<setw(15)<<arbol->nit<<setw(15)<<arbol->nombre<<setw(30)<<arbol->direccion<<endl;			
		//cout<<"identificador: "<<arbol->id<<endl;
		//cout<<"NIT: "<<arbol->nit<<endl;
		//cout<<"NOMBRE: "<<arbol->nombre<<endl;
		//cout<<"DIRECCION: "<<arbol->direccion<<endl<<endl;
		mostrarClientes(arbol->izq);
	}
}


//funcion para crear proveedores
 nodos *crearnodo(char nom[25],char dire[25],char pro[25],nodos *anterior){
      nodos *n_nodo= new nodos(nom,dire,pro,NULL,anterior);
      return n_nodo;
 }

//funcion para insertar nodos en el arbol
 void lista::insertar_prove(nodos *&lista_proveedor,char nombr[25],char direc[25],char produc[25],nodos *anterior){
 
      if(lista_proveedor==NULL)
      {
             nodos *n_nodo=crearnodo(nombr,direc,produc,anterior);
             lista_proveedor=n_nodo;
      }else //si el arbol tiene uno o mas nodos
      {
   			insertar_prove(lista_proveedor->siguiente,nombr,direc,produc,lista_proveedor);
          	//arbol->anterior=arbol->siguiente;
      }
 }
 
 //funcon para mostrar el arbol con recursividad
 void lista::mostrar_proveedores(nodos *lista_proveedor){
      if(lista_proveedor== NULL)
      {
                 return ;
      }
      else
      {
		cout<<"NOMBRE: " <<lista_proveedor->nombre<<endl;      
		cout<<"DIRECCION: "<<lista_proveedor->direccion<<endl;
		cout<<"PRODUCTO: "<<lista_proveedor->producto<<endl<<endl;
 		mostrar_proveedores(lista_proveedor->siguiente);
         
    }
}

//funciones para almacenar productos

productos *nuevoProducto(int id, char codigo[25], char descri[25], float precio_c, float precio_v, int exis, productos *padre){	
    productos *nuevo_producto = new productos();
	nuevo_producto->id = id;
	strcpy(nuevo_producto->codigo, codigo);
	strcpy(nuevo_producto->descripcion,descri);
	nuevo_producto->precio_compra = precio_c;
	nuevo_producto->precio_venta = precio_v;
	nuevo_producto->existencia = exis;
	nuevo_producto->derecha = NULL;
	nuevo_producto->izquierda = NULL;
	nuevo_producto->padre = padre;
	
	return nuevo_producto;
}

void insertarProductos(productos *& arbolProductos, int id, char codigo[15], char descri[25],float precio_c, float precio_v,int exis,productos *padre){
	if(arbolProductos == NULL){
		productos *nuevo_producto = nuevoProducto(id,codigo,descri,precio_c, precio_v,exis,padre);
		arbolProductos = nuevo_producto;
	}else{
		int valorRaiz = arbolProductos->id; //Obtenemos el valor de la raiz
		if(id < valorRaiz){ //Si el elemento es menor a la raiz, insertamos en izq
			insertarProductos(arbolProductos->izquierda,id,codigo,descri,precio_c,precio_v,exis,arbolProductos);
		}
		else{//Si el elemento es mayor a la raiz, insertamos en der
			insertarProductos(arbolProductos->derecha,id,codigo,descri,precio_c,precio_v,exis,arbolProductos);
		}	
	}
}

//Funcion para mostrar el arbol productos
void mostrarProductos(productos *arbolProductos){
	if(arbolProductos == NULL){ //Si el arbol esta vacio
		return;
	}
	else{
		mostrarProductos(arbolProductos->derecha);
		
		cout<<left<<setw(8)<<arbolProductos->id<<setw(15)<<arbolProductos->codigo<<setw(15)<<arbolProductos->descripcion<<setw(15)<<arbolProductos->precio_compra<<setw(10)<<arbolProductos->existencia<<endl;
		//cout<<endl<<"ID_PRODUCTO: "<<arbolProductos->id<<endl;
		//cout<<"CODIGO_PRODUCTO: "<<arbolProductos->codigo<<endl;
		//cout<<"DESCRIPCION: "<<arbolProductos->descripcion<<endl;
		//cout<<"PRECIO COMPRA: "<<arbolProductos->precio_compra<<endl;
		//cout<<"PRECIO VENTA: "<<arbolProductos->precio_venta<<endl;
		//cout<<"EXISTENCIA: "<<arbolProductos->existencia<<endl;
		mostrarProductos(arbolProductos->izquierda);
	}
}

