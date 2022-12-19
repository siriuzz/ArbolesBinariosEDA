// ArbolesBinariosEDA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;


struct Nodo {
	int dato;
	Nodo* izq;
	Nodo* der;
	Nodo* padre;
};

Nodo* arbol = NULL;

#pragma region crear e insertar nodo
//crea el nodo que se desea insertar en el arbol
Nodo* crearNodo(int n, Nodo* padre) {
	Nodo* nuevo_nodo = new Nodo(); //apartar espacio en memoria

	//propiedades del nuevo nodo
	nuevo_nodo->dato = n;
	nuevo_nodo->izq = NULL;
	nuevo_nodo->der = NULL;
	nuevo_nodo->padre = padre;

	return nuevo_nodo;
}

//busca la posicion donde insertar el nodo (recursiva)
void insertarNodo(Nodo*& arbol, int n, Nodo* padre) {
	if (arbol == NULL) { //si el arbol esta vacio o se ha llegado a la posicion deseada
		Nodo* nuevo_nodo = crearNodo(n, padre);
		arbol = nuevo_nodo;
	}
	else { //si el arbol no esta vacio o no se ha llegado a la posicion correspondiente
		int datoRaiz = arbol->dato;
		if (n < datoRaiz) { //si el dato es menor que la raiz, izquierda
			insertarNodo(arbol->izq, n, arbol);
		}
		else { //si el dato es mayor que la raiz, derecha
			insertarNodo(arbol->der, n, arbol);
		}
	}
}
#pragma endregion

#pragma region mostrar arbol
//muestra los nodos del arbol (recursiva)
void mostrarArbol(Nodo* arbol, int contador) {
	if (arbol == NULL) { //se llega a un elemento hoja, o el arbol esta vacio
		return;
	}
	else { //primero se despliega la parte derecha, luego la raiz, y por ultimo la parte izquierda
		mostrarArbol(arbol->der, contador + 1); //parte derecha
		for (int i = 0; i < contador; i++) { //tantos espacios como diga el contador
			cout << "  ";
		}
		cout << arbol->dato << endl; //raiz
		mostrarArbol(arbol->izq, contador + 1); //parte izquierda
	}
}
#pragma endregion

#pragma region busqueda de un nodo
//busca un dato en el arbol binario de busqueda (recursiva)
bool busqueda(Nodo* arbol, int n) {
	if (arbol == NULL) return false; //se llega a un elemento hoja sin encontrar el dato
	else if (arbol->dato == n) { //se encuentra el dato
		return true;
	}
	else if (n < arbol->dato) { //el dato es menor que la raiz del arbol, izquierda
		return busqueda(arbol->izq, n);
	}
	else if (n > arbol->dato) { //el dato es mayor que la raiz del arbol, derecha
		return busqueda(arbol->der, n);
	}
}

#pragma endregion
//recorre el arbol con el recorrido preorder (recursiva)
void preOrder(Nodo* arbol) {
	if (arbol == NULL) return;
	else {
		cout << arbol->dato << " - ";
		preOrder(arbol->izq);
		preOrder(arbol->der);
	}
}

#pragma region funciones auxialiares eliminar
//busca el valor minimo de un arbol (recursivo)
Nodo* minimo(Nodo* arbol) {
	if (arbol == NULL) return NULL; //en el caso de que no se encuentre un minimo (arbol sin ramas)

	if (arbol->izq) { //se sigue buscando el minimo a la izquierda
		return minimo(arbol->izq);
	}
	else { //si ya no hay ramas a la izquierda, encontramos el minimo
		return arbol;
	}
}

//
void reemplazar(Nodo* arbol, Nodo* nuevoNodo) {
	//si el nodo a eliminar tiene un padre
	if (arbol->padre) { 
		if (arbol->padre->izq) { //se verifica que el padre tenga una rama a la izquierda
			//si el dato de la rama izquierda del padre es igual al dato del arbol
			if (arbol->dato == arbol->padre->izq->dato) {
				arbol->padre->izq = nuevoNodo;
			}
		}

		if (arbol->padre->der) { //se verifica que el padre tenga una rama a la izquierda
			//si el dato de la rama derecha del padre es igual al dato del arbol
			if (arbol->dato == arbol->padre->der->dato) {
				arbol->padre->der = nuevoNodo;
			}
		}
	}

	if (nuevoNodo) { 
		nuevoNodo->padre = arbol->padre;
	}
}

//vuelve NULL las propiedades del nodo y lo elimina
void destruirNodo(Nodo* nodo) {
	nodo->izq = NULL;
	nodo->der = NULL;

	delete nodo;
}
#pragma endregion

#pragma region eliminar nodo
//administra las condiciones que se deben dar para cada caso de eliminacion de un nodo
void eliminarNodo(Nodo* eliminar) {
	if (eliminar->izq && eliminar->der) { //nodo con rama izquierda y derecha != NULL
		Nodo* menor = minimo(eliminar->der);
		eliminar->dato = menor->dato;
		eliminarNodo(menor);
	}
	else if (eliminar->izq) { //nodo solo con rama a la izquierda
		reemplazar(eliminar, eliminar->izq);
		destruirNodo(eliminar);
	}
	else if (eliminar->der) { //nodo solo con rama a la derecha
		reemplazar(eliminar, eliminar->der);
		destruirNodo(eliminar);
	}
	else { //nodo sin ramas
		reemplazar(eliminar, NULL);
		destruirNodo(eliminar);
	}
}

//busca el nodo que se desea eliminar
void eliminar(Nodo* arbol, int n) {
	if (arbol == NULL) { //si el arbol esta vacio
		return;
	}
	else if (n < arbol->dato) { //izquierda
		eliminar(arbol->izq, n);
	}
	else if (n > arbol->dato) { //derecha
		eliminar(arbol->der, n);
	}
	else { //igual a n
		eliminarNodo(arbol);
	}
}
#pragma endregion



int main()
{
	int contador = 0;
	string opcion;

	insertarNodo(arbol, 10, NULL);
	insertarNodo(arbol, 5, NULL);
	insertarNodo(arbol, 15, NULL);
	insertarNodo(arbol, 20, NULL);
	insertarNodo(arbol, 12, NULL);
	insertarNodo(arbol, 30, NULL);
	insertarNodo(arbol, 8, NULL);
	insertarNodo(arbol, 3, NULL);
	insertarNodo(arbol, 9, NULL);
	insertarNodo(arbol, 6, NULL);
	insertarNodo(arbol, 7, NULL);



	do {
		cout << "(1)Insertar\n(2)Eliminar\n(3)Mostrar\n(4)Buscar\n(5)Recorrido (PreOrder)\n>>";
		cin >> opcion;

		switch (stoi(opcion)) {
		case 1:
			int dato;
			cout << "Digite el numero que desea insertar: ";
			cin >> dato;

			insertarNodo(arbol, dato, NULL);
			break;
		case 2:
			cout << "Digite el numero del nodo que desea eliminar: ";
			cin >> dato;
			eliminar(arbol, dato);
			break;
		case 3:
			mostrarArbol(arbol, contador);

			break;
		case 4:
			cout << "Digite el numero que desea buscar en el arbol: ";
			cin >> dato;
			if (busqueda(arbol, dato)) {
				cout << "El elemento ha sido encontrado en la lista" << endl;
			}
			else {
				cout << "Elemento no encontrado" << endl;

			}
			break;

		case 5:
			preOrder(arbol);
			break;
		}
		system("PAUSE");
		system("CLS");
	} while (stoi(opcion) != 6);
}