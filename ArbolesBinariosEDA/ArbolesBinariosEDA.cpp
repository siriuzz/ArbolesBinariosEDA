/*
Enunciado: Realizar un programa C++ que permita gestionar un Árbol Binario de Búsqueda.

Participantes:
1- John Luis Del Rosario Sánchez - ID 1106940
2- Ashly Marisell Paula Ynoa - ID 1108023
3- Elián Matos Díaz - ID 1106901
4- Juan Daniel Ubiera Méndez - ID 1107248
5- Kelvin Arístides García Espinal - ID 1107646

Fecha de entrega: 12/12/2022
*/

#include <iostream>
#include <string>
#include <stdlib.h>
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
Nodo* CrearNodo(int n, Nodo* padre) {
	Nodo* nuevo_nodo = new Nodo(); //apartar espacio en memoria

	//propiedades del nuevo nodo
	nuevo_nodo->dato = n;
	nuevo_nodo->izq = NULL;
	nuevo_nodo->der = NULL;
	nuevo_nodo->padre = padre;

	return nuevo_nodo;
}

//busca la posicion donde insertar el nodo (recursiva)
void Insertar(Nodo*& arbol, int n, Nodo* padre) {
	if (arbol == NULL) { //si el arbol esta vacio o se ha llegado a la posicion deseada
		Nodo* nuevo_nodo = CrearNodo(n, padre);
		arbol = nuevo_nodo;
	}
	else { //si el arbol no esta vacio o no se ha llegado a la posicion correspondiente
		int datoRaiz = arbol->dato;
		if (n < datoRaiz) { //si el dato es menor que la raiz, izquierda
			Insertar(arbol->izq, n, arbol);
		}
		else { //si el dato es mayor que la raiz, derecha
			Insertar(arbol->der, n, arbol);
		}
	}
}
#pragma endregion

//muestra los nodos del arbol (recursiva)
void MostrarArbol(Nodo* arbol, int contador) {
	if (arbol == NULL) { //se llega a un elemento hoja, o el arbol esta vacio
		return;
	}
	else { //primero se despliega la parte derecha, luego la raiz, y por ultimo la parte izquierda
		MostrarArbol(arbol->der, contador + 1); //parte derecha
		for (int i = 0; i < contador; i++) { //tantos espacios como diga el contador
			cout << "  ";
		}
		cout << arbol->dato << endl; //raiz
		MostrarArbol(arbol->izq, contador + 1); //parte izquierda
	}
}

//busca un dato en el arbol binario de busqueda (recursiva)
bool Busqueda(Nodo* arbol, int n) {
	if (arbol == NULL) return false; //se llega a un elemento hoja sin encontrar el dato
	else if (arbol->dato == n) { //se encuentra el dato
		return true;
	}
	else if (n < arbol->dato) { //el dato es menor que la raiz del arbol, izquierda
		return Busqueda(arbol->izq, n);
	}
	else if (n > arbol->dato) { //el dato es mayor que la raiz del arbol, derecha
		return Busqueda(arbol->der, n);
	}
}

//recorre el arbol con el recorrido preorder (recursiva)
void PreOrder(Nodo* arbol) {
	if (arbol == NULL) return;
	else {
		cout << arbol->dato << " - ";
		PreOrder(arbol->izq);
		PreOrder(arbol->der);
	}
}

#pragma region funciones auxialiares eliminar
//busca el valor minimo de un arbol (recursivo)
Nodo* Minimo(Nodo* arbol) {
	if (arbol == NULL) return NULL; //en el caso de que no se encuentre un minimo (arbol sin ramas)

	if (arbol->izq) { //se sigue buscando el minimo a la izquierda
		return Minimo(arbol->izq);
	}
	else { //si ya no hay ramas a la izquierda, encontramos el minimo
		return arbol;
	}
}

//reemplaza las propiedades del nodo padre
void Reemplazar(Nodo* arbol, Nodo* nuevoNodo) {
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
void DestruirNodo(Nodo* nodo) {
	nodo->izq = NULL;
	nodo->der = NULL;

	nodo;
}

#pragma endregion

#pragma region eliminar nodo
//administra las condiciones que se deben dar para cada caso de eliminacion de un nodo
void EliminarNodo(Nodo* eliminar) {
	if (eliminar->izq && eliminar->der) { //nodo con rama izquierda y derecha != NULL
		Nodo* menor = Minimo(eliminar->der);
		eliminar->dato = menor->dato;
		EliminarNodo(menor);
	}
	else if (eliminar->izq) { //nodo solo con rama a la izquierda
		Reemplazar(eliminar, eliminar->izq);
		DestruirNodo(eliminar);
	}
	else if (eliminar->der) { //nodo solo con rama a la derecha
		Reemplazar(eliminar, eliminar->der);
		DestruirNodo(eliminar);
	}
	else { //nodo sin ramas
		Reemplazar(eliminar, NULL);
		DestruirNodo(eliminar);
	}
}

//busca el nodo que se desea eliminar
void Eliminar(Nodo* arbol, int n) {
	if (arbol == NULL) { //si el arbol esta vacio o no se encontró el valor
		cout << "Nodo no encontrado en el arbol binario" << endl;
		return;
	}
	else if (n < arbol->dato) { //izquierda
		Eliminar(arbol->izq, n);
	}
	else if (n > arbol->dato) { //derecha
		Eliminar(arbol->der, n);
	}
	else { //igual a n
		EliminarNodo(arbol);
		cout << "Nodo " << n << " eliminado correctamente!" << endl;
	}
}
#pragma endregion

//valida si un string es un numero
bool ValidarNumero(string str)
{
	int i = 0;
	while (str[i] != '\0') //'\0' es el character que marca el final del string
	{
		if (isdigit(str[i]) == false)
		{
			return false;
		}
		i++;
	}
	return true; //devuelve un str igual si no se encontraron letras
}

int main()
{
	int contador = 0;
	string opcion, dato;
	//arbol de prueba
	//int arbolPrueba[11] = { 10,5,15,20,12,30,8,3,9,6,7 };
	//for (int i = 0; i < sizeof(arbolPrueba) / sizeof(arbolPrueba[0]);i++) {
	//	Insertar(arbol, arbolPrueba[i], NULL);
	//}

	cout << "Bienvenido!" << endl;

	do {
		cout << "Que accion desea realizar sobre el Arbol Binario de Busqueda?" << endl;
		cout << "(1)Insertar\n(2)Eliminar\n(3)Mostrar\n(4)Buscar\n(5)Recorrido (PreOrder)\n(6)Salir\n>>";
		cin >> opcion;
		if (!ValidarNumero(opcion)) {
			cout << "Tipo de dato incorrecto, intente de nuevo" << endl;
			opcion = "0";
			system("PAUSE");
			system("CLS");
			continue;
		}

		switch (stoi(opcion)) {
		case 1: //Insertar
			cout << "Digite el numero que desea insertar: ";
			cin >> dato;
			if (!ValidarNumero(dato)) {
				cout << "Solo se pueden insertar numeros (positivos), intente de nuevo" << endl;
				break;
			}

			Insertar(arbol, stoi(dato), NULL);
			cout << "Numero agregado correctamente!" << endl;
			break;
		case 2: //Eliminar
			if (arbol == NULL) {
				cout << "El arbol esta vacio, inserte datos primero" << endl;
				break;
			}
			cout << "Digite el numero del nodo que desea eliminar: ";
			cin >> dato;
			if (!ValidarNumero(dato)) {
				cout << "Solo se pueden insertar numeros, intente de nuevo" << endl;
				break;
			}

			Eliminar(arbol, stoi(dato));
			break;
		case 3: //Mostrar
			if (arbol == NULL) {
				cout << "El arbol esta vacio, inserte datos primero" << endl;
				break;
			}

			MostrarArbol(arbol, contador);
			break;
		case 4: //Buscar
			if (arbol == NULL) {
				cout << "El arbol esta vacio, inserte datos primero" << endl;
				break;
			}
			cout << "Digite el numero que desea buscar en el arbol: ";
			cin >> dato;
			if (!ValidarNumero(dato)) {
				cout << "Solo se pueden insertar numeros, intente de nuevo" << endl;
				break;
			}

			if (Busqueda(arbol, stoi(dato))) cout << "El elemento ha sido encontrado en la lista" << endl;
			else cout << "Elemento no encontrado" << endl;

			break;

		case 5: //Recorrido preOrder
			if (arbol == NULL) {
				cout << "El arbol esta vacio, inserte datos primero" << endl;
				break;
			}

			PreOrder(arbol);
			cout << "FIN" << endl;
			break;

		case 6: //Salir
			exit(0);
			break;

		default:
			cout << "Opcion fuera del menu, intente de nuevo" << endl;
			break;
		}
		system("PAUSE");
		system("CLS");
	} while (stoi(opcion) != 6);
}