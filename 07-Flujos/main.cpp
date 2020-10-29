
/******************************************
*
*  Trabajo Práctico N° 5 - Flujos
*
*  por Fernando Gustavo Riganti (159.146-0)
*
*
*******************************************/


#include "poligono.h"
#include <cassert>



int main()
{

	// -------- Filtramos los polígonos cuyo perímetro es menor a 10.0 

	const double filtro = 10.0;
	
	std::ifstream flujo_entrada_con_filtro;
	std::ofstream flujo_salida_con_filtro;
	
	flujo_entrada_con_filtro.open("flujo_entrada_con_filtro.pol");
	flujo_salida_con_filtro.open("flujo_salida_con_filtro.pol");

	poligono::Poligono poligono_a_filtrar;
	
	for (;poligono::ExtraerPoligono(flujo_entrada_con_filtro,poligono_a_filtrar);) {
		if (!(poligono::getPerimetro(poligono_a_filtrar) < filtro)) {
		 poligono::EnviarPoligono(flujo_salida_con_filtro, poligono_a_filtrar);
		}

	}

	flujo_entrada_con_filtro.close();
	flujo_salida_con_filtro.close();


      // --------- Prueba por entrada de archivo
      
	std::ifstream flujo_entrada;
	flujo_entrada.open("flujo_entrada.pol");
	poligono::Poligono prueba_entrada[3];

	// Extraigo los polígonos
	
	for (int i = 0; poligono::ExtraerPoligono(flujo_entrada, prueba_entrada[i]) ; ++i);


	// Pruebas visuales

	for (int i = 0; i < 3; i++) {

		std::cout << "Poligono " << i+1 << " (" << prueba_entrada[i].cantidad_vertices << " vertices):" << std::endl;
		std::cout << " Colores:" << std::endl;
		std::cout << "   R:" << (unsigned) prueba_entrada[i].color.R;
		std::cout << "   G:" << (unsigned) prueba_entrada[i].color.G;
		std::cout << "   B:" << (unsigned) prueba_entrada[i].color.B << std::endl;
		std::cout << " Vertices:" << std::endl;
		poligono::imprimirVertices(prueba_entrada[i]);
		std::cout << std::endl << "-------------------------------------------------------------" << std::endl;

	}
	flujo_entrada.close();


      // ---------  Pruebas hechas con "cin"
     

	std::cout << std::endl << "Ingrese dos poligonos" << std::endl;

	poligono::Poligono prueba_entrada_cin[2];

	for (int i = 0; poligono::ExtraerPoligono(std::cin, prueba_entrada_cin[i]) ; ++i);

	// Pruebas visuales

	for (int i = 0; i < 2; i++) {

		std::cout << "Poligono " << i+1 << " (" << prueba_entrada_cin[i].cantidad_vertices << " vertices):" << std::endl;
		std::cout << " Colores:" << std::endl;
		std::cout << "   R:" << (unsigned) prueba_entrada_cin[i].color.R;
		std::cout << "   G:" << (unsigned) prueba_entrada_cin[i].color.G;
		std::cout << "   B:" << (unsigned) prueba_entrada_cin[i].color.B << std::endl;
		std::cout << " Vertices:" << std::endl;
		poligono::imprimirVertices(prueba_entrada_cin[i]);
		std::cout << std::endl << "-------------------------------------------------------------" << std::endl;

	}




	// -------- Introduzco los polígonos de la pruebas para enviarlos al un flujo de salida      

	std::ofstream salida;
	
	salida.open("flujo_salida.pol");
	EnviarPoligono(salida, prueba_entrada[0]);
	EnviarPoligono(salida, prueba_entrada[2]);
	salida.close();	

		
}
