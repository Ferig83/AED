

namespace ayed {

 template <class Tipo> class Lista_Enlazada;
 template <class Tipo> class Pila;
 template <class Tipo> class Cola;
 template <class Tipo> class Nodo;


//-----------------------------------------------------------------------------


 template <class Tipo> 
 class Nodo {

	private:

		Nodo() { }
		Nodo* siguiente_nodo;
		Tipo dato;
		friend class Lista_Enlazada<Tipo>;
		friend class Pila<Tipo>;
		friend class Cola<Tipo>;

 };


//-----------------------------------------------------------------------------

 template <class Tipo> 
 class Lista_Enlazada {

	public:

	        Lista_Enlazada();

		void agregar_al_final(Tipo dato_a_agregar);
		void agregar_en(Tipo dato_a_agregar, unsigned posicion);   
         	void set_nodo(Tipo dato_a_agregar, unsigned numero_del_nodo);
		void borrar_nodo (unsigned numero_del_nodo); 	
		Tipo get_dato_nodo (unsigned numero_del_nodo);
		unsigned get_tamanio();
		bool is_vacia();                	

	        ~Lista_Enlazada();
 
	private: 

		Nodo<Tipo>* primer_nodo = nullptr;
	        unsigned cantidad_nodos = 0;
		
		
 };

}

//-----------------------------------------------------------------------------


/* Definiciones  --  los templates no puedo definirlos fuera del header :(  */


template <class Tipo> 
ayed::Lista_Enlazada<Tipo>::Lista_Enlazada() {
   primer_nodo = nullptr;
}

template <class Tipo> 
ayed::Lista_Enlazada<Tipo>::~Lista_Enlazada() {

   if (primer_nodo != nullptr) { 

   Nodo<Tipo>* indice_nodo = primer_nodo;
     while (indice_nodo != nullptr) {
        Nodo<Tipo>* nodo_a_borrar;
        nodo_a_borrar = indice_nodo;
        indice_nodo = indice_nodo->siguiente_nodo;
        delete nodo_a_borrar;
        std::cout << "\nNodo lista enlazada borrado desde el destructor";
     }
   }
}


template <class Tipo>
void ayed::Lista_Enlazada<Tipo>::agregar_al_final(Tipo dato_a_agregar) {

   Nodo<Tipo>* nodo_nuevo = new Nodo<Tipo>; 
   nodo_nuevo->siguiente_nodo = nullptr;
   nodo_nuevo->dato = dato_a_agregar;

   if (cantidad_nodos == 0) {
      primer_nodo = nodo_nuevo;
   } else {
		   
      Nodo<Tipo>* indice_nodo = primer_nodo;
      while (indice_nodo->siguiente_nodo != nullptr) {
         indice_nodo = indice_nodo->siguiente_nodo;
      }
      indice_nodo->siguiente_nodo = nodo_nuevo; 

   }

     
   cantidad_nodos++;

}


template <class Tipo>
void ayed::Lista_Enlazada<Tipo>::agregar_en(Tipo dato_a_agregar, unsigned posicion) {

   Nodo<Tipo>* nodo_nuevo = new Nodo<Tipo>; 
   nodo_nuevo->dato = dato_a_agregar

   // Revisar bien esto si no hay nodos, y eso
		   
   Nodo<Tipo>* indice_nodo = primer_nodo;
   for (int i = 0; i < posicion - 1; ++i) {
      indice_nodo = indice_nodo->siguiente_nodo;
   }

   Nodo<Tipo>* nodo = indice_nodo->siguiente_nodo;
   
   indice_nodo->siguiente_nodo = nodo_nuevo;
   nodo_nuevo->siguiente_nodo = nodo;   
   cantidad_nodos++;

}




template <class Tipo>
void ayed::Lista_Enlazada<Tipo>::set_nodo(Tipo dato_a_agregar, unsigned numero_del_nodo) {

   Nodo<Tipo>* indice_nodo = primer_nodo;
   for (unsigned i = 0; i < numero_del_nodo; i++) {
      indice_nodo = indice_nodo->siguiente_nodo;
   }
   indice_nodo->dato = dato_a_agregar;

}


template <class Tipo>
void ayed::Lista_Enlazada<Tipo>::borrar_nodo (unsigned numero_del_nodo) {

   Nodo<Tipo>* indice_nodo = primer_nodo;
    for (int i = 0; i < (numero_del_nodo-1); i++) {
       indice_nodo = indice_nodo->siguiente_nodo;	
    }   
    Nodo<Tipo>* nodo_a_borrar = indice_nodo->siguiente_nodo;
    indice_nodo->siguiente_nodo = nodo_a_borrar->siguiente_nodo;
    delete nodo_a_borrar; 
    cantidad_nodos--;
} 	
	        

template <class Tipo>
Tipo ayed::Lista_Enlazada<Tipo>::get_dato_nodo (unsigned numero_del_nodo) {

   Nodo<Tipo>* indice_nodo = primer_nodo;
  
   for (int i = 0; i < numero_del_nodo; i++) {
      indice_nodo = indice_nodo->siguiente_nodo;
   }
   return indice_nodo->dato;
}	


template <class Tipo>
unsigned ayed::Lista_Enlazada<Tipo>::get_tamanio() {

   return cantidad_nodos;
}


template <class Tipo>
bool ayed::Lista_Enlazada<Tipo>::is_vacia() {

	return cantidad_nodos == 0 ? true : false;

}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

namespace ayed {


 template <class Tipo> 
 class Pila {

	public:

	        Pila(Tipo dato_a_agregar);
	        Pila();

		void push(Tipo dato_a_agregar);
         	Tipo pop();
		Tipo peek();  
		bool is_vacia();
	        unsigned get_tamanio();              	

	        ~Pila();
 
	private: 

		Nodo<Tipo>* primer_nodo = nullptr;
	        unsigned cantidad_nodos = 0;	
		
 };

}


template <class Tipo> 
ayed::Pila<Tipo>::Pila(Tipo dato_a_agregar) {

   try  {
      primer_nodo = new Nodo<Tipo>;
   }

   catch (std::bad_alloc& ba) {
      std::cerr << "Error en reserva de memoria: " << ba.what() << "\n";
   }


   primer_nodo->siguiente_nodo = nullptr;
   primer_nodo->dato = dato_a_agregar;
   cantidad_nodos++;
}

template <class Tipo> 
ayed::Pila<Tipo>::Pila() {
   primer_nodo = nullptr;
}


//-----------------------------------------------------------------------------

template <class Tipo> 
ayed::Pila<Tipo>::~Pila() {

   Nodo<Tipo>* indice_nodo = primer_nodo;

   while (indice_nodo != nullptr) {
      Nodo<Tipo>* nodo_a_borrar;
      nodo_a_borrar = indice_nodo;
      indice_nodo = indice_nodo->siguiente_nodo;
      Tipo contenido_previo = nodo_a_borrar->dato;
      delete nodo_a_borrar;
      std::cout << "\nNodo de pila borrado desde el destructor";
   }
}


//-----------------------------------------------------------------------------



template <class Tipo>
void ayed::Pila<Tipo>::push(Tipo dato_a_agregar) {


   Nodo<Tipo>* nodo_nuevo;

   try  {
      nodo_nuevo = new Nodo<Tipo>; 
   }

   catch (std::bad_alloc& ba) {
      std::cerr << "Error en reserva de memoria: " << ba.what() << "\n";
   }

   if (primer_nodo == nullptr) {

     primer_nodo = nodo_nuevo;
     primer_nodo->dato = dato_a_agregar;
     primer_nodo->siguiente_nodo = nullptr;

   } else {
   
		   
     nodo_nuevo->siguiente_nodo = primer_nodo;
     nodo_nuevo->dato = dato_a_agregar;
     primer_nodo = nodo_nuevo;
   
   }

   cantidad_nodos++;
}

//-----------------------------------------------------------------------------

template <class Tipo>
Tipo ayed::Pila<Tipo>::pop () {

    Nodo<Tipo>* nodo_a_borrar = primer_nodo;
    Tipo dato_pop;


    if (primer_nodo == nullptr) { 
	std::cerr << "No hay nodos"; 
	return dato_pop;  // Esto mejorarlo

    } 

    dato_pop = primer_nodo->dato;
    primer_nodo = primer_nodo->siguiente_nodo;
    delete nodo_a_borrar;
    cantidad_nodos--;
    return dato_pop;
} 	



//-----------------------------------------------------------------------------


template <class Tipo>
Tipo ayed::Pila<Tipo>::peek () {

    return primer_nodo->dato;
  
} 	

//-----------------------------------------------------------------------------


template <class Tipo>
bool ayed::Pila<Tipo>::is_vacia () {

    return cantidad_nodos == 0 ? true : false;
  
} 	

//-----------------------------------------------------------------------------


template <class Tipo>
unsigned ayed::Pila<Tipo>::get_tamanio () {

    return cantidad_nodos;
} 	


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


namespace ayed {

 template <class Tipo> 
 class Cola {

	public:

	        Cola(Tipo dato_a_agregar);
	        Cola();

		void queue(Tipo dato_a_agregar);
         	Tipo unqueue();
		Tipo frente();  
		bool is_vacia();
	        unsigned get_tamanio();              	

	        ~Cola();
 
	private: 

		Nodo<Tipo>* primer_nodo = nullptr;
	        unsigned cantidad_nodos = 0;	
		
 };

}


template <class Tipo> 
ayed::Cola<Tipo>::Cola(Tipo dato_a_agregar) {

   try  {
      primer_nodo = new Nodo<Tipo>;
   }

   catch (std::bad_alloc& ba) {
      std::cerr << "Error en reserva de memoria: " << ba.what() << "\n";
   }


   primer_nodo->siguiente_nodo = nullptr;
   primer_nodo->dato = dato_a_agregar;
   cantidad_nodos++;
}

template <class Tipo> 
ayed::Cola<Tipo>::Cola() {
   primer_nodo = nullptr;
}


//-----------------------------------------------------------------------------

template <class Tipo> 
ayed::Cola<Tipo>::~Cola() {

   Nodo<Tipo>* indice_nodo = primer_nodo;

   while (indice_nodo != nullptr) {
      Nodo<Tipo>* nodo_a_borrar;
      nodo_a_borrar = indice_nodo;
      indice_nodo = indice_nodo->siguiente_nodo;
      delete nodo_a_borrar;
      std::cout << "\nNodo de cola borrado desde el destructor";
   }
}


//-----------------------------------------------------------------------------

template <class Tipo>
void ayed::Cola<Tipo>::queue(Tipo dato_a_agregar) {


   Nodo<Tipo>* nodo_nuevo;

   try  {
      nodo_nuevo = new Nodo<Tipo>; 
   }

   catch (std::bad_alloc& ba) {
      std::cerr << "Error en reserva de memoria: " << ba.what() << "\n";
   }

   nodo_nuevo->siguiente_nodo = nullptr;
   nodo_nuevo->dato = dato_a_agregar;
    
   if (primer_nodo == nullptr) {
      primer_nodo = nodo_nuevo;
   } else {
      Nodo<Tipo>* indice_nodo = primer_nodo;
      while (indice_nodo->siguiente_nodo != nullptr) {
         indice_nodo = indice_nodo->siguiente_nodo;
      }

      indice_nodo->siguiente_nodo = nodo_nuevo;  
   }

   cantidad_nodos++;

}



//-----------------------------------------------------------------------------


template <class Tipo>
Tipo ayed::Cola<Tipo>::unqueue() {

    Tipo dato_unqueue;

    if (primer_nodo == nullptr) { 
	std::cerr << "No hay nodos"; 
	return dato_unqueue;
    }



   ayed::Nodo<Tipo> *nodo_a_borrar = primer_nodo;
   dato_unqueue = primer_nodo->dato;
   primer_nodo = primer_nodo->siguiente_nodo;
   delete nodo_a_borrar;
   cantidad_nodos--;
   return dato_unqueue;

}


//-----------------------------------------------------------------------------

template <class Tipo>
bool ayed::Cola<Tipo>::is_vacia () {

    return cantidad_nodos == 0 ? true : false;
  
} 	

//-----------------------------------------------------------------------------


template <class Tipo>
unsigned ayed::Cola<Tipo>::get_tamanio () {

    return cantidad_nodos;
} 	

//-----------------------------------------------------------------------------


template <class Tipo>
Tipo ayed::Cola<Tipo>::frente() {

    return primer_nodo->dato;
} 	



