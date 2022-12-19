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
Nodo* crearNodo(int n, Nodo* padre) {
	Nodo* nuevo_nodo = new Nodo();

	nuevo_nodo->dato = n;
	nuevo_nodo->izq = NULL;
	nuevo_nodo->der = NULL;
	nuevo_nodo->padre = padre;

	return nuevo_nodo;
}

void insertarNodo(Nodo*& arbol, int n, Nodo* padre) {
	if (arbol == NULL) {
		Nodo* nuevo_nodo = crearNodo(n, padre);
		arbol = nuevo_nodo;
	}
	else {
		int datoRaiz = arbol->dato;
		if (n < datoRaiz) {
			insertarNodo(arbol->izq, n, padre);
		}
		else {
			insertarNodo(arbol->der, n, padre);
		}
	}
}
#pragma endregion

#pragma region mostrar arbol
void mostrarArbol(Nodo* arbol, int contador) {
	if (arbol == NULL) {
		return;
	}
	else {
		mostrarArbol(arbol->der, contador + 1);
		for (int i = 0; i < contador; i++) {
			cout << "  ";
		}
		cout << arbol->dato << endl;
		mostrarArbol(arbol->izq, contador + 1);
	}
}
#pragma endregion

#pragma region busqueda de un nodo
bool busqueda(Nodo* arbol, int n) {
	if (arbol == NULL) return false;
	else if (arbol->dato == n) {
		return true;
	}
	else if (n < arbol->dato) {
		return busqueda(arbol->izq, n);
	}
	else if (n > arbol->dato) {
		return busqueda(arbol->der, n);
	}
}

#pragma endregion

#pragma region funciones auxialiares eliminar
Nodo* minimo(Nodo* arbol) {
	if (arbol == NULL) return NULL;

	if (arbol->izq) {
		return minimo(arbol->izq);
	}
	else {
		return arbol;
	}
}

void reemplazar(Nodo* arbol, Nodo* nuevoNodo) {
	if (arbol->padre) {
		if (arbol->dato = arbol->padre->izq->dato) {
			arbol->padre->izq = nuevoNodo;
		}
		else if (arbol->dato == arbol->padre->der->dato) {
			arbol->padre->der = nuevoNodo;
		}
	}
	if (nuevoNodo) {
		nuevoNodo->padre = arbol->padre;
	}
}

void destruirNodo(Nodo* nodo) {
	nodo->izq = NULL;
	nodo->der = NULL;

	delete nodo;
}
#pragma endregion

#pragma region eliminar nodo
void eliminarNodo(Nodo* eliminar) {
	if (eliminar->izq && eliminar->der) {
		Nodo* menor = minimo(eliminar->der);
		eliminar->dato = menor->dato;
		eliminarNodo(menor);
	}
	else if (eliminar->izq) {
		reemplazar(eliminar, eliminar->izq);
		destruirNodo(eliminar);
	}
	else if (eliminar->der) {
		reemplazar(eliminar, eliminar->der);
		destruirNodo(eliminar);
	}
	else {
		reemplazar(eliminar, NULL);
		destruirNodo(eliminar);
	}
}

void eliminar(Nodo* arbol, int n) {
	if (arbol == NULL) {
		return;
	}
	else if (n < arbol->dato) {
		eliminar(arbol->izq, n);
	}
	else if (n > arbol->dato) {
		eliminar(arbol->der, n);
	}
	else {
		eliminarNodo(arbol);
	}
}
#pragma endregion



int main()
{
	int contador = 0;
	string opcion;

	insertarNodo(arbol, 10, NULL);
	insertarNodo(arbol, 8, NULL);
	insertarNodo(arbol, 7, NULL);
	insertarNodo(arbol, 9, NULL);
	insertarNodo(arbol, 12, NULL);
	insertarNodo(arbol, 11, NULL);



	do {
		cout << "(1)Insertar\n(2)Eliminar\n(3)Mostrar\n(4)Buscar\n>>";
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
		}
		system("PAUSE");
		system("CLS");
	} while (stoi(opcion) != 5);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
