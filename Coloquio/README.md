## TP - Coloquio

---

### Análisis del problema

#### Enunciado
 Crear contenedores (enlazados y continuos), realizar las pruebas pertinentes y dar ejemplos de uso.
 
#### Restricciones

* No se han establecido restricciones

#### Léxico e Hipótesis de trabajo

Los contenedores son tipos de datos o estructuras que contienen en si mismos otro tipo de objetos (ya sean estructuras, tipos de datos atómicos, otros contenedores, etc). Por ejemplo, se puede diseñar un contenedor como una pila que funcione como tal y maneje en su estructura cualquier tipo de dato (inclusive otra pila). Se diferencia de las estructuras en que los tipos de datos no están definidos en nuestro código (sí se definen al compilarse).

En C++ podemos encontrar muchos contenedores implementados bajo la forma de "templates" (y una biblioteca llamada Standard Template Library que los incluye), como por ejemplo std::array que permite manejar un array continuo utilizando como objetos del array el tipo de dato o estructura que queramos.

En esta presentación diseñamos tres tipos de contenedores utilizando el mismo sistema de templates:

* Lista_Enlazada
* Pila
* Cola

##### Contenedores Enlazados

Sea "Tipo" un tipo de dato y Tipo_1, Tipo_2 ... Tipo_n  las posiciones ordenadas de los objetos creados bajo ese tipos de dato, y "n" el número de datos totales

- __Lista_Enlazada__ = {(Tipo_1);(Tipo_2);(Tipo_3); ... ;(Tipo_n)}

Con los siguientes métodos:

* agregar_al_final(Tipo x) = {(Tipo_1); (Tipo_2); ...; (Tipo_n); (x_n+1)}
* agregar_en(Tipo x, m) = {(Tipo_1); (Tipo_2); ...; (x_m) ;...; (Tipo_n+1)}
* set_nodo(Tipo x, m) = Tipo_m -> x_m
* borrar_nodo (m) = Tipo_m -> nulo  ^  n = n - 1    (ordinal decrementado en 1)
*	get_dato_nodo (m) = Tipo_m
* get_tamanio = n
* is_vacia = verdadero si el ordinal de Lista_Enlazada es 0 , falso si el ordinal de Lista_Enlazada es distinto de cero


- __Pila__ = {(Tipo_1);(Tipo_2);(Tipo_3); ... ;(Tipo_n)}

Con los siguientes métodos:

* push(Tipo x) = {(x); (Tipo_(1+1)); (Tipo_(2+1)); ...; ((Tipo_(n+1))}
* pop = Tipo_1  con {(Tipo_2);(Tipo_3);(Tipo_4); ... ;(Tipo_n-1)} ^  n = n - 1 (ordinal decrementado en 1)
* peek = Tipo_1
* get_tamanio = n
* is_vacia = verdadero si el ordinal de Pila es 0, falso si el ordinal de Pila es distinto de cero


- __Cola__ = {(Tipo_1);(Tipo_2);(Tipo_3); ... ;(Tipo_n)}

Con los siguientes métodos:

* queue(Tipo x) = {(Tipo_1); (Tipo_2); ...; (Tipo_n); (x)}
* unqueue = Tipo_1  con {(Tipo_2);(Tipo_3);(Tipo_4); ... ;(Tipo_n-1)} ^  n = n - 1    (ordinal decrementado en 1)
* frente = Tipo_1
* get_tamanio = n
* is_vacia = verdadero si el ordinal de Cola es 0, falso si el ordinal de Cola es distinto de cero

##### Contenedores Continuos:

- __Lista_Continua__ = {(Tipo_1);(Tipo_2);(Tipo_3); ... ;(Tipo_n)}

Con los siguientes métodos:

* set_nodo(Tipo x, m) = Tipo_m -> x_m
*	get_dato_nodo (m) = Tipo_m
* get_tamanio = n


- __Pila__ = {(Tipo_1);(Tipo_2);(Tipo_3); ... ;(Tipo_n)}

Con los siguientes métodos:

* push(Tipo x) =  {(Tipo_1); (Tipo_2); ...; (Tipo_n); (x)}
* pop = Tipo_1  con {(Tipo_1);(Tipo_2);(Tipo_3); ... ;(Tipo_n-1)} ^  n = n - 1 (ordinal decrementado en 1)
* peek = Tipo_n
* get_tamanio = n
* is_vacia = verdadero si el ordinal de Pila es 0, falso si el ordinal de Pila es distinto de cero


- __Cola__ = {(Tipo_n);....;(Tipo_3);(Tipo_2);(Tipo_1)}

Con los siguientes métodos:

* queue(Tipo x) = {(x);(Tipo_n);....;(Tipo_3);(Tipo_2);(Tipo_1)}
* unqueue = Tipo_1  con {(Tipo_n-1);....;(Tipo_3);(Tipo_2)} ^  n = n - 1    (ordinal decrementado en 1)
* frente = Tipo_1
* get_tamanio = n
* is_vacia = verdadero si el ordinal de Cola es 0, falso si el ordinal de Cola es distinto de cero



## Ejemplos de implementación:

### Sistema básico de turnos segun llegada - Uso de Cola

Se necesita una aplicación para ingresar pacientes que llegan a la recepción de un consultorio médico y mostrar por un display (ajeno al std::cout) su nombre y apellido segun vayan ingresando.

### Modelo IPO y resolución del problema:

Se requiere que los pacientes que han llegado primero a la recepción sean los primeros en atenderse en el consultorio, por lo tanto se ve conveniente el uso de nuestro tipo de dato "Cola" ya que el tipo de almacenaje y acceso cumple con el sistema FIFO (First In First Out : primero en ingresar es el  primero en salir). Como no existe una cantidad fija de pacientes (más allá de que podemos estimar un límite), podemos ver conveniente utilizar una pila con elementos enlazados, en la cual la reserva de memoria se hará en tiempo de ejecución.

El modelo IPO puede consistir en:

* Entrada: Ingreso de pacientes en la cola mediante teclado
* Procesamiento: Dar formato al nombre para su salida y adherir un mensaje de "Pase, por favor"
* Salida: Enviar el flujo de datos a través de un archivo que representaría el buffer del display, con posterior borrado del elemento

La aplicación es muy simple pero demuestra de una manera sencilla el sistema FIFO y cómo la Cola diseñada actúa como contenedor de la estructura Paciente (la cual tiene nombre y apellido como cadenas).


### Sistema básico de UNDO (deshacer) - Uso de Lista_Enlazada y Pila

Se necesita una aplicación base que consiste en una agenda con cuatro celdas de almacenamiento y se desea poder visualizarlas y editarlas. A su vez, tiene como opcion deshacer los cambios que vayamos realizando.

### Modelo IPO y resolución del problema:

La agenda misma consiste en un archivo donde se tienen todos los datos pero para conveniencia se almacenarán todos en memoria apenas se inicia la aplicación. Este almacenamiento requerirá de poder editar cualquier nodo de la lista donde se guarde, por lo que se ve conveniente  utilizar nuestro contenedor "Lista_Enlazada", que contendrá la estructura "Persona" (la cual contiene nombre, apellido, dirección y teléfono). Sin embargo, también debemos escribir un sistema para deshacer los cambios en el caso de que el usuario se haya equivocado, y este tipo de sistemas cumple muy bien con el método de almacenamiento LIFO (Last In First Out - Último en Entrar, Primero en Salir) haciendo ideal el uso de la Pila (los últimos cambios son los que se deben deshacer primero).

El modelo IPO puede consistir en:

Para edición de datos:

* Entrada: Ingreso de datos de personas y un número N 
* Procesamiento: Reemplazar (en memoria) la entrada en la posición N por el ingreso solicitado en la entrada
* Salida: Base de datos modificada

Para deshacer cambios:

* Entrada: Base de datos con una última modificación
* Procesamiento: Reemplazar la última modificación por una anterior
* Salida: Base de datos sin la última modificación

La aplicación es un ejemplo combinado de Lista_Enlazada y Pila, y representa una agenda muy simplificada para demostrar de manera sencilla el posible uso de ambos contenedores.
