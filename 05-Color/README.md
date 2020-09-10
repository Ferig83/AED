## TP 04-Color

---

### Análisis del problema

#### Enunciado
 Crear un tipo de datos para color, proponiendo y definiendo distintas operaciones.

#### Restricciones

* Realizar todas las pruebas con "assert" 
* Definir los colores secundarios, el blanco y el negro con las operaciones sugeridas. 
* Los  colores  primarios,  secundarios,  negro  y  blanco  deben  implementarse como  ocho  variables  declaradas  fuera  de  main  y  de  toda  función,  con  el calificador const para que no puedan modificarse 
* No utilizar getters y setters para acceder a los canales de color.  
* Utilizar el tipo uint8_t de cstdint, si no es posible, usar unsigned char.
* Implementar la operación IsIgual que retorna true si un color es igual a otro,si no, false.

#### Léxico e Hipótesis de trabajo

La representación de colores RGB es un sistema de 24 bits (muchas veces 32 bits ya que se suele utilizar un canal extra llamado alpha) que se utiliza para representar una amplia gama de colores basado en la mezcla de las luces rojo, verde y azul (en ese orden). Cada canal tiene un valor que va desde el 0 (luz apagada) al 255 (intensidad máxima). Es posible realizar operaciones de suma, resta, mezcla (promedio) y sacar el color complementario de un color, compararlos, etc.

Definimos entonces:

Sea __Color_RGB__ una terna ordenada en __r__ perteneciente a los números naturales (incluido el cero) del 0 al 255 


- __mezclarColor__:  Color_RGB x Color_RGB x N x N --> Color_RGB

Se realiza un porcentaje (con redondeo hacia abajo) de cada color y se hace un promedio.

- __sumarColor__: Color_RGB x Color_RGB --> Color_RGB

Suma las intensidades de dos colores, resultando en un nuevo color

- __restarColor__: Color_RGB x Color_RGB --> Color_RGB
  
Resta las intensidades de dos colores, resultando en un nuevo color  
  
- __isIgual__: Color_RGB x Color_RGB --> Booleano

Compara los tres canales de cada color y si son iguales, retorna un valor verdadero. De lo contrario, retorna falso

- __getComplementario__:  Color_RGB --> Color_RGB

Se obtiene un color complementario restándole a la intensidad máxima el color del argumento

- __getHtmlRgb__:  Color_RGB --> sigma* 

Dado un color, devuelve una cadena que representa su intensidad en formato "rgb(x,y,z)" donde x,y,z son las intensidades del RGB, respectivamente.

- __getHtmlHex__:  Color_RGB --> sigma*

Dado un color, devuelve una cadena que representa su intensidad en formato "#XXYYZZ" donde X,Y,Z son las intensidades del RGB en hexadecimal, respectivamente.

- __CrearSvgConTextoEscritoEnAltoConstraste__ : sigma* x sigma* x Color_RGB --> archivo .svg

Dado un texto y un nombre de archivo, crea un archivo <normbre archivo>.SVG que contiene una representación gráfica del texto, en el color dado y con un rectángulo de fondo en su color complementario.


Se obtienen como constantes con valores RGB representados con el tipo de dato Color_RGB:

rojo = (255,0,0)
verde = (0,255,0)
azul = (0,0,255)
amarillo = (255,255,0)
magenta = (255,0,255)
cyan = (0,255,255)
blanco = (255,255,255)
negro = (0,0,0)

---

### Modelo IPO y resolución del problema:

 Para los colores, utilizaremos la estructura _Color_RGB_ para representar la terna rojo,azul y verde. Se utilizará el tipo de dato atómico y fijo __uint8_t__ para representar el byte de cada color.
 
 __¿Por qué en caso de no poder usar "uint8_t" no debe usarse "char"?___  Porque representa un entero de 1 byte con signo, y obtendríamos por lo tanto un rango que va del -128 al 127. Nosotros necesitamos que el entero sea sin signar, dandonos el rango de 0 a 255 que necesitamos. De no poder usar uint8_t , se debería usar unsigned char que cumple con este requisito.
 

A continuación se listan las operaciones para el tipo de dato Color_RGB, describiendo el modelo IPO:

__IMPORTANTE: Todas las funciones, estructuras y constantes propias de esta implementación viven en el namespace "color", por lo que debe anteponerse "color::" para cada una__

* poligono mezclarColor(array <Vertice, n > , ColorRGB color)

  - ENTRADA: Un array de n __Vertice__ que representan el polígono, y un color del tipo ColorRGB
  - PROCESAMIENTO: Mueve los vértices a la estructura de salida, así también como su cantidad
  - SALIDA: Una estructura del tipo __Poligono__ 

* template <typename T> void Mostrar_Todos_Los_Vertices(const T &t)

  - ENTRADA: Una estructura del tipo __Poligono__ 
  - PROCESAMIENTO: Itera los vértices de la estructura de entrada mediante un ciclo FOR e imprime los valores utilizando std::cout
  - SALIDA: La impresión en pantalla de los valores (la función en sí misma no devuelve datos de retorno)

* template <typename T> Vertice getVertice(const T &t, int n)
 
  - ENTRADA Una estructura del tipo __Poligono__  , junto con un número natural que representa el índice
  - PROCESAMIENTO: Simplemente retorna el vértice en el índice indicado 
  - SALIDA: Devuelve el vértice en el índice indicado
 
* template <typename T> double getPerimetro(const T &t)
 
  - ENTRADA: Una estructura del tipo __Poligono__ 
  - PROCESAMIENTO: Calcula cada una de las longitudes entre vértices mediante un ciclo FOR, incluyendo (aunque fuera del ciclo) la longitud entre el primer vértice y el último. Para calcular cada longitud se restan las coordenadas de los vértices, se elevan al cuadrado y se suman. Por último, se le hace la raiz cuadrada.
  - SALIDA: Un número real con la suma de las longitudes calculadas.
  
* template <typename T> double getLongitud(const T &t, int i, int fin)
 
  - ENTRADA: Una estructura del tipo __Poligono__ , y dos ínidices naturales
  - PROCESAMIENTO: Calcula la suma de las longitudes de los segmentos comprendidos entre dos vértices, iterando los vértices y segmentos que están entre ellos. El cálculo es similar al del perímetro, solo que selectiva a los vértices indicados.
  - SALIDA: La suma de la longitud de los segmentos
 
* template <typename T> double getDistancia(const T &t, int i, int j)

  - ENTRADA : Una estructura del tipo __Poligono__  , y dos ínidices naturales
  - PROCESAMIENTO: De manera similar al cálculo de longitud, se calcula la distancia entre dos vértices.
  - SALIDA: Numero real con la distancia calculada.
 
* template <typename T> double getAngulo(const T &t, int i)

  - ENTRADA: Una estructura del tipo __Poligono__  y un indice natural
  - PROCESAMIENTO: Se realiza el teorema del coseno para calcular el ángulo del vértice indicado. Si el vértice está en un extremo, se calcula como si el polígono fuese cerrado.
  - SALIDA: Un número real representando en radianes el valor del ángulo


* template <typename T> ColorRGB getColor(const T &t)
 
   - ENTRADA: Una estructura del tipo __Poligono__ 
   - PROCESAMIENTO: Simplemente retorna el color del polígono o triángulo
   - SALIDA: El color del polígono o triángulo como estructura _ColorRGB_
 
* template <typename T> void setColor(T &t, ColorRGB color);

   - ENTRADA: Una estructura del tipo __Poligono__ y una estructura del tipo ColorRGB
   - PROCESAMIENTO: Cambia el color del polígono o triángulo
   - SALIDA: ninguna
 
* void AgregarVerticeAlFinal(Poligono &t, Vertice vertice);

   - ENTRADA: Una estructura del tipo __Poligono__ y una estructura del tipo __Vertice__
   - PROCESAMIENTO: Agrega el vértice ingresado al final del polígono, corroborando que no pase el techo de cantidades máximas de vértices permitidas
   - SALIDA: ninguna


* void BorrarUltimoVertice(Poligono &t);


   - ENTRADA: Una estructura del tipo __Poligono__ 
   - PROCESAMIENTO: Reduce en una unidad el indicador _cantidad_vertices_
   - SALIDA: ninguna


* template <typename T> unsigned getCantidadVertices(const T &t);

   - ENTRADA: Una estructura del tipo __Poligono__ 
   - PROCESAMIENTO: Retorna la cantidad de vértices dada por _cantidad_vertices_
   - SALIDA: Un numero natural representando la cantidad de vértices



### Extra

La versión en lenguaje ensamblador no va a estar disponible para este trabajo práctico, pero en su lugar sugiero ver un visualizador de objetos 3D que estoy desarrollando, programado 100% en NASM: https://github.com/Ferig83/Visor3D_ASM   (solo para Windows, x64)

Cubre de sobra todos los conceptos (y muchos más!), excepto el de plantillas/templates. Además es muy lindo de ver :)  
