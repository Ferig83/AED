# Adición


Nuestro objetivo es sumar dos números enteros. Según el módelo de IPO (datos de entrada que se procesan para obtener resultados como salida), para su procesamiento debemos tener espacio y tiempo. Como se tratará de una operación sencilla (sumar dos números sin más), no se discutirá el tema del tiempo pero sí lo haremos con el espacio: **nuestro procesador nos obliga a colocar en memoria todo lo que se procesa, incluyendo los mensajes (cadenas) que luego irán a la salida.**

En el caso de C++, con std::out no necesitaremos declarar variables ni ordenar explicitamente que se almacenen los mensajes que vamos a imprimir (más allá de que internamente sí hay un almacenamiento en memoria de todas las cadenas que imprimimos). Sin embargo, sí debemos reservar espacio para los números. Además necesitamos instrucciones que nos permitan la entrada de datos (los números a ingresar), la salida (los resultados a mostrar y los mensajes que orienten al usuario) y las operaciones aritméticas.

*Paso 1  (LÉXICO): Reservar los espacios bajo los nombres "numero1", "numero2" y "resultado", todos de tipo entero*

Luego necesitamos pedir que se rellenen los espacios de "numero1" y "numero2", ya que estos son los números que
vamos a sumar

*Paso 2 (INPUT): Pedirle al usuario que ingrese los valores para "numero1" y "numero2"*

Una vez hecho esto, entramos en la fase de procesamiento del modelo **IPO**: Procesamos los dos valores, sumándo ambos
y colocando el resultado en el espacio "resultado" (puede usarse una de las variables para guardar el resultado pero
preferimos usar una tercera para explicar mejor el algoritmo).

*Paso 3 (PROCESAMIENTO):  Sumamos "numero1" y "numero2" y volcamos el resultado en el espacio "resultado"*

Ahora debemos mostrar el resultado, lo que indica que estamos en la fase de output del sistema **IPO**.

*Paso 4 (OUTPUT):  Mostramos lo guardado en "resultado" en pantalla.*


El algoritmo completo sería el siguiente

*Inicio \
   "numero1","numero2","resultado" del tipo entero  \
    mostrar "Ingrese el primer número" \
    leer "numero1" \
    mostrar "Ingrese el segundo número" \
    leer "numero2" \
    resultado = numero1 + numero2 \
    mostrar "El resultado es: ", resultado \
Fin* 

No estamos verificando si lo que ingresó fueron letras (en el código propuesto en assembler si se hace, tomando
como nulas los valores donde se ingresen caracteres no numéricos) y además la suma puede hacerse diferente (pedir que se ingrese la cadena entera), pero para simplificar el código se realizó de esa manera.

Veamos como sería el diagrama de flujo:


![Diagrama](https://github.com/Ferig83/AED/blob/master/01-Adici%C3%B3n/diagrama.png)


## Versión en NASM

En este trabajo práctico se incluye el código en C++ de un algoritmo simple en donde se suman 
dos valores. En la carpeta ASM incluyo el código que contiene la versión en lenguaje ensamblador
(seguimos con Netwide Assembler bajo Linux x64) y además una librería de funciones que
voy a ir ampliando. La librería tiene:


* ASMLIB_Cout  : Nuestro intento por emular el std::cout

* ASMLIB_Cin   : Idem para std::cin

* ASMLIB_Entero_a_Cadena : Para convertir un número entero positivo a cadena

* ASMLIB_Cadena_a_Entero: Para convertir a entero una cadena de caracteres numéricos finalizada en 0


Lo nuevo de este código es la inclusión de funciones que representan la entrada de datos, y nos encontramos
con la tarea de convertir datos que representan cadenas (arreglo de datos tipo "char") con datos que 
representan "números" (datos tipo "int" o "enteros"). Este tipo de conversión como se puede ver no es muy 
compleja ya que prácticamente debemos convertir caracter por caracter, en formato ASCII, al valor que la
máquina reconoce y puede operar como número. Si nos fijamos en una tabla de código ASCII, veremos que
con restarle el número 48 a cada caracter se lo convertirá en número, y sumándole 48 pasaríamos de 
número a caracter.

Sin embargo vemos que en el código en C++ no se necesitó en ningún momento que hagamos esta conversión. El 
"std::cin" hizo esta conversión por nosotros o detectó el tipo de dato?  Es posible que internamente se esté
haciendo uso de "templates" (plantillas) donde para cada tipo de dato tendremos diferentes métodos en cout que indiquen
cómo comportarse en cada caso. Nuestro código fallará si hubiesemos declarado la variable numero1 como "char\[\]" 
por lo que bajo esta evidencia podríamos deducir que no se hacen conversiones de datos.


NOTA: Es importante aclarar que no pretendo (y de hecho sería bastante desacertado) decir que reproduje la misma 
funcionalidad del std::cin y el std::cout  en assembler, pero trataremos de acercarnos lo más que podamos).





