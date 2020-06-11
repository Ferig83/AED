## TP 03-Bisiesto

---

### Análisis del problema

#### Enunciado
 Escribir un programa que nos permita determinar si un año es bisiesto o no.

#### Restricciones
No utilizar "condicionales", "ifs" o "switchs"

#### Hipotesis de trabajo

Primero se debe determinar cuál es la definición de año bisiesto y el tipo de datos que se necesita para la función. Se conoce que la determinación de si un año es bisiesto o no corresponde a la divisibilidad del número del año con respecto a ciertos valores, por lo que la función aceptará un parámetro del tipo entero (sin signar ya que la clasificación comienza desde 1582) y cómo salida un booleano que señalará como verdadero si el año es bisiesto, y falso si no lo es. Dentro de la función utilizaremos booleanos con operadores lógicos y la operación "modulo" (resto de una división entera).

La definición de un año bisiesto es que sea divisible por 4. Además no debe ser divisible por 100, excepto que también sea divisible por 400.

---
### Solución

Sea "year" un número natural mayor a 1582 y sea:
    
    p(year) :  year % 4 = 0
    q(year) :  year % 100 = 0
    r(year) :  year % 400 = 0
    
Siendo "%" la operación que devuelve el resto de dividir el primer operando por el segundo (división entera), y sea:

IsBisiesto(year): Naturales -> Booleanos  

Se desarrolló la función "IsBisiesto" que retorna el valor booleano resultante del siguiente árbol de operaciones:


![Arbol](https://github.com/Ferig83/AED/blob/master/03-Bisiesto/tp3ayed.png)


Esto implica que la expresión de retorno será :

  p AND ((q AND r) OR NOT(q))
  
  Es decir, será:
  
  (year % 4 = 0) AND ((year % 100 = 0 AND year % 400 = 0) OR ¬(year % 100 = 0))
  
  Se comprueban con varios años utilizando la función ASSERT, dando resultados satisfactorios.  


### Extra

La versión en ASM hace lo mismo, solo que nuestros asserts no señalan en qué comparación tenemos el error. 
Podríamos implementarlo salvando un argumento como cadena pero a fines prácticos lo mejor sería poner un identificador.
De momento, me centro en el uso de las operaciones booleanas (y lo útil que es el arbol de operaciones cuando
nos vamos al bajo nivel!).


