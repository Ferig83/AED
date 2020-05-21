## TP 02-EjemploTipos

---

### Análisis del problema

#### Enunciado
 Escribir un programa que ejemplifique el uso de los tipos de datos basicos de C++ vistos en clase:
- int - char - double - string - bool - unsigned

#### Restricciones
No extraer valores de cin, usar valores literales (constantes)

#### Hipotesis de trabajo

Necesitamos mediante un ejemplo usar todos esos tipos de datos y aplicarles algún tipo de operación. Se asume por
las restricciones que no hay interacción del usuario cuando nuestro código ya está compilado. Como tampoco
puede usarse el std::cout (asumimos que tampoco se usará el printf del C) y sí puede usarse el assert(), vamos a 
asumir también que las salidas serán de está función y que las pruebas del código consistirán en modificar el mismo,
compilarlo y chequear si el assert no provoca salidas (y si las provoca, analizar las causas).


---
### Solución

Escribí como ejemplo un código que cumple con estas características, como si se estuviese analizando un experimento de biología.
El programa se ejecuta sin ninguna entrada y no tendrá salida alguna excepto que se modifiquen a propósito las constantes en el 
código para provocar que el assert corte el programa y muestre qué condición no se cumplió. 

El código en sí es bastante descriptivo. Los enteros se utilizan para sacar un promedio, el cual es volcado en un double. Las 
constantes booleanas se operan con "and" y "xor" para corroborar si los especímenes del ejemplo cumplen que ambos son adultos y 
de sexo diferente. Las cadenas (string) se recortan para verificar solo una porción de las mismas.

### ¿Los tipos de datos usados son los únicos en C++?

En C++ no son los únicos, existen tipos de datos como float y arrays de todos los tipos de datos de arriba. También existen
tipos de enteros de tamaño fijo tipo uint32 que sería un unsigned int de 32 bits independientemente del procesador. Se pueden
también crear estructuras que vendrían a ser también tipos de datos.

### Extra:  Cuántos tipos de datos admite el lenguaje ensamblador?

Una de las cosas que podemos observar es que la computadora no reconoce tantos tipos de datos. Sí podemos reconocer que
existe uno especial para los de coma flotante (IEEE 754) el cual adjunto librería para imprimirlos (bajo ciertos defectos
de precisión, usando un algoritmo llamado Dragon2). Este tipo de datos se operan bajo instrucciones y registros especiales
aunque antaño se hacía usando los registros comunes. 

Por el otro lado, los lenguajes ensambladores suelen hacer conversiones. Por ejemplo:

section .data
    variable1 db '0'   ; El lenguaje ensamblador me convierte este caracter al número 48
 
 Sin embargo esto no lo considero como un tipo de dato, sino una mera conversión.

(NOTA: La parte de ensamblador puede que no esté finalizada para el 21 de Mayo a las 12:00 hs. El código está hecho
pero necesito portarlo de Windows a Linux)

