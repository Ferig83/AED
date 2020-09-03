## TP 04-Polígonos

---

### Análisis del problema

#### Enunciado
 Crear tipos de datos para polígonos y triángulos, proponiendo y definiendo distintas operaciones.

#### Restricciones
No utilizar vectores dinámicos (ej: std::vector).  

#### Hipotesis de trabajo

Debemos representar a los polígonos y triángulos como un conjunto de vértices en el plano R^2. Por definición, un polígono no debería tener menos de tres vértices, por lo que el polígono más pequeño es el triángulo. Además, cada polígono tendrá un color y vamos a utilizar el sistema RGB de 24 bits para representarlo (sin el "alpha" que se suele utilizar para transparencia): El sistema consiste en representar el rojo, verde y azúl con un byte cada uno y en ese orden, siendo 00h la ausencia del color y FFh el máximo posible (por ejemplo, el 00FF00h es un verde intenso).

Como operaciones vamos a definir las siguientes:

(en desarrollo)
Poligono Inicializar_Figura(G &vertices);
void Mostrar_Todos_Los_Vertices(T &t);
Vertice Mostrar_Vertice_En(T &t, int n);
double getPerimetro(T &t);
double getLongitud(T &t, int i, int fin);
double getDistancia(T &t, int i, int j);
double getAngulo(T &t, int i); 
ColorRGB getColor(T &t);
void setColor(T &t, ColorRGB color);
void AgregarVerticeAlFinal(T &t, Vertice vertice);
void BorrarUltimoVertice(T &t);
int getCantidadVertices(T &t);


---
### Solución

(en desarrollo)

#### Léxico:


(en desarrollo, preparar las definiciones de todo y de las funciones)

#### Modelo IPO y resolución del problema:

(en desarrollo)

### Extra

La versión en lenguaje ensamblador no va a estar disponible para este trabajo práctico, pero en su lugar sugiero ver un visualizador de objetos 3D que estoy desarrollando, programado 100% en NASM: https://github.com/Ferig83/Visor3D_ASM   (solo para Windows, x64)

Cubre de sobra todos los conceptos (y muchos más!), excepto el de plantillas/templates. Además es muy lindo de ver :)  
