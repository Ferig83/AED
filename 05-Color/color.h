#pragma once

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>


namespace color {

// Estructuras

struct Color_RGB {
	uint8_t R;
	uint8_t G;
	uint8_t B;
};



// Prototipos de funciones

Color_RGB mezclarColor(Color_RGB color1, Color_RGB color2, uint8_t porcentaje1, uint8_t porcentaje2);

Color_RGB sumarColor(Color_RGB color1, Color_RGB color2);

Color_RGB restarColor(Color_RGB color1, Color_RGB color2);

Color_RGB getComplementario(Color_RGB color);

std::string getHex(int valor);

std::string getHtmlRgb(Color_RGB color);

std::string getHtmlHex(Color_RGB color);

void CrearSvgConTextoEscritoEnAltoContraste(std::string nombre_archivo, std::string texto, Color_RGB color);

bool isIgual(Color_RGB color1, Color_RGB color2);

// Constantes

const Color_RGB rojo{255,0,0};
const Color_RGB verde{0,255,0};
const Color_RGB azul{0,0,255};
const Color_RGB amarillo = sumarColor(rojo, verde);
const Color_RGB magenta = sumarColor(rojo, azul);
const Color_RGB cyan = sumarColor(verde, azul);
const Color_RGB blanco = sumarColor(sumarColor(verde, azul), sumarColor(rojo,azul));
const Color_RGB negro = restarColor(rojo,rojo);

}