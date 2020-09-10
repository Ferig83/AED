#include "color.h"


color::Color_RGB color::mezclarColor(color::Color_RGB color1, color::Color_RGB color2, uint8_t porcentaje1, uint8_t porcentaje2) {
	color::Color_RGB mezcla;
	
	porcentaje1 > 255 ? 255 : porcentaje1;
	porcentaje2 > 255 ? 255 : porcentaje2;

	mezcla.R = ( ((color1.R * porcentaje1) / 100) + ((color2.R * porcentaje2) / 100) ) / 2 > 255 ? 255: 
	(((color1.R * porcentaje1) / 100) + ((color2.R * porcentaje2) / 100) ) / 2 ;


	mezcla.G = ( ((color1.G * porcentaje1) / 100) + ((color2.G * porcentaje2) / 100) ) / 2 > 255 ? 255: 
	(((color1.G * porcentaje1) / 100) + ((color2.G * porcentaje2) / 100) ) / 2 ;


	mezcla.B = ( ((color1.B * porcentaje1) / 100) + ((color2.B * porcentaje2) / 100) ) / 2 > 255 ? 255: 
	( ((color1.B * porcentaje1) / 100) + ((color2.B * porcentaje2) / 100) ) / 2 ;

	return mezcla;
	
}


color::Color_RGB color::sumarColor(color::Color_RGB color1, color::Color_RGB color2) {
	color::Color_RGB suma;
	suma.R = color1.R + color2.R > 255 ? 255: color1.R + color2.R;
	suma.G = color1.G + color2.G > 255 ? 255: color1.G + color2.G;
	suma.B = color1.B + color2.B > 255 ? 255: color1.B + color2.B;	
	return suma;
}


color::Color_RGB color::restarColor(color::Color_RGB color1, color::Color_RGB color2) {
	color::Color_RGB resta;
	resta.R = color1.R - color2.R < 0 ? 0: color1.R - color2.R;
	resta.G = color1.G - color2.G < 0 ? 0: color1.G - color2.G;
	resta.B = color1.B - color2.B < 0 ? 0: color1.B - color2.B;	
	return resta;
}


color::Color_RGB color::getComplementario(color::Color_RGB color) {
	color::Color_RGB complementario;
	complementario.R = 255 - color.R; 
	complementario.G = 255 - color.G; 
	complementario.B = 255 - color.B;
	return complementario; 
}


std::string color::getHex(int valor) {
	std::string cadena;
	char valorHex[2];
	sprintf(valorHex,"%X",valor);
	if (valor < 16 ) {
     	     cadena.insert(0,1,'0');
     	     cadena.insert(1,1,valorHex[0]);
    	} else {
    	     cadena.insert(0,1,valorHex[0]);
  	     cadena.insert(1,1,valorHex[1]);     
  	} 

	// Descomentar si se necesita que esté en minúsculas
  	// transform(cadena.begin(), cadena.end(), cadena.begin(), ::tolower);   
 	return cadena;
} 


std::string color::getHtmlRgb(color::Color_RGB color) {
	return ("rgb(" + std::to_string(color.R) + "," +
	       std::to_string(color.G) + "," +
	       std::to_string(color.B) + ")") ;
}

std::string color::getHtmlHex(color::Color_RGB color) {
	return ("#" + color::getHex(color.R) + color::getHex(color.G) + color::getHex(color.B));
}


void color::CrearSvgConTextoEscritoEnAltoContraste(std::string nombre_archivo, std::string texto, color::Color_RGB color) {

	std::ofstream archivo;
	archivo.open(nombre_archivo);
	archivo << "<svg xmlns=\"http://www.w3.org/2000/svg\">"
		<< "<rect x=\"0\" y=\"0\" height=\"30\" width=\"120\" "
		<< "style=\"fill:" + color::getHtmlHex(color::getComplementario(color)) + "\"/>"
		<< "<text x=\"5\" y=\"18\" style=\"fill:" + color::getHtmlRgb(color)
		<< "\">"<<texto
		<< "</text></svg>";
 	archivo.close();
}

bool color::isIgual(color::Color_RGB color1, color::Color_RGB color2) {
	return ((color1.R == color2.R) && (color1.G == color2.G) && (color1.B == color2.B));
}
