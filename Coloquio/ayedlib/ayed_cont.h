/*--- VERSIONES CONTINUAS ---*/


#include <cstddef> // std::size_t

namespace ayed_cont {

   template <class Tipo> class Lista_Continua;
   template <class Tipo> class Pila;
   template <class Tipo> class Cola;
   template <class Tipo> class Nodo;


//-----------------------------------------------------------------------------


 template <class Tipo> 
 class Nodo {

	private:

		Nodo() { }
		Tipo dato;
		friend class Lista_Continua<Tipo>;
		friend class Pila<Tipo>;
		friend class Cola<Tipo>;

 };


 template <class Tipo> 
 class Pila {

	public:

	        Pila(Tipo dato_a_agregar, std::size_t cantidad_total);
	        Pila(std::size_t cantidad_total);

		void push(Tipo dato_a_agregar);
         	Tipo pop();
		Tipo peek();  
		bool is_vacia();
	        unsigned get_tamanio();              	

	        ~Pila();
 
	private: 

		Nodo<Tipo>* indice = nullptr;
	        unsigned cantidad_elementos = 0;	
	        std::size_t cantidad_elementos_total = 0;	

		
 };

}


template <class Tipo> 
ayed_cont::Pila<Tipo>::Pila(Tipo dato_a_agregar, std::size_t cantidad_total) {

   try  {
      indice = new Nodo<Tipo>[cantidad_total];
   }

   catch (std::bad_alloc& ba) {
      std::cerr << "Error en reserva de memoria: " << ba.what() << "\n";
   }

   indice->dato = dato_a_agregar
   cantidad_elementos_total = cantidad_total;
   cantidad_elementos++;
}

template <class Tipo> 
ayed_cont::Pila<Tipo>::Pila(std::size_t cantidad_total) {
   try  {
      indice = new Nodo<Tipo>[cantidad_total];
   }

   catch (std::bad_alloc& ba) {
      std::cerr << "Error en reserva de memoria: " << ba.what() << "\n";
   }

   cantidad_elementos_total = cantidad_total;
}


//-----------------------------------------------------------------------------

template <class Tipo> 
ayed_cont::Pila<Tipo>::~Pila() {
	
	delete[] indice;
	std::cout << "\nPila continua borrada desde el destructor";
}


//-----------------------------------------------------------------------------



template <class Tipo>
void ayed_cont::Pila<Tipo>::push(Tipo dato_a_agregar) {

   if (cantidad_elementos >= cantidad_elementos_total) {
    std::cerr << "No hay mas elementos disponibles (pila a tope)"; 
   }
   else {
    Nodo<Tipo>* nodo_push = indice + cantidad_elementos++;
    nodo_push->dato = dato_a_agregar; 
   }
}

//-----------------------------------------------------------------------------

template <class Tipo>
Tipo ayed_cont::Pila<Tipo>::pop () {

     if (cantidad_elementos <= 0) std::cerr << "No hay mas elementos";	
     return cantidad_elementos > 0 ? (indice+--cantidad_elementos)->dato : 0;
} 	



//-----------------------------------------------------------------------------


template <class Tipo>
Tipo ayed_cont::Pila<Tipo>::peek () {

    return (indice+cantidad_elementos-1)->dato;
  
} 	

//-----------------------------------------------------------------------------


template <class Tipo>
bool ayed_cont::Pila<Tipo>::is_vacia () {

    return cantidad_elementos == 0 ? true : false;
  
} 	

//-----------------------------------------------------------------------------


template <class Tipo>
unsigned ayed_cont::Pila<Tipo>::get_tamanio () {

    return cantidad_elementos;
} 	



//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


namespace ayed_cont {


 template <class Tipo> 
 class Cola{

	public:

	        Cola(const Tipo &dato_a_agregar, const std::size_t cantidad_total);
	        Cola(const std::size_t cantidad_total);

		void queue(const Tipo &dato_a_agregar);
         	Tipo unqueue();
		Tipo frente();  
		bool is_vacia();
	        unsigned get_tamanio();              	

	        ~Cola();
 
	private: 

		Nodo<Tipo>* detras = nullptr;
	        unsigned cantidad_elementos = 0;	
	        std::size_t cantidad_elementos_total = 0;	

		
 };

}



template <class Tipo> 
ayed_cont::Cola<Tipo>::Cola(const Tipo &dato_a_agregar, const std::size_t cantidad_total) {

   try  {
      detras = new Nodo<Tipo>[cantidad_total];
   }

   catch (std::bad_alloc& ba) {
      std::cerr << "Error en reserva de memoria: " << ba.what() << "\n";
   }

   detras->dato = dato_a_agregar
   cantidad_elementos_total = cantidad_total;
   cantidad_elementos++;
}

template <class Tipo> 
ayed_cont::Cola<Tipo>::Cola(const std::size_t cantidad_total) {
   try  {
      detras = new Nodo<Tipo>[cantidad_total];
   }

   catch (std::bad_alloc& ba) {
      std::cerr << "Error en reserva de memoria: " << ba.what() << "\n";
   }

   cantidad_elementos_total = cantidad_total;
}


//-----------------------------------------------------------------------------

template <class Tipo> 
ayed_cont::Cola<Tipo>::~Cola() {
	
	delete[] detras;
	std::cout << "\nCola continua borrada desde el destructor";
}


//-----------------------------------------------------------------------------



template <class Tipo>
void ayed_cont::Cola<Tipo>::queue(const Tipo &dato_a_agregar) {

   if (cantidad_elementos >= cantidad_elementos_total) {
    std::cerr << "No hay mas elementos disponibles (cola a tope)"; 
   }
   else {
    Nodo<Tipo>* nodo_queue = detras+cantidad_elementos++;
    while (nodo_queue != detras) {
      nodo_queue->dato = (nodo_queue-1)->dato;
      --nodo_queue;
    }
      nodo_queue->dato = dato_a_agregar;
   }

}



//-----------------------------------------------------------------------------

template <class Tipo>
Tipo ayed_cont::Cola<Tipo>::unqueue () {

     if (cantidad_elementos <= 0) {
       std::cerr << "No hay mas elementos";
     }
	
     return cantidad_elementos > 0 ? (detras+--cantidad_elementos)->dato : 0;
} 	



//-----------------------------------------------------------------------------


template <class Tipo>
Tipo ayed_cont::Cola<Tipo>::frente () {
    
    return (detras+cantidad_elementos-1)->dato;
  
} 	

//-----------------------------------------------------------------------------

template <class Tipo>
bool ayed_cont::Cola<Tipo>::is_vacia () {

    return cantidad_elementos == 0 ? true : false;
  
} 	

//-----------------------------------------------------------------------------

template <class Tipo>
unsigned ayed_cont::Cola<Tipo>::get_tamanio () {

    return cantidad_elementos;
} 	


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


namespace ayed_cont {


 template <class Tipo> 
 class Lista_Continua{


	public:

	        Lista_Continua(std::size_t  cantidad_total);

	       	void set_nodo(const Tipo &dato_a_agregar, unsigned numero_del_nodo);
		Tipo get_dato_nodo (unsigned numero_del_nodo);
		unsigned get_tamanio();
		              	

	        ~Lista_Continua();
 
	private: 

		Nodo<Tipo>* indice = nullptr;
		std::size_t cantidad_elementos_total = 0;
		
		
 };

}

//-----------------------------------------------------------------------------


template <class Tipo> 
ayed_cont::Lista_Continua<Tipo>::Lista_Continua(std::size_t cantidad_total) {

   try  {
      indice = new Nodo<Tipo>[cantidad_total];
   }

   catch (std::bad_alloc& ba) {
      std::cerr << "Error en reserva de memoria: " << ba.what() << "\n";
   }

   cantidad_elementos_total = cantidad_total; 
}

//-----------------------------------------------------------------------------

template <class Tipo> 
ayed_cont::Lista_Continua<Tipo>::~Lista_Continua() {
	
	delete[] indice;
	std::cout << "\nLista continua borrada desde el destructor";
}


//-----------------------------------------------------------------------------


template <class Tipo> 
void ayed_cont::Lista_Continua<Tipo>::set_nodo(const Tipo &dato_a_agregar, unsigned posicion) {

   (indice+posicion)->dato = dato_a_agregar;
}

//-----------------------------------------------------------------------------

template <class Tipo> 
Tipo ayed_cont::Lista_Continua<Tipo>::get_dato_nodo (unsigned posicion) {

   return (indice+posicion)->dato;
}


//-----------------------------------------------------------------------------

template <class Tipo>
unsigned ayed_cont::Lista_Continua<Tipo>::get_tamanio () {

    return cantidad_elementos_total;
} 