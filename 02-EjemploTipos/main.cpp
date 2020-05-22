/******************************************************
*
*  Trabajo Práctico N° 3 
*
*  Ejemplo de Tipos de Datos
*
*  "La reproducción del Uteneanus Algoritmicus"  
*
*  Por Fernando Riganti (156.149-0)
*  20 de Mayo de 2020
*
*
*******************************************************/


/*------------------------------------------------------------------------- 

El "Uteneanus Algoritmicus" es un pequeño mamífero que pasta en los alrededores 
del Campus. Su reproducción requiere condiciones muy especiales: Solo se reproduce
si el promedio de los alumnos de Algoritmos y Estructura de Datos supera el 6, 
ya que es muy sensible las hormonas liberadas por el estrés de los alumnos. 
Además, la temperatura del ambiente debe ser entre -1 °C a 20 °C  ya que son muy 
sensibles al calor y cuando es más caluroso se alejan unos de otros. Si hace
mucho frío tampoco se reproducirán.

Tomamos en el laboratorio dos especimenes del tipo 2A (correspondientes a dicho animal
según clasificación biológica BIOUTN), y vemos si pueden reproducirse. 

Para verificar las condiciones, tomamos cuatro alumnos recién evaluados en los exámenes
de AED y los hacemos sentar alrededor de la jaulita donde se encuentran dos especímenes
de Uteneanus Algoritmicus (coloquialmente llamados "Conejo de Campus");

-----------------------------------------------------------------------*/

#include <cassert>
#include <string>

int main()
{

	// Constantes:

		// Nombre y tipo de especímenes:

	 	const std::string especimen1_nombre = "0001-2A";
		const std::string especimen2_nombre = "0002-2A";

		// Maduración de los especímenes:

		const bool especimen1_adulto = true;
		const bool especimen2_adulto = true;

		// Sexo de los especímenes (M: Macho, H: Hembra)

		char especimen1_sexo = 'M';
		char especimen2_sexo = 'H';
		
		// Conversión a mayúsculas (demuestro además que podemos sumar en char
	
		if ((especimen1_sexo == 'm') or (especimen1_sexo == 'h')) especimen1_sexo -= 32;
		if ((especimen2_sexo == 'm') or (especimen2_sexo == 'h')) especimen2_sexo -= 32;
		
		// Notas de los alumnos:

		const unsigned int nota1 = 6;
		const unsigned int nota2 = 8;
		const unsigned int nota3 = 4;
		const unsigned int nota4 = 9;


		// Temperatura del laboratorio (en grados Celsius)

		const int temperatura = 18;
		


//-----------------------------------------------------------------------------



	// Variables:

	bool posibilidad_biologica = false;
	double promedio = 0.0;
	bool especimen1_macho = especimen1_sexo == 'M' ? true : false; 
	bool especimen2_macho = especimen2_sexo == 'M' ? true : false;


	// Chequeo que los especimenes sean del tipo 2A, sino salgo del programa 

	assert(especimen1_nombre.substr(5, 2) == "2A");
	assert(especimen2_nombre.substr(5, 2) == "2A");

	
	// Chequeo si la reproducción es posible por el sexo y maduración de los especímenes	

	posibilidad_biologica = (especimen1_adulto and especimen2_adulto) and (especimen1_macho xor especimen2_macho);
	
	assert(posibilidad_biologica == true);

	// Chequeo si la temperatura es adecuada:

	assert((temperatura >= -1) || (temperatura <= 20));

	// Chequeo si el promedio de los alumnos es igual o mayor a seis:

	promedio = (nota1 + nota2 + nota3 + nota4) / 4.0; 

	assert (promedio >= 6.0);
	 
	return(0);
}
