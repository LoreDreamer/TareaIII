# SOLUCIÓN PUZZLE 8

### DESCRIPCIÓN

Este sistema permite buscar de dos formas distintas la solución a un puzzle 8. Las dos acciones posibles son buscar la solución mediante DFS (Búsqueda en profundidad o Deep-First Search) y BFS (Búsqueda en Anchura). La diferencia principal entre estos dos métodos se basa en la forma de buscar y la cantidad de iteraciones que hacen para poder llegar al resultado, lo cual se puede ver en el número de iteraciones que tomó para poder llegar a la solución.

### COMO USAR

Para poder usar el sistema, usted debe hacer uso del Fork & Run a su derecha en la pantalla. Tras hacer eso, debe hacer uso del siguiente comando para poder hacer uso del buscador de películas.

````
./tarea3
````

También puede hacer uso del botón Run en la parte superior de la página, la cual revisará el código por errores y después lo ejecutará.

## FUNCIONALIDADES

### FUNCIONA CORRECTAMENTE:

- Busca correctamente la solución del ejemplo asociado en DFS.
- Busca correctamente la solución del ejemplo asociado en BFS.

### PROBLEMAS CONOCIDOS:

- Actualmente la función 'Greedy Best-First Search' no se encuentra implementada en el programa.
- Para el DFS, hay un límite de altura o de pasos para los puzzles 8. Si su puzzle 8 no se resuelve dentro de los 15 pasos, el programa dará el puzzle sin solución.
- Cabe mencionar que en el DFS, el puzzle hará movimientos innecesarios al tratar de llegar a solución por el simple hecho de querer cumplir con el límite de 15 pasos.
- Algo similar se aplica en el BFS, ya que si el puzzle llega a un límite de iteraciones (actualmente 15.000.000), el programa cerrará para evitar errores por parte del compilador.
- No se recomienda cambiar el puzzle de ejemplo en la función main, ya que con otras variantes del puzzle este podría no entregar soluciones debido a las restricciones mencionadas anteriormente.

## EJEMPLO DE USO

Para empezar, debemos nos encontraremos con el menu:

````
========================================

     Choose a search method

========================================

1) Deep-First Search
2) Breadth-First Search
3) Greedy Best-First Search
4) Exit

Choose an option:
````

Tenemos 4 opciones dentro del menu, las cuales serán explicadas, partiendo desde el Deep-First Search o Búsqueda en Profundidad:

````
========================================

     Choose a search method

========================================

1) Deep-First Search
2) Breadth-First Search
3) Greedy Best-First Search
4) Exit

Choose an option: 1

Original State:

x 2 8 
1 3 4 
6 5 7 

Puzzle solved!
Iterations: 119550

Step 14:

x 1 2 
3 4 5 
6 7 8 

Step 13:

1 x 2 
3 4 5 
6 7 8 

Step 12:

1 4 2 
3 x 5 
6 7 8 

Step 11:

1 4 2 
3 5 x 
6 7 8 

Step 10:

1 4 2 
3 5 8 
6 7 x 

Step 9:

1 4 2 
3 5 8 
6 x 7 

Step 8:

1 4 2 
3 x 8 
6 5 7 

Step 7:

1 x 2 
3 4 8 
6 5 7 

Step 6:

1 2 x 
3 4 8 
6 5 7 

Step 5:

1 2 8 
3 4 x 
6 5 7 

Step 4:

1 2 8 
3 x 4 
6 5 7 

Step 3:

1 2 8 
x 3 4 
6 5 7 

Step 2:

1 2 8 
6 3 4 
x 5 7 

Step 1:

1 2 8 
x 3 4 
6 5 7 

Initial State:

x 2 8 
1 3 4 
6 5 7 

Press Enter to continue . . .

````

Como puede ver, el programa entrega la solución de nuestro puzzle en 14 pasos o 15 si contamos el estado inicial como paso. Después, tenemos como segunda opción el uso del Breadth-First Search o Búsqueda en Anchura: 

````
========================================

     Choose a search method

========================================

1) Deep-First Search
2) Breadth-First Search
3) Greedy Best-First Search
4) Exit

Choose an option: 2
Initial State:

x 2 8 
1 3 4 
6 5 7 

Puzzle solved!
Iterations: 221143

Step 12:

x 1 2 
3 4 5 
6 7 8 

Step 11:

1 x 2 
3 4 5 
6 7 8 

Step 10:

1 4 2 
3 x 5 
6 7 8 

Step 9:

1 4 2 
3 5 x 
6 7 8 

Step 8:

1 4 2 
3 5 8 
6 7 x 

Step 7:

1 4 2 
3 5 8 
6 x 7 

Step 6:

1 4 2 
3 x 8 
6 5 7 

Step 5:

1 x 2 
3 4 8 
6 5 7 

Step 4:

1 2 x 
3 4 8 
6 5 7 

Step 3:

1 2 8 
3 4 x 
6 5 7 

Step 2:

1 2 8 
3 x 4 
6 5 7 

Step 1:

1 2 8 
x 3 4 
6 5 7 

Initial State:

x 2 8 
1 3 4 
6 5 7 

Press Enter to continue . . .
````

Como pueden ver, a comparación del DFS, el Breadth-First Search toma más tiempo debido a la necesidad de usar más memoria para ciertas operaciones. 

Para finalizar, tenemos la opción de Greedy Best-First Search que actualmente no se encuentra disponible, por lo que tenemos que avanzar a la opción para salir del sistema:

````
========================================

     Choose a search method

========================================

1) Deep-First Search
2) Breadth-First Search
3) Greedy Best-First Search
4) Exit

Choose an option: 4
Saliendo del programa...
Press Enter to continue . . .

````

---

En caso de que haya problemas con el código, usted puede contactar al desarrollador de la aplicación mediante GitHub. Solamente haga uso de este código en el shell y contacte al desarrollador con todos los detalles posibles:

````
gcc tdas/*.c tarea3.c -Wno-unused-result -o tarea3
````