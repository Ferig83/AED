## TP 04-Polígonos

---

### Análisis del problema

#### Enunciado
 Crear tipos de datos para polígonos y triángulos, proponiendo y definiendo distintas operaciones.

#### Restricciones
No utilizar vectores dinámicos (ej: std::vector).  

#### Léxico e Hipotesis de trabajo

Debemos representar a los polígonos y triángulos como un conjunto de vértices en el plano R^2. Por definición, un polígono no debería tener menos de tres vértices, por lo que el polígono más pequeño es el triángulo. Además, cada polígono tendrá un color y vamos a utilizar el sistema RGB de 24 bits para representarlo (sin el "alpha" que se suele utilizar para transparencia): El sistema consiste en representar el rojo, verde y azúl con un byte cada uno y en ese orden, siendo 00h la ausencia del color y FFh el máximo posible (por ejemplo, el 00FF00h es un verde intenso).

Como operaciones vamos a definir las siguientes:

#### Léxico

Sea "vértice" un par ordenado en R^2, "polígono" un conjunto finito de vértices. "índice" la posición del vértice, siendo 0 el primero y cantidad total - 1 el último. Sea "color" el conjunto de 3 bytes que representan el rojo, verde y azul (en ese orden). 


- Inicializar_Figura:  vértices --> polígono

Convierte un conjunto vértices y lo transforma en un polígono o triángulo (color negro por defecto)

- Mostrar_Todos_Los_Vertices: polígono --> vertices

Muestra como par ordenado todos los vértices del polígono

- getVertice: polígono x índice --> vértice
  
Devuelve un vértice según índice (del "0" a "cantidad de vertices - 1")

- getPerimetro: polígono --> R

Devuelve el perímetro del polígono, suponiéndolo cerrado (conecta los vértices en orden, y el último vértice con el primero)

- getLongitud:  polígono x índice x índice --> R

Devuelve la longitud de los segmentos que conectan dos vértices referenciados por los índices

- getDistancia: polígono x índice x índice --> R

Devuelve la distancia entre dos vértices, referenciados por sus índices

- getAngulo:  polígono x índice --> R 

Devuelve el ángulo en radianes de un vértice, referenciado por su índice

- getColor:  polígono --> color

Devuelve el color de un polígono

- setColor: polígono x color --> polígono

Cambia el color de un polígono

- AgregarVerticeAlFinal: polígono x vértice --> polígono

Agrega un vértice al final del polígono (recordar que el orden es importante para el cálculo de ángulos)

- BorrarUltimoVertice: polígono --> polígono

Borra el último vértice de un polígono

- getCantidadVertices(T &t): polígono --> N

Devuelve la cantidad de vértices de un polígono


---

#### Modelo IPO y resolución del problema:

(en desarrollo)

### Extra

La versión en lenguaje ensamblador no va a estar disponible para este trabajo práctico, pero en su lugar sugiero ver un visualizador de objetos 3D que estoy desarrollando, programado 100% en NASM: https://github.com/Ferig83/Visor3D_ASM   (solo para Windows, x64)

Cubre de sobra todos los conceptos (y muchos más!), excepto el de plantillas/templates. Además es muy lindo de ver :)  
