

#include <cassert>
#include <iostream>
#include "ayed.h"


int main() {


/*
	ayed::Lista_Enlazada<int> lista;
	lista.set_nodo(3,0);
        assert (lista.get_dato_nodo(0) == 3);

	lista.agregar_nodo();
	lista.set_nodo(5,1);
	assert (lista.get_dato_nodo(1) == 5);

	lista.agregar_nodo();
	lista.set_nodo(123,2);
	lista.borrar_nodo(1);
	assert (lista.get_cantidad_nodos() == 2);
	assert (lista.get_dato_nodo(0) == 3);
	assert (lista.get_dato_nodo(1) == 123);
*/	

	// Pila Inicializada con Constructor

	ayed::Pila<std::string> pila_inicializada("Primer Elemento");
        pila_inicializada.Push("Segundo Elemento");
        pila_inicializada.Push("Tercer Elemento");
	assert(pila_inicializada.Peek() == "Tercer Elemento");
        assert(pila_inicializada.Pop() == "Tercer Elemento");
        assert(pila_inicializada.Peek() == "Segundo Elemento");
        assert(pila_inicializada.Pop() == "Segundo Elemento");
        assert(pila_inicializada.Pop() == "Primer Elemento");
        pila_inicializada.Push("Comprobacion de destructor 1er elemento -- Pila Inicializada");
        pila_inicializada.Push("Comprobacion de destructor 2do elemento -- Pila Inicializada");
        pila_inicializada.Push("Comprobacion de destructor 3er elemento -- Pila Inicializada");

	// Pila sin inicializar con Constructor

	ayed::Pila<std::string> pila_sin_inicializar;
        pila_sin_inicializar.Push("Primer Elemento");
        pila_sin_inicializar.Push("Segundo Elemento");
        pila_sin_inicializar.Push("Tercer Elemento");
	assert(pila_sin_inicializar.Peek() == "Tercer Elemento");
        assert(pila_sin_inicializar.Pop() == "Tercer Elemento");
        assert(pila_sin_inicializar.Peek() == "Segundo Elemento");
        assert(pila_sin_inicializar.Pop() == "Segundo Elemento");
        assert(pila_sin_inicializar.Pop() == "Primer Elemento");



/*


	// Cola
		
	ayed::Cola<int> cola;
	cola.Queue(1);
	cola.Queue(2);
	std::cout << cola.Frente();
	cola.Queue(3);
	std::cout << cola.Frente();
*/		

}




