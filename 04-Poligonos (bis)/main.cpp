
/******************************************
*
*  Trabajo Práctico N° 4 - Polígonos y triángulos
*
*  por Fernando Gustavo Riganti (159.146-0)
*
*
*******************************************/


#include "poligono.h"
#include <cassert>



int main()
{
	// Para hacer las pruebas más cómodas, vamos a inicializar un polígono de prueba

	
	poligono::Poligono poligono_test = poligono::inicializarPoligono(6, {0.0 , 0.0,
									  0.0 , 2.0,
		    		     		 			  3.5 , 2.0, 		
	    		  	     					  3.5 , 9.0,
									  18.5, 9.0,
				     					  18.5, 0.0}, color::rojo);
	
	// Probamos getVertice

	assert (poligono::getVertice(poligono_test, 0).x == 0.0 && poligono::getVertice(poligono_test, 0).y == 0.0);
	assert (poligono::getVertice(poligono_test, 1).x == 0.0 && poligono::getVertice(poligono_test, 1).y == 2.0);
	assert (poligono::getVertice(poligono_test, 4).x == 18.5 && poligono::getVertice(poligono_test, 4).y == 9.0);
	
	// Probamos getCantidadVertices, addVertice y removeVertice 

	assert(poligono::getCantidadVertices(poligono_test) == 6);

	poligono::addVertice(poligono_test, {14.0,54.0});
	poligono::addVertice(poligono_test, {1.5,100.0});

	
	assert (poligono::getCantidadVertices(poligono_test) == 8);
	assert (poligono::getVertice(poligono_test, 6).x == 14.0 && poligono::getVertice(poligono_test, 6).y == 54.0);
	assert (poligono::getVertice(poligono_test, 7).x == 1.5 && poligono::getVertice(poligono_test, 7).y == 100.0);


	poligono::removeVertice(poligono_test);
	assert (poligono::getCantidadVertices(poligono_test) == 7);
	poligono::removeVertice(poligono_test);
	assert (poligono::getCantidadVertices(poligono_test) == 6);
	
	
	// Probamos setVertice

	poligono::setVertice(poligono_test, 0, {0.6, 7.0});
	assert (poligono::getVertice(poligono_test, 0).x == 0.6 && poligono::getVertice(poligono_test, 0).y == 7.0);


	poligono::setVertice(poligono_test, 0, {0.0, 0.0});
	assert (poligono::getVertice(poligono_test, 0).x == 0.0 && poligono::getVertice(poligono_test, 0).y == 0.0);


	// Probamos getCantidadLados, el cual tenemos dos: cerrado (el polígono es cerrado) y abierto

	assert (poligono::getCantidadLadosCerrado(poligono_test) == 6);
	assert (poligono::getCantidadLadosAbierto(poligono_test) == 5);
	
	// Y por último probamos el perímetro 		

	
	assert (poligono::getPerimetro(poligono_test) >= 54.999 && poligono::getPerimetro(poligono_test) <= 55.501);
			
	return 0;
}