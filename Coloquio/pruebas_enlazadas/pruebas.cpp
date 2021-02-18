

#include <cassert>
#include <iostream>
#include "..\ayedlib\ayed.h"


int main() {


	//--- Lista Enlazada ---

	ayed::Lista_Enlazada<std::string> lista;
	lista.agregar_al_final("primer valor");
        assert (lista.get_dato_nodo(0) == "primer valor");
	lista.agregar_al_final("otro valor");
	assert(lista.get_tamanio() == 2);
	lista.set_nodo("primer valor modificado",0);
	assert (lista.get_dato_nodo(1) == "otro valor");
       	assert (lista.get_dato_nodo(0) == "primer valor modificado");
	
	lista.agregar_en("segundo valor", 1);
       	assert (lista.get_dato_nodo(1) == "segundo valor");
	lista.borrar_nodo(0);
       	assert (lista.get_dato_nodo(0) == "segundo valor");
	
	

	//--- Pila Inicializada con Constructor --- 

	ayed::Pila<std::string> pila_inicializada("Primer Elemento");
        pila_inicializada.push("Segundo Elemento");
        pila_inicializada.push("Tercer Elemento");
	assert(pila_inicializada.peek() == "Tercer Elemento");
        assert(pila_inicializada.pop() == "Tercer Elemento");
        assert(pila_inicializada.peek() == "Segundo Elemento");
        assert(pila_inicializada.pop() == "Segundo Elemento");
        assert(pila_inicializada.pop() == "Primer Elemento");
        pila_inicializada.push("Comprobacion de destructor 1er elemento -- Pila Inicializada");
        pila_inicializada.push("Comprobacion de destructor 2do elemento -- Pila Inicializada");
        pila_inicializada.push("Comprobacion de destructor 3er elemento -- Pila Inicializada");


	// Pila sin inicializar con Constructor

	ayed::Pila<std::string> pila_sin_inicializar;
        pila_sin_inicializar.push("Primer Elemento");
        pila_sin_inicializar.push("Segundo Elemento");
        pila_sin_inicializar.push("Tercer Elemento");
	assert(pila_sin_inicializar.peek() == "Tercer Elemento");
        assert(pila_sin_inicializar.pop() == "Tercer Elemento");
        assert(pila_sin_inicializar.peek() == "Segundo Elemento");
        assert(pila_sin_inicializar.pop() == "Segundo Elemento");
        assert(pila_sin_inicializar.pop() == "Primer Elemento");


	// Cola
		
	ayed::Cola<std::string> cola;
	cola.queue("primero");
	cola.queue("segundo");
	assert (!cola.is_vacia());
	assert (cola.get_tamanio() == 2);
	assert (cola.frente() == "primero");
	assert (cola.unqueue() == "primero");
	assert (cola.unqueue() == "segundo");
	assert (cola.is_vacia());
     
}




