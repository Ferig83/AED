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

Sea x un número natural mayor a 1582 y sea:
    
    p(x) :  x % 4 = 0
    q(x) :  x % 100 = 0
    r(x) :  x % 400 = 0

Se desarrolló una función que retorna el valor booleano resultante del siguiente árbol de operaciones:


