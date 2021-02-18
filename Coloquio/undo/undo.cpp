#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "../ayedlib/ayed.h"



class Persona {

   public: 

      std::string nombre,apellido,telefono,direccion;

};



class Undo {

	public:
		void cargar_undo(Persona &persona, unsigned posicion_previa) {
		  this->persona = persona;
		  this->posicion_previa = posicion_previa;
		} 

		Persona persona;
		unsigned posicion_previa;
	

				
};




//-----------------------------------------------------------------------------

Persona get_entrada () {

   Persona persona;

   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Para ignorar los saltos de linea que se hayan dado antes
   std::cout << "Ingrese el nuevo nombre: ";
   std::getline(std::cin, persona.nombre);
   std::cout << "Ingrese el apellido: ";
   std::getline(std::cin, persona.apellido);
   std::cout << "Ingrese la direccion: ";
   std::getline(std::cin, persona.direccion);
   std::cout << "Ingrese el numero de telefono: ";
   std::getline(std::cin, persona.telefono);
   return persona;
}


//-----------------------------------------------------------------------------

void cargar_agenda (std::fstream &agenda, ayed::Lista_Enlazada<Persona> &entrada) {

   while (!agenda.eof()) {
	Persona persona;
	std::string espacio;

        std::getline(agenda, persona.nombre);
        std::getline(agenda, persona.apellido);
        std::getline(agenda, persona.direccion);
        std::getline(agenda, persona.telefono);
        std::getline(agenda, espacio);

	entrada.agregar_al_final(persona);
   }

}


//-----------------------------------------------------------------------------

int main () {

	  std::fstream agenda("agenda_pila.dat");
	  ayed::Lista_Enlazada<Persona> entradas;
	  unsigned respuesta = 0;
	  ayed::Pila<Undo> undos;
	  Undo undo_a_realizar;

	  cargar_agenda(agenda, entradas);

	  while (respuesta != 6) {


	     system("CLS");

   	     std::cout << "Agenda\n-------\n\n";

	     for (unsigned i = 0; i < entradas.get_tamanio(); ++i) {
		std::cout << "Ficha numero: "<< i+1 << std::endl;
		std::cout << entradas.get_dato_nodo(i).nombre << std::endl;
		std::cout << entradas.get_dato_nodo(i).apellido << std::endl;
		std::cout << entradas.get_dato_nodo(i).direccion << std::endl;
		std::cout << entradas.get_dato_nodo(i).telefono << "\n\n";

	     }

	     std::cout << "\n  Ingrese (1...4) para editar los campos;  (5) Para deshacer ; (6) Para salir\n";
	     std::cin >> respuesta;
	
		

	     switch (respuesta) {
		case 5: 
                  if (undos.is_vacia()) { std::cout << "\nNo hay elementos\n"; break; }
		  undo_a_realizar = undos.pop();
		  entradas.set_nodo(undo_a_realizar.persona, undo_a_realizar.posicion_previa);
		  break;
	        case 6: break;
	        default:  
		    if (respuesta >= 1 && respuesta <= 4) { 
			undos.push({entradas.get_dato_nodo(respuesta-1), respuesta-1});
			entradas.set_nodo(get_entrada(), respuesta-1);

		    } else {  std::cout << "\nERROR: Comando erroneo\n";  } break;
 	

	      }	

  	}

	// Grabo las modificaciones en el archivo
        
	agenda.clear();
        agenda.seekg (0, agenda.beg);
	
        for (unsigned i = 0; i < entradas.get_tamanio();) {
		agenda << entradas.get_dato_nodo(i).nombre << std::endl;
		agenda << entradas.get_dato_nodo(i).apellido << std::endl;
		agenda << entradas.get_dato_nodo(i).direccion << std::endl;
		agenda << entradas.get_dato_nodo(i).telefono;
		agenda << (++i == entradas.get_tamanio() ? "\n--------------------" : "\n--------------------\n");
	}

      
	agenda.close();

}





