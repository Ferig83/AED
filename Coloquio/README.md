## TP - Coloquio

---

### Análisis del problema

#### Enunciado
 Crear contenedores, realizar las pruebas pertinentes y dar ejemplos de uso.
 
#### Restricciones

* No se han establecido restricciones

#### Léxico e Hipótesis de trabajo

Los contenedores son tipos de datos o estructuras que contienen en si mismos otro tipo de objetos (ya sean estructuras, tipos de datos atomicos, otros contenedores, etc). Por ejemplo, se puede diseñar un contenedor como una pila que funcione como tal y maneje en su estructura cualquier tipo de dato (inclusive otra pila). Se diferencia de las estructuras en que los tipos de datos no están definidos en nuestro código (sí se definen al compilarse).

En C++ podemos encontrar muchos contenedores implementados bajo la forma de "templates" (y una biblioteca llamada Standard Template Library que los incluye), como por ejemplo std::array que permite manejar un array continuo utilizando como objetos del array el tipo de dato o estructura que queramos.

En esta presentación diseñamos tres tipos de contenedores utilizando el mismo sistema de templates:

* Lista_Enlazada
* Pila
* Cola

- __Lista_Enlazada__ = {  

Con los siguientes métodos:

* Constructor
* agregar_al_final
* Destructor


## Ejemplos de implementación:

### Sistema básico de turnos segun llegada - Uso de Cola

Se necesita una aplicación para ingresar pacientes que llegan a la recepción de un consultorio médico y mostrar por un display (ajeno al std::cout) su nombre y apellido segun vayan ingresando.

### Modelo IPO y resolución del problema:

Se requiere que los pacientes que han llegado primero a la recepción sean los primeros en atenderse en el consultorio, por lo tanto se ve conveniente el uso de nuestro tipo de dato "Cola" ya que el tipo de almacenaje y acceso cumple con el sistema FIFO (First In First Out : primero en ingresar es el  primero en salir). Como no existe una cantidad fija de pacientes (más allá de que podemos estimar un límite), podemos ver conveniente utilizar una pila con elementos enlazados, en la cual la reserva de memoria se hará en tiempo de ejecución.

El modelo IPO puede consistir en:

Entrada: Ingreso de pacientes en la cola mediante teclado
Procesamiento: Dar formato al nombre para su salida y adherir un mensaje de "Pase, por favor"
Salida: Enviar el flujo de datos a través de un archivo que representaría el buffer del display, con posterior borrado del elemento

La aplicación es muy simple pero demuestra de una manera sencilla el sistema FIFO y cómo la Cola diseñada actúa como contenedor de la estructura Paciente (la cual tiene nombre y apellido como cadenas).


### Sistema básico de UNDO (deshacer) - Uso de Lista_Enlazada y Pila

Se necesita una aplicación base que consiste en una agenda con cuatro celdas de almacenamiento y se desea poder visualizarlas y editarlas. A su vez, tiene como opcion deshacer los cambios que vayamos realizando.

### Modelo IPO y resolución del problema:

La agenda misma consiste en un archivo donde se tienen todos los datos pero para conveniencia se almacenarán todos en memoria apenas se inicia la aplicación. Este almacenamiento requerirá de poder editar cualquier nodo de la lista donde se guarde, por lo que se ve conveniente  utilizar nuestro contenedor "Lista_Enlazada", que contendrá la estructura "Persona" (la cual contiene nombre, apellido, dirección y teléfono). Sin embargo, también debemos escribir un sistema para deshacer los cambios en el caso de que el usuario se haya equivocado, y este tipo de sistemas cumple muy bien con el método de almacenamiento LIFO (Last In First Out - Último en Entrar, Primero en Salir) haciendo ideal el uso de la Pila (los últimos cambios son los que se deben deshacer primero).

