## TP 05-Color

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

* rojo = (255,0,0)
* verde = (0,255,0)
* azul = (0,0,255)
* amarillo = (255,255,0)
* magenta = (255,0,255)
* cyan = (0,255,255)
* blanco = (255,255,255)
* negro = (0,0,0)

---

### Modelo IPO y resolución del problema:

 Para los colores, utilizaremos la estructura _Color_RGB_ para representar la terna rojo,azul y verde. Se utilizará el tipo de dato atómico y fijo __uint8_t__ para representar el byte de cada color.
 
 __¿Por qué en caso de no poder usar "uint8_t" no debe usarse "char"?___  Porque representa un entero de 1 byte con signo, y obtendríamos por lo tanto un rango que va del -128 al 127. Nosotros necesitamos que el entero sea sin signar, dandonos el rango de 0 a 255 que necesitamos. De no poder usar uint8_t , se debería usar unsigned char que cumple con este requisito.
 

A continuación se listan las operaciones para el tipo de dato Color_RGB, describiendo el modelo IPO:

__IMPORTANTE: Todas las funciones, estructuras y constantes propias de esta implementación viven en el namespace "color", por lo que debe anteponerse "color::" para cada una__

* Color_RGB mezclarColor(Color_RGB color1, Color_RGB color2, uint8_t porcentaje1, uint8_t porcentaje2)

  - ENTRADA: Dos colores tipo Color_RGB a mezclar, y los porcentajes respectivos en números enteros (máximo porcentaje: 255).
  - PROCESAMIENTO: Controla que la mezcla no supere los 255 por cada canal, y realiza el promedio.
  - SALIDA: La mezcla final de tipo Color_RGB

* Color_RGB sumarColor(Color_RGB color1, Color_RGB color2)

  - ENTRADA: Dos colores tipo Color_RGB a sumar
  - PROCESAMIENTO: Controla que la suma no supere los 255 por cada canal, y realiza la suma
  - SALIDA: La suma final de tipo Color_RGB. Si algún canal superó el valor 255, se setea a 255.

* Color_RGB restarColor(Color_RGB color1, Color_RGB color2)

  - ENTRADA: Dos colores tipo Color_RGB a restar
  - PROCESAMIENTO: Controla que la resta no baje del 0 por cada canal, y realiza la resta
  - SALIDA: La resta final de tipo Color_RGB. Si algún canal bajó del 0, se setea a 0.


* Color_RGB getComplementario(Color_RGB color)

  - ENTRADA: Un color tipo Color_RGB
  - PROCESAMIENTO: Hace la resta del blanco menos el color de entrada
  - SALIDA: Un color tipo Color_RGB, siendo el complementario del  color argumento.

* (FUNCIÓN AUXILIAR) std::string getHex(int valor)  

  - ENTRADA: Un valor entero
  - PROCESAMIENTO: Convierte el número mediante la función sprintf a formato hexadecimal de dos dígitos.
  - SALIDA: Una cadena de dos caracteres con el número en hexadecimal (letras mayúsculas).

* std::string getHtmlRgb(Color_RGB color)

  - ENTRADA: Un dato tipo Color_RGB
  - PROCESAMIENTO: Crea una cadena con el texto "rgb(x,y,z)" donde x,y,z son los valores en decimal de los canales del color argumento.
  - SALIDA: La cadena convertida.

* std::string getHtmlHex(Color_RGB color)

  - ENTRADA: Un dato tipo Color_RGB
  - PROCESAMIENTO: Crea una cadena con el texto "#XXYYZZ" donde X,Y,Z son los valores en hexadecimal de los canales del color argumento. Utiliza getHex.
  - SALIDA: La cadena convertida.

* void CrearSvgConTextoEscritoEnAltoContraste(std::string nombre_archivo, std::string texto, Color_RGB color)

  - ENTRADA: Una cadena con el nombre del archivo, una cadena con el texto a mostrar y un dato tipo Color_RGB
  - PROCESAMIENTO: Se crea un archivo utilizando ofstream, el cual se carga la información .SVG eligiendo como parámetros los indicados (más el complementario). Se utiliza getHtmlRgb y getHtmlHex.
  - SALIDA: Ninguna, pero se crea el archivo como efecto de lado, el cual puede ser probado en un navegador web que soporte .SVG


* bool isIgual(Color_RGB color1, Color_RGB color2);


  - ENTRADA: Dos tipos de dato Color_RGB
  - PROCESAMIENTO: Se compara cada canal de ambos colores.
  - SALIDA: Verdadero si los canales son iguales. Falso si no lo son.



### Extra

Como en el TP anterior, la versión en lenguaje ensamblador no va a estar disponible para este trabajo práctico, pero en su lugar sugiero ver un visualizador de objetos 3D que estoy desarrollando, programado 100% en NASM: https://github.com/Ferig83/Visor3D_ASM   (solo para Windows, x64)

Este visualizador muestra un gráfico en 3D y tiene un sistema de sombreado dinámico, por lo que se utiliza el sistema RGB para darle color al objeto. Se realiza el producto escalar de las normales de los triángulos que componen el objeto y el vector que representa la dirección de la luz (ambos normalizados). Se obtiene un valor de 0 a 1 y se utiliza el mismo para definir la proporcion del valor de todos los canales (cuanto más perpendicular sea la luz al plano, más oscuro el color).
