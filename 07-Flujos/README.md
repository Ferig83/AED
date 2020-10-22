## TP 07-Flujos

(IMPORTANTE: Debería ser el N° 6 pero junté dos trabajos en el N° 4, por lo que regularizo todo a partir de este)
---

### Análisis del problema

#### Enunciado
 Crear funciones que acepten flujos de polígonos tanto de entrada como de salida.
 
#### Restricciones

* No se han establecido restricciones

#### Léxico e Hipótesis de trabajo

Los flujos de datos son una serie de datos que se emiten o reciben ininterrumpidamente y pueden ser procesados. Tienen un formato especial el cual sirve para identificar el contexto de cada uno de esos datos (por ejemplo, si se tratan de un nombre, de una dirección, de un color ,etc). Se pueden usar separadores y "confiar" en la ubicación de los datos con respecto a dichos separadores para su identificación, sin embargo esto puede llevarnos a problemas en el caso de que una serie no se reciba o envíe desde el principio, se corte, etc.

Los sistemas operativos disponen de métodos de flujos de datos que vamos a aprovechar para este trabajo. Se explicará como se hace el procedimiento ya que los tipos de datos utilizados (polígonos y colores) ya se han explicado en trabajos anteriores. 


Definimos entonces:

- __ExtraerVerticePoligono__:  Flujo Entrada x Vertice --> booleano x Flujo Entrada Modificado 

Extrae datos relativos a los vértices del polígono y retorna verdadero si la operación se ha realizado. Los datos se manejan en forma de flujo de datos.


- __ExtraerCantidadVerticesPoligono__:  Flujo Entrada x Entero positivo --> booleano x Flujo Entrada Modificado 

Extrae la cantidad de vértices del polígono y retorna verdadero si la operación se ha realizado. Los datos se manejan en forma de flujo de datos.


- __ExtraerColorPoligono__:  Flujo Entrada x Color RGB --> booleano x Flujo Entrada Modificado 

Extrae el color del polígono y retorna verdadero si la operación se ha realizado. Los datos se manejan en forma de flujo de datos.



- __ExtraerPoligono__:  Flujo Entrada x Poligono --> booleano x Flujo Entrada Modificado 


Extrae todos los datos del polígono y retorna verdadero si la operación se ha realizado. Los datos se manejan en forma de flujo de datos.



- __EnviarVerticePoligono__:  Flujo Salida x Vertice --> booleano x Flujo Salida Modificado 

Envía al flujo datos relativos a los vértices del polígono y retorna verdadero si la operación se ha realizado. 


- __EnviarCantidadVerticesPoligono__:  Flujo Salida x Entero positivo --> booleano x Flujo Salida Modificado 

Envía al flujo la cantidad de vértices del polígono y retorna verdadero si la operación se ha realizado. 

- __EnviarColorPoligono__:  Flujo Salida x Color RGB --> booleano x Flujo Salida Modificado 

Envía al flujo el color del polígono y retorna verdadero si la operación se ha realizado. 


- __EnviarPoligono__:  Flujo Salida x Poligono --> booleano x Flujo Salida Modificado 

Envía al flujo todos los datos del polígono y retorna verdadero si la operación se ha realizado. 

---

### Modelo IPO y resolución del problema:

 Utilizaremos std::istream y std::ostream en C++ para manejar los flujos de entrada y de salida (respectivamente). Se recuerda que tanto para el color como para los polígonos hay "namespaces" definidos que por una cuestión de legibilidad no se escribirán en este informe. 
 
 
* bool ExtraerCantidadVerticesPoligono (std::istream &istr, unsigned &cantidad_vertices)

  - ENTRADA: El flujo destino y un puntero a la cantidad de vértices
  - PROCESAMIENTO: Envía al flujo la cantidad de vertices.
  - SALIDA: Booleano que es true si los datos se pueden ingresar.

 
* bool ExtraerVerticePoligono (std::istream &istr, Vertice &vertice)

  - ENTRADA: El flujo destino y un puntero a los vértices del polígono
  - PROCESAMIENTO: Envía al flujo los vertices.
  - SALIDA: Booleano que es true si los datos se pueden ingresar.


* bool ExtraerColorPoligono (std::istream &istr, color::Color_RGB &color)
 
  - ENTRADA: El flujo destino y un puntero al color del polígono
  - PROCESAMIENTO: Envía al flujo el color
  - SALIDA: Booleano que es true si los datos se pueden ingresar.


* bool ExtraerPoligono (std::istream &istr, Poligono &poligono)

  - ENTRADA: El flujo destino y el puntero a un polígono
  - PROCESAMIENTO: Envía al flujo el polígono entero
  - SALIDA: Booleano que es true si los datos se pueden ingresar.


* bool EnviarVerticePoligono (std::ostream &ostr, Vertice vertice)

  - ENTRADA: El flujo destino y el vertice del polígono
  - PROCESAMIENTO: Envía al flujo de salida el vertice
  - SALIDA: Booleano que es true si los datos se pueden ingresar.

* bool EnviarCantidadVerticesPoligono (std::ostream &ostr, unsigned cantidad_vertices)

  - ENTRADA: El flujo destino y la cantidad de vértices del polígono
  - PROCESAMIENTO: Envía al flujo de salida la cantidad de vértices.
  - SALIDA: Booleano que es true si los datos se pueden ingresar.

* bool EnviarColorPoligono (std::ostream &ostr, color::Color_RGB color);

  - ENTRADA: El flujo destino y el color del polígono
  - PROCESAMIENTO: Envía al flujo de salida el color del polígono.
  - SALIDA: Booleano que es true si los datos se pueden ingresar.


* bool EnviarPoligono (std::ostream &ostr, const Poligono &poligono);

  - ENTRADA: El flujo destino y el polígono entero
  - PROCESAMIENTO: Envía al flujo de salida el polígono entero
  - SALIDA: Booleano que es true si los datos se pueden ingresar.









