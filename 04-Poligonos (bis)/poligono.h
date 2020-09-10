#pragma once

#include <iostream>
#include <array>
#include <cmath>
#include <cassert>
#include "color.h"

#ifndef VERTICES_MAXIMOS
#define VERTICES_MAXIMOS 20
#endif


namespace poligono {


//--- ESTRUCTURAS ---------------------------------------------------


struct Vertice {
	double x,y;			
};

struct Poligono {
	color::Color_RGB color;
	unsigned cantidad_vertices;
	std::array<Vertice,VERTICES_MAXIMOS> vertices;     
};



//--- PROTOTIPOS DE FUNCIONES ---------------------------------------


Poligono inicializarPoligono (unsigned cantidad, const std::array<poligono::Vertice, VERTICES_MAXIMOS> &vertices, color::Color_RGB color);
void imprimirVertices(const Poligono &t);
Vertice getVertice(const Poligono &t, unsigned n);
double getPerimetro(const Poligono &t);
double getLongitud(const Poligono &t, unsigned i, unsigned fin);
double getDistancia(const Poligono &t, unsigned i, unsigned j);
double getAngulo(const Poligono &t, unsigned i); 
color::Color_RGB getColor(const Poligono &t);
void setColor(Poligono &t, color::Color_RGB color);
void addVertice(Poligono &t, Vertice vertice);
void removeVertice(Poligono &t);
void setVertice(Poligono &t, unsigned i, Vertice vertice);
unsigned getCantidadLadosAbierto(const Poligono &t);
unsigned getCantidadLadosCerrado(const Poligono &t);
unsigned getCantidadVertices(const Poligono &t);



}