#include <iostream>
#include <cassert>
#include "..\ayedlib\ayed_cont.h"


int main () {

	


	// --- Pila ---

	ayed_cont::Pila<std::string> pila(5);

	
	pila.push("primero");
	pila.push("segundo");
	pila.push("tercero");
	assert(pila.get_tamanio() == 3);
	assert(pila.peek() == "tercero");
	assert(pila.pop() == "tercero");
	assert(pila.pop() == "segundo");
	assert(pila.get_tamanio() == 1);
	pila.pop();
	assert(pila.is_vacia());
	pila.push("2");
	pila.push("3");
	pila.push("4");
	pila.push("5");
	pila.push("6");
	pila.push("7");
	assert(!pila.is_vacia());

	// --- Cola ---

	ayed_cont::Cola<std::string> cola(5);
	cola.queue("primero");
	cola.queue("segundo");
	assert (!cola.is_vacia());
	assert (cola.get_tamanio() == 2);
	assert (cola.frente() == "primero");
	assert (cola.unqueue() == "primero");
	assert (cola.unqueue() == "segundo");
	assert (cola.is_vacia());
     
	
	// --- Lista_Continua ---

	ayed_cont::Lista_Continua<std::string> lista(5);
	assert (lista.get_tamanio() == 5);
	lista.set_nodo("primero", 0);
	lista.set_nodo("quinto", 4);
	assert (lista.get_dato_nodo(0) == "primero");
	assert (lista.get_dato_nodo(4) == "quinto");


}