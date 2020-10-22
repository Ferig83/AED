#include "poligono.h"


bool poligono::ExtraerVerticePoligono (std::istream &istr, poligono::Vertice &vertice) {
	istr >> vertice.x;
	istr >> vertice.y;
	return (bool) istr;
}

bool poligono::ExtraerCantidadVerticesPoligono (std::istream &istr, unsigned &cantidad_vertices) {
	istr >> cantidad_vertices;
	return (bool) istr;
}



bool poligono::ExtraerColorPoligono (std::istream &istr, color::Color_RGB &color) {
	
	unsigned short byte_leido;
	istr >> byte_leido;
	byte_leido = byte_leido > 255 ? 255 : byte_leido;
	byte_leido = byte_leido < 0 ? 0 : byte_leido;
	color.R = byte_leido;
	istr >> byte_leido;
	byte_leido = byte_leido > 255 ? 255 : byte_leido;
	byte_leido = byte_leido < 0 ? 0 : byte_leido;
	color.G = byte_leido;
	istr >> byte_leido;
	byte_leido = byte_leido > 255 ? 255 : byte_leido;
	byte_leido = byte_leido < 0 ? 0 : byte_leido;
	color.B = byte_leido;
	return (bool) istr;
}


bool poligono::ExtraerSeparador(std::istream &istr) {
	istr.clear();
	char caracter_leido = 0;
	istr >> caracter_leido;
	return ((istr) && (caracter_leido == '/'));
	
}


bool poligono::ExtraerPoligono (std::istream &istr, poligono::Poligono& poligono) {

 	ExtraerColorPoligono(istr, poligono.color);

	ExtraerCantidadVerticesPoligono(istr, poligono.cantidad_vertices);

	for (unsigned i = 0; i < poligono.cantidad_vertices; ++i) {
		ExtraerVerticePoligono(istr, poligono.vertices[i]);	
	}
	
	return ExtraerSeparador(istr);
}


//-----------------------------------------------------------------------------


bool poligono::EnviarVerticePoligono (std::ostream &ostr, poligono::Vertice vertice) {
	ostr << vertice.x << ' ' << vertice.y << ' ';
	return (bool) ostr;
}

bool poligono::EnviarCantidadVerticesPoligono (std::ostream &ostr, unsigned cantidad_vertices) {
	ostr << cantidad_vertices << ' ';
	return (bool) ostr;
}


bool poligono::EnviarColorPoligono (std::ostream &ostr, color::Color_RGB color) {
	
	ostr << (unsigned) color.R << ' ' << (unsigned) color.G << ' ' << (unsigned) color.B << ' ';
	return (bool) ostr;
}

bool poligono::EnviarPoligono (std::ostream &ostr, const poligono::Poligono &poligono) {
	poligono::EnviarColorPoligono(ostr, poligono.color);
	poligono::EnviarCantidadVerticesPoligono (ostr, poligono.cantidad_vertices);
	for (int i = 0; i < poligono.cantidad_vertices; ++i) {
		EnviarVerticePoligono(ostr, poligono.vertices.at(i));
	}
	ostr << " / ";
	return (bool) ostr;
}


//-----------------------------------------------------------------------------

poligono::Poligono poligono::inicializarPoligono(unsigned cantidad, const std::array<poligono::Vertice, VERTICES_MAXIMOS> &vertices, color::Color_RGB color) {

	assert((vertices.size() >= 3) && (vertices.size() <= VERTICES_MAXIMOS));

	poligono::Poligono poligono;
	poligono.cantidad_vertices = cantidad;
	poligono.color = color;
	poligono.vertices = vertices;
	return poligono;
}



void  poligono::addVertice(poligono::Poligono &t, poligono::Vertice vertice) {
	assert (t.cantidad_vertices < VERTICES_MAXIMOS);
	t.cantidad_vertices += 1;
	t.vertices[t.cantidad_vertices-1] = vertice;
}

 
void poligono::removeVertice(poligono::Poligono &t) {
	t.cantidad_vertices -= 1;
}



void poligono::imprimirVertices(const poligono::Poligono &t) {
	for (int i = 0; i < t.cantidad_vertices; ++i){ 
		std::cout << "\n(" << t.vertices[i].x << " ; " << t.vertices[i].y << ")";
	} 
}


poligono::Vertice poligono::getVertice(const poligono::Poligono &t, unsigned n) {
	assert(t.cantidad_vertices > n);
	return t.vertices[n];
}


double poligono::getPerimetro(const poligono::Poligono &t) {
	double valor = 0;
	for (int i = 0; i < (t.cantidad_vertices - 1); ++i){
	 	valor = valor + std::sqrt(std::pow(t.vertices[i].x - t.vertices[i+1].x,2.0) + std::pow(t.vertices[i].y - t.vertices[i+1].y,2.0));
	}
	valor = valor + std::sqrt(std::pow(t.vertices[t.cantidad_vertices-1].x - t.vertices[0].x,2.0) + std::pow(t.vertices[t.cantidad_vertices-1].y - t.vertices[0].y,2.0));
	return valor;
}


double poligono::getLongitud(const poligono::Poligono &t, unsigned i, unsigned fin) {
	double valor = 0;
	for (; i < (fin - 1); ++i){
	 	valor = valor + std::sqrt(std::pow(t.vertices[i].x - t.vertices[i+1].x,2.0) + std::pow(t.vertices[i].y - t.vertices[i+1].y,2.0));
	}
	return valor;
}

double poligono::getDistancia(const poligono::Poligono &t, unsigned i, unsigned j) {
	return std::sqrt(std::pow(t.vertices[i].x - t.vertices[j].x,2.0) + std::pow(t.vertices[i].y - t.vertices[j].y,2.0));
}

double poligono::getAngulo(const poligono::Poligono &t, unsigned i) {

		double a,b,c;

		// Optimizable, hacerlo lo más branchless posible

		if (i==t.cantidad_vertices-1) {


			a = std::pow(t.vertices[i - 2].x - t.vertices[i-3].x, 2.0) + std::pow(t.vertices[i-2].y - t.vertices[i-3].y,2.0);
			b = std::pow(t.vertices[i - 1].x - t.vertices[i-2].x, 2.0) + std::pow(t.vertices[i-1].y - t.vertices[i-2].y,2.0);
			c = std::pow(t.vertices[i - 1].x - t.vertices[0].x, 2.0) + std::pow(t.vertices[i-1].y - t.vertices[i-0].y,2.0);
		} else if (i == 0) {
		
			a = std::pow(t.vertices[1].x - t.vertices[2].x,2.0) + std::pow(t.vertices[1].y - t.vertices[2].y,2.0);
			b = std::pow(t.vertices[0].x - t.vertices[1].x,2.0) + std::pow(t.vertices[0].y - t.vertices[1].y,2.0);
			c = std::pow(t.vertices[0].x - t.vertices[t.cantidad_vertices -1].x,2.0) + std::pow(t.vertices[0].y - t.vertices[t.cantidad_vertices -1].y,2.0);
		}  else {
		
			a = std::pow(t.vertices[i-2].x - t.vertices[i].x,2.0) + std::pow(t.vertices[i-2].y - t.vertices[i].y,2.0);
			b = std::pow(t.vertices[i - 1].x - t.vertices[i-2].x,2.0) + std::pow(t.vertices[i-1].y - t.vertices[i-2].y,2.0);
			c = std::pow(t.vertices[i - 1].x - t.vertices[i].x,2.0) + std::pow(t.vertices[i-1].y - t.vertices[i].y,2.0);
			
		}	
		a = std::sqrt(a);	

		b = std::sqrt(b);
		c = std::sqrt(c);
		return (b*c != 0.0 ? std::acos((std::pow(a,2.0) - std::pow(b,2.0) - std::pow(c,2.0)) / (b * c * (-1.0))) : 0);

}


color::Color_RGB poligono::getColor(const poligono::Poligono &t) {
		return t.color;		
}

void poligono::setColor(poligono::Poligono &t, color::Color_RGB color) {
		t.color = color;		
}


unsigned poligono::getCantidadLadosCerrado(const poligono::Poligono &t) {
	return t.cantidad_vertices;
}

unsigned poligono::getCantidadLadosAbierto(const poligono::Poligono &t) {
	return (t.cantidad_vertices - 1);
}

unsigned poligono::getCantidadVertices(const poligono::Poligono &t) {
	return t.cantidad_vertices;
}

void poligono::setVertice(poligono::Poligono &t, unsigned i, Vertice vertice) {
	t.vertices[i] = vertice;
}




