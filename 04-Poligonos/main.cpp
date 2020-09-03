
/******************************************
*
*  Trabajo Práctico N° 4 - Polígonos y triángulos
*
*  por Fernando Gustavo Riganti (159.146-0)
*
*
*******************************************/


#include <iostream>
#include <array>
#include <cmath>
#include <cassert>


#define VERTICES_MAXIMOS 20


//--- ENUMERACIONES Y CONSTANTES ------------------------------------

enum Tipo_Figura {
	triangulo,
	poligono
};


//--- ESTRUCTURAS ---------------------------------------------------

struct ColorRGB {
	char rojo = 0x00;
	char verde = 0x00;
	char azul = 0x00;
};

struct Vertice {
	double x,y;			
};

struct Triangulo{
	ColorRGB color;
	unsigned cantidad_vertices;
	std::array<Vertice,3> vertices;	
};

struct Poligono {
	ColorRGB color;
	unsigned cantidad_vertices;
	std::array<Vertice,VERTICES_MAXIMOS> vertices;     
};


//--- PROTOTIPOS DE FUNCIONES ---------------------------------------


template <typename T, typename G> T Inicializar_Figura(G &vertices);
template <typename T> void Mostrar_Todos_Los_Vertices(const T &t);
template <typename T> Vertice getVertice(const T &t, int n);
template <typename T> double getPerimetro(const T &t);
template <typename T> double getLongitud(const T &t, int i, int fin);
template <typename T> double getDistancia(const T &t, int i, int j);
template <typename T> double getAngulo(const T &t, int i); 
template <typename T> ColorRGB getColor(const T &t);
template <typename T> void setColor(T &t, ColorRGB color);
void AgregarVerticeAlFinal(Poligono &t, Vertice vertice);
void BorrarUltimoVertice(Poligono &t);
template <typename T> unsigned getCantidadVertices(const T &t);



//--- MAIN ---------------------------------------------------------


int main()
{
	std::array<Vertice,5> vertices_pentagono = {0.4, 3.2,
			 			    2.1, 1.4,
			  			    1.2, 4.4,
					 	    5.5, 6.6,
					  	    4.2, 1.2};


	std::array<Vertice,3> vertices_triangulo = {0.0, 1.0, 
  						    1.0, 1.0,
			   			    1.0, 0.0};
				

	Poligono pentagono = Inicializar_Figura<Poligono>(vertices_pentagono);
	Triangulo triangulo = Inicializar_Figura<Triangulo>(vertices_triangulo);
	

	
	Mostrar_Todos_Los_Vertices(triangulo);
	
	std::cout << std::endl << "Angulo: " << getAngulo(triangulo, 1);
	
	return 0;
}



//--- DEFINICION DE FUNCIONES ---------------------------------------


template <typename T, typename G> 
T Inicializar_Figura(G &vertices) {

	assert((vertices.size() >= 3) && (vertices.size() <= VERTICES_MAXIMOS));

	T poligono;
	poligono.cantidad_vertices = vertices.size();

	for (int i = 0; i < poligono.cantidad_vertices; ++i){ 
		poligono.vertices[i].x = vertices[i].x;
		poligono.vertices[i].y = vertices[i].y;
	} 

	return poligono;
}


template <typename T> 
void Mostrar_Todos_Los_Vertices(const T &t) {
	for (int i = 0; i < t.cantidad_vertices; ++i){ 
		std::cout << "\n(" << t.vertices[i].x << " ; " << t.vertices[i].y << ")";
	} 
}


template <typename T> 
Vertice getVertice(const T &t, int n) {
	assert(t.cantidad_vertices > n);
	return t.vertice[n];
}


template <typename T> 
double getPerimetro(const T &t) {
	double valor = 0;
	for (int i = 0; i < (t.cantidad_vertices - 1); ++i){
	 	valor = valor + sqrt(pow(t.vertice[i].x - t.vertice[i+1].x,2.0) + pow(t.vertice[i].y - t.vertice[i+1].y,2.0));
	}
	valor = valor + sqrt(pow(t.vertice[t.cantidad_vertices-1].x - t.vertice[0].x,2.0) + pow(t.vertice[t.cantidad_vertices-1].y - t.vertice[0].y,2.0));
	return valor;
}

template <typename T> 
double getLongitud(const T &t, int i, int fin) {
	double valor = 0;
	for (; i < (fin - 1); ++i){
	 	valor = valor + sqrt(pow(t.vertice[i].x - t.vertice[i+1].x,2.0) + pow(t.vertice[i].y - t.vertice[i+1].y,2.0));
	}
	return valor;
}

template <typename T> 
double getDistancia(const T &t, int i, int j) {
	return sqrt(pow(t.vertice[i].x - t.vertice[j].x,2.0) + pow(t.vertice[i].y - t.vertice[j].y,2.0));
}

template <typename T> 
double getAngulo(const T &t, int i) {

		double a,b,c;

		// Optimizable, hacerlo lo más branchless posible

		if (i==t.cantidad_vertices-1) {


			a = pow(t.vertices[i - 2].x - t.vertices[i-3].x, 2.0) + pow(t.vertices[i-2].y - t.vertices[i-3].y,2.0);
			b = pow(t.vertices[i - 1].x - t.vertices[i-2].x, 2.0) + pow(t.vertices[i-1].y - t.vertices[i-2].y,2.0);
			c = pow(t.vertices[i - 1].x - t.vertices[0].x, 2.0) + pow(t.vertices[i-1].y - t.vertices[i-0].y,2.0);
		} else if (i == 0) {
		
			a = pow(t.vertices[1].x - t.vertices[2].x,2.0) + pow(t.vertices[1].y - t.vertices[2].y,2.0);
			b = pow(t.vertices[0].x - t.vertices[1].x,2.0) + pow(t.vertices[0].y - t.vertices[1].y,2.0);
			c = pow(t.vertices[0].x - t.vertices[t.cantidad_vertices -1].x,2.0) + pow(t.vertices[0].y - t.vertices[t.cantidad_vertices -1].y,2.0);
		}  else {
		
			a = pow(t.vertices[i-2].x - t.vertices[i].x,2.0) + pow(t.vertices[i-2].y - t.vertices[i].y,2.0);
			b = pow(t.vertices[i - 1].x - t.vertices[i-2].x,2.0) + pow(t.vertices[i-1].y - t.vertices[i-2].y,2.0);
			c = pow(t.vertices[i - 1].x - t.vertices[i].x,2.0) + pow(t.vertices[i-1].y - t.vertices[i].y,2.0);
			
		}	
		a = sqrt(a);	

		b = sqrt(b);
		c = sqrt(c);
		return (b*c != 0.0 ? acos((pow(a,2.0) - pow(b,2.0) - pow(c,2.0)) / (b * c * (-1.0))) : 0);

}


template <typename T> 
ColorRGB getColor(const T &t) {
		return t.color;		
}

template <typename T> 
void setColor(T &t, ColorRGB color) {
		t.color = color;		
}

void AgregarVerticeAlFinal(Poligono &t, Vertice vertice) {
	assert (t.cantidad_vertices < VERTICES_MAXIMOS);
	t.cantidad_vertices += 1;
	t.vertices[t.cantidad_vertices] = vertice;
}

 
void BorrarUltimoVertice(Poligono &t) {
	t.cantidad_vertices -= 1;
}

template <typename T> 
unsigned getCantidadVertices(const T &t) {
	return t.cantidad_vertices;
}







