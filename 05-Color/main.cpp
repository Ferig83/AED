
/******************************************
*
*  Trabajo Práctico N° 5 - Color
*
*  por Fernando Gustavo Riganti (159.146-0)
*
*
*******************************************/



#include <cassert>
#include "color.h"

int main () {

	// Probamos la función isIgual, la cual nos será práctica para el resto de los assert

	assert (color::isIgual({255,0,0}, color::rojo));

	// Prueba de colores secundarios, blanco y negro, creados con funciones sumarColor y restarColor

	assert (color::isIgual(color::blanco,   {255,255,255}));
	assert (color::isIgual(color::negro,    {0,0,0}));
	assert (color::isIgual(color::amarillo, {255,255,0}));
	assert (color::isIgual(color::magenta,  {255,0,255}));
	assert (color::isIgual(color::cyan,  	 {0,255,255}));

	// Probamos si sumarColor y restarColor exceden el rango de los canales: [0,255]

	assert (color::isIgual (color::sumarColor(color::blanco, color::blanco), {255,255,255}) );
	assert (color::isIgual (color::restarColor(color::negro, color::negro), {0,0,0}));

	// Probamos la operación Mezclar, la cual debemos meter dos colores y sus respectivos porcentajes en números enteros

	assert (color::isIgual(color::mezclarColor(color::azul,color::magenta, 50, 100), {127,0,191})) ; 
	
	// Probamos la función getComplementario

	assert (color::isIgual(color::getComplementario({10,255,50}), {245,0,205}));

	// Probamos getHtmlRgb

	assert (color::getHtmlRgb({11,0,255}) == "rgb(11,0,255)" );

	// Probamos getHtmlHex

	assert (color::getHtmlHex({0,5,11}) == "#00050B");
	assert (color::getHtmlHex({255,0,255}) == "#FF00FF");
		
	// Por último creamos el archivo .SVG con el mensaje "Hola a todos!", con color cyan de fondo y su
	// complementario (rojo) de fondo.

  	color::CrearSvgConTextoEscritoEnAltoContraste("hola.svg", "Hola a todos!", color::cyan);

}