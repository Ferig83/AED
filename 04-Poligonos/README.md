## TP 04-Polígonos

---

### Análisis del problema

#### Enunciado
 Crear tipos de datos para polígonos y triángulos, proponiendo y definiendo distintas operaciones.

#### Restricciones
No utilizar vectores dinámicos (ej: std::vector).  

#### Léxico e Hipótesis de trabajo

Debemos representar a los polígonos y triángulos como un conjunto de vértices en el plano R^2. Por definición, un polígono no debería tener menos de tres vértices, por lo que el polígono más pequeño es el triángulo. Además, cada polígono tendrá un color y vamos a utilizar el sistema RGB de 24 bits para representarlo (sin el "alpha" que se suele utilizar para transparencia): El sistema consiste en representar el rojo, verde y azúl con un byte cada uno y en ese orden, siendo 00h la ausencia del color y FFh el máximo posible (por ejemplo, el 00FF00h es un verde intenso).

Como operaciones vamos a definir las siguientes:


Sea __vértice__ un par ordenado en __R^2__, __polígono__ un conjunto finito de vértices, __índice__ la posición del vértice, siendo 0 el primero y cantidad total - 1 el último y sea __color__ el conjunto de 3 bytes que representan el rojo, verde y azul (en ese orden). Se definen las siguientes funciones:


- __Inicializar_Figura__:  vértices --> polígono

Convierte un conjunto vértices y lo transforma en un polígono o triángulo (color negro por defecto)

- __Mostrar_Todos_Los_Vertices__: polígono --> vertices

Muestra como par ordenado todos los vértices del polígono

- __getVertice__: polígono x índice --> vértice
  
Devuelve un vértice según índice (del "0" a "cantidad de vertices - 1")

- __getPerimetro__: polígono --> R

Devuelve el perímetro del polígono, suponiéndolo cerrado (conecta los vértices en orden, y el último vértice con el primero)

- __getLongitud__:  polígono x índice x índice --> R

Devuelve la longitud de los segmentos que conectan dos vértices referenciados por los índices

- __getDistancia__: polígono x índice x índice --> R

Devuelve la distancia entre dos vértices, referenciados por sus índices

- __getAngulo__:  polígono x índice --> R 

Devuelve el ángulo en radianes de un vértice, referenciado por su índice

- __getColor__:  polígono --> color

Devuelve el color de un polígono

- __setColor__: polígono x color --> polígono

Cambia el color de un polígono

- __AgregarVerticeAlFinal__: polígono x vértice --> polígono

Agrega un vértice al final del polígono (recordar que el orden es importante para el cálculo de ángulos)

- __BorrarUltimoVertice__: polígono --> polígono

Borra el último vértice de un polígono

- __getCantidadVertices__: polígono --> N

Devuelve la cantidad de vértices de un polígono


---

### Modelo IPO y resolución del problema:

Se plantea la estructura _ColorRGB_ que consiste en agrupar los bytes de cada color, los cuales están definidos sus valores con el tipo de dato Char (1 byte). Para los vértices, utilizaremos la estructura _Vertice_ para representar el par ordenado, utilizando números en coma flotante de doble precisión para cada componente.

Los polígonos y los triángulos deben ser dos tipos de datos separados. Ambos tienen en común una variable entera sin signo llamada _"cantidad_vertices"_ que refleja la cantidad de los mismos, y además ambos tienen un arreglo de vértices. Sin embargo, en el caso del triángulo el arreglo consta de tres vértices mientras que en el caso del polígono, al no poder usar arreglos dinámicos (ver restricciones), se utilizará un arreglo cuyo techo estará dado por la macro __VERTICES_MAXIMOS__ (inicializada en el código con el valor de 20). Aquí juega un rol muy importante la variable _cantidad_vertices_ , ya que nos permitirá realizar la iteración de los vértices reales que tiene el polígono (dejando de lado en los cálculos el espacio sobrante reservado).

Como se pide que __triángulo__ y __polígono__ sean dos tipos de dato diferentes, se propone utilizar plantillas para evitar escribir las mismas funciones para cada tipo. 


template <typename T, typename G> T Inicializar_Figura(G &vertices);
template <typename T> void Mostrar_Todos_Los_Vertices(const T &t);
template <typename T> Vertice getVertice(const T &t, int n);
template <typename T> double getPerimetro(const T &t);
template <typename T> double getLongitud(const T &t, int i, int fin);
template <typename T> double getDistancia(const T &t, int i, int j);
template <typename T> double getAngulo(const T &t, int i); 
template <typename T> ColorRGB getColor(const T &t);
template <typename T> void setColor(T &t, ColorRGB color);
template <typename T> void AgregarVerticeAlFinal(T &t, Vertice vertice);
template <typename T> void BorrarUltimoVertice(T &t);
template <typename T> int getCantidadVertices(const T &t);



### Extra

La versión en lenguaje ensamblador no va a estar disponible para este trabajo práctico, pero en su lugar sugiero ver un visualizador de objetos 3D que estoy desarrollando, programado 100% en NASM: https://github.com/Ferig83/Visor3D_ASM   (solo para Windows, x64)

Cubre de sobra todos los conceptos (y muchos más!), excepto el de plantillas/templates. Además es muy lindo de ver :)  
