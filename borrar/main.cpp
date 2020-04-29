/*** Adición ************** 
 *
 *  por Fernando Riganti
 *  25/04/2020
 *
 *  
 **************************/


#include <iostream>

int main ()
{
	
	// Usamos el estilo de declarar las variables al principio
	
	int numero1, numero2, resultado;

	std::cout << "Ingrese el primer número: ";
	std::cin >> numero1;
	std::cout << "Ingrese el segundo número: ";
	std::cin >> numero2;
	resultado = numero1 + numero2;
	std::cout << "El resultado es: " << resultado << std::endl;
	return 0;
}
