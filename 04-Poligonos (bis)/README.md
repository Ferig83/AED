__IMPORTANTE: Esta entrega corresponde a la entrega formal del trabajo "Polígonos", el cual no incluye el triángulo y se complementa con "Color"__

__Existe una entrega anterior llamada "04-Poligonos" la cual contiene la implementación de triángulo usando plantillas. Preferí no mezclarlas ya que los enunciados estaban separados.__



## TP 04-Polígonos (bis)

---

### Análisis del problema

#### Enunciado
 Crear un tipo de datos para polígonos, proponiendo y definiendo distintas operaciones.

#### Restricciones
No utilizar vectores dinámicos (ej: std::vector) y realizar todas las pruebas con "assert"

#### Léxico e Hipótesis de trabajo

Debemos representar a los polígonos como un conjunto de vértices en el plano R^2. Por definición, un polígono no debería tener menos de tres vértices, y tampoco se define si el polígono es cerrado o abierto. Además, cada polígono tendrá un color y se utilizará el sistema RGB de 24 bits para representarlo (sin el "alpha" que se suele utilizar para transparencia): El sistema consiste en representar el rojo, verde y azúl con un byte cada uno y en ese orden, siendo 00h la ausencia del color y FFh el máximo posible (por ejemplo, el 00FF00h es un verde intenso).

Como operaciones vamos a definir las siguientes:


Sea __vértice__ un par ordenado en __R^2__, __polígono__ un conjunto finito de vértices mayor o igual a dos, __índice__ la posición del vértice, siendo 0 el primero y __cantidad total - 1__ el último, y sea __color__ el conjunto de 3 bytes que representan el rojo, verde y azul (en ese orden). Se definen las siguientes funciones:


- __inicializarPoligono__:  N x vértices x color --> polígono

Convierte un conjunto de n vertices y un color, y lo transforma en un polígono. Se debe especificar la cantidad de vértices (por eso usamos el número entero)

- __imprimirVertices__: polígono --> vertices

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

Devuelve el ángulo en radianes de un vértice, referenciado por su índice y considerando el polígono cerrado.

- __getColor__:  polígono --> color

Devuelve el color de un polígono

- __setColor__: polígono x color --> polígono

Cambia el color de un polígono

- __addVertice__: polígono x vértice --> polígono

Agrega un vértice al final del polígono (recordar que el orden es importante para el cálculo de ángulos)

- __removeVertice__: polígono --> polígono

Borra el último vértice de un polígono

- __getCantidadVertices__: polígono --> N

Devuelve la cantidad de vértices de un polígono

- __getCantidadLadosAbierto__: polígono --> N

Devuelve la cantidad de lados de un polígono suponiendo que es abierto (el último vertice no se une con el primero)

- __getCantidadLadosCerrado__: polígono --> N

Devuelve la cantidad de lados de un polígono suponiéndolo cerrado.

- __setVertice__: polígono x N x vértice --> polígono

Cambia un vértice del polígono en el índice indicado.


---

### Modelo IPO y resolución del problema:

 Para los vértices, utilizaremos la estructura _Vertice_ para representar el par ordenado, utilizando números en coma flotante de doble precisión para cada componente. La estructura Poligono consistirá entonces en un array de "Vertice", y se agrega una variable entera sin signo llamada _"cantidad_vertices"_ que refleja la cantidad de los mismos Sin embargo, al no poder usar arreglos dinámicos (ver restricciones), se utilizará un arreglo cuyo techo estará dado por la macro __VERTICES_MAXIMOS__ (inicializada en el código con el valor de 20). Aquí juega un rol muy importante la variable _cantidad_vertices_ , ya que nos permitirá realizar la iteración de los vértices reales que tiene el polígono (dejando de lado en los cálculos el espacio sobrante reservado).

Para el color, se reutiliza el tipo de dato _ColorRGB_ de "color.cpp" y se suman por lo tanto todas sus operaciones. Para más información consultar www.github.com/Ferig83/AED/05-Color/.  

A continuación se listan las operaciones para el tipo de dato Polígono, describiendo el modelo IPO:

__IMPORTANTE__ : Todas las funciones, estructuras y constantes implementadas viven en el namespace "poligono", a excepción de las referidas a "color" (las cuales viven en el namespace "color") y las estándar de C++ (namespace "std"). 


* Poligono inicializarPoligono (unsigned cantidad, const std::array<poligono::Vertice, VERTICES_MAXIMOS> &vertices, color::Color_RGB color)

  - ENTRADA: Un array de n __Vertice__ que representan el polígono, y un color del tipo ColorRGB
  - PROCESAMIENTO: Mueve los vértices a la estructura de salida, así también como su cantidad. 
  - SALIDA: Una estructura del tipo __Poligono__ 

* void imprimirVertices(const Poligono &t)

  - ENTRADA: Una estructura del tipo __Poligono__ 
  - PROCESAMIENTO: Itera los vértices de la estructura de entrada mediante un ciclo FOR e imprime los valores utilizando std::cout
  - SALIDA: La impresión en pantalla de los valores (la función en sí misma no devuelve datos de retorno)

* Vertice getVertice(const Poligono &t, unsigned n)

  - ENTRADA Una estructura del tipo __Poligono__  , junto con un número natural que representa el índice
  - PROCESAMIENTO: Simplemente retorna el vértice en el índice indicado 
  - SALIDA: Devuelve el vértice en el índice indicado
 
* double getPerimetro(const Poligono &t)

  - ENTRADA: Una estructura del tipo __Poligono__ 
  - PROCESAMIENTO: Calcula cada una de las longitudes entre vértices mediante un ciclo FOR, incluyendo (aunque fuera del ciclo) la longitud entre el primer vértice y el último. Para calcular cada longitud se restan las coordenadas de los vértices, se elevan al cuadrado y se suman. Por último, se le hace la raiz cuadrada.
  - SALIDA: Un número real con la suma de las longitudes calculadas.
  
* double getLongitud(const Poligono &t, unsigned i, unsigned fin)

  - ENTRADA: Una estructura del tipo __Poligono__ , y dos ínidices naturales
  - PROCESAMIENTO: Calcula la suma de las longitudes de los segmentos comprendidos entre dos vértices, iterando los vértices y segmentos que están entre ellos. El cálculo es similar al del perímetro, solo que selectiva a los vértices indicados.
  - SALIDA: La suma de la longitud de los segmentos
 
* double getDistancia(const Poligono &t, unsigned i, unsigned j)

  - ENTRADA : Una estructura del tipo __Poligono__  , y dos ínidices naturales
  - PROCESAMIENTO: De manera similar al cálculo de longitud, se calcula la distancia entre dos vértices.
  - SALIDA: Numero real con la distancia calculada.
 
* double getAngulo(const Poligono &t, unsigned i)

  - ENTRADA: Una estructura del tipo __Poligono__  y un indice natural
  - PROCESAMIENTO: Se realiza el teorema del coseno para calcular el ángulo del vértice indicado. Si el vértice está en un extremo, se calcula como si el polígono fuese cerrado.
  - SALIDA: Un número real representando en radianes el valor del ángulo


* color::Color_RGB getColor(const Poligono &t)

   - ENTRADA: Una estructura del tipo __Poligono__ 
   - PROCESAMIENTO: Simplemente retorna el color del polígono o triángulo
   - SALIDA: El color del polígono o triángulo como estructura _ColorRGB_
 
* void setColor(Poligono &t, color::Color_RGB color)

   - ENTRADA: Una estructura del tipo __Poligono__ y una estructura del tipo ColorRGB
   - PROCESAMIENTO: Cambia el color del polígono o triángulo
   - SALIDA: ninguna
 
* void addVertice(Poligono &t, Vertice vertice)

   - ENTRADA: Una estructura del tipo __Poligono__ y una estructura del tipo __Vertice__
   - PROCESAMIENTO: Agrega el vértice ingresado al final del polígono, corroborando que no pase el techo de cantidades máximas de vértices permitidas
   - SALIDA: ninguna


* void removeVertice(Poligono &t)

   - ENTRADA: Una estructura del tipo __Poligono__ 
   - PROCESAMIENTO: Reduce en una unidad el indicador _cantidad_vertices_
   - SALIDA: ninguna


* unsigned getCantidadVertices(const Poligono &t)

   - ENTRADA: Una estructura del tipo __Poligono__ 
   - PROCESAMIENTO: Retorna la cantidad de vértices dada por _cantidad_vertices_
   - SALIDA: Un numero natural representando la cantidad de vértices


* unsigned getCantidadLadosAbierto(const Poligono &t)

   - ENTRADA: Una estructura del tipo __Poligono__ 
   - PROCESAMIENTO: Suma cantidad de lados si el polígono fuese abierto.
   - SALIDA: La cantidad de lados


* unsigned getCantidadLadosCerrado(const Poligono &t)

   - ENTRADA: Una estructura del tipo __Poligono__ 
   - PROCESAMIENTO: Suma cantidad de lados si el polígono fuese cerrado.
   - SALIDA: La cantidad de lados


* void setVertice(Poligono &t, unsigned i, Vertice vertice)

   - ENTRADA: Una estructura del tipo __Poligono__ , un indice y el vértice que reemplaza el existente
   - PROCESAMIENTO: Cambia el vértice en el índice dado por el pasado como argumento
   - SALIDA: Ninguna


### Extra

La versión en lenguaje ensamblador no va a estar disponible para este trabajo práctico, pero en su lugar sugiero ver un visualizador de objetos 3D que estoy desarrollando, programado 100% en NASM: https://github.com/Ferig83/Visor3D_ASM   (solo para Windows, x64)

Cubre de sobra todos los conceptos (y muchos más!). Además es muy lindo de ver :)  
