/*--- VERSIONES CONTIGUAS ---*/


namespace ayed_cont {

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


template <class Tipo> 
class Lista_Enlazada {

	public:

	        Lista_Enlazada(unsigned cantidad_total);

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


template <class Tipo> 
ayed_cont::Lista_Enlazada<Tipo>::Lista_Enlazada(unsigned cantidad_total) {

   try  {
      primer_nodo = new Nodo<Tipo>[cantidad_total];
   }

   catch (std::bad_alloc& ba) {
      std::cerr << "Error en reserva de memoria: " << ba.what() << "\n";
   }

   cantidad_nodos = cantidad_total;
}

//-----------------------------------------------------------------------------

template <class Tipo> 
ayed_cont::Lista_Enlazada<Tipo>::Lista_Enlazada(unsigned cantidad_total) {

   try  {
      primer_nodo = new Nodo<Tipo>[cantidad_total];
   }

   catch (std::bad_alloc& ba) {
      std::cerr << "Error en reserva de memoria: " << ba.what() << "\n";
   }

   cantidad_nodos = cantidad_total;
}


template <class Tipo>
void ayed_cont::Lista_Enlazada<Tipo>::agregar_en(Tipo dato_a_agregar, unsigned posicion) {

   
   primer_nodo + posicion =

}
