#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/heap.h"
#include "tdas/extra.h"
#include "tdas/stack.h"
#include "tdas/queue.h"
#include <string.h>

typedef struct { // Estructura para almacenar los datos de los nodos del grafo

    int square[3][3]; // Matriz 3x3 que representa el tablero
    int x;    // Posición x del espacio vacío
    int y;    // Posición y del espacio vacío
    int nActions;

} State;

typedef struct Node { // Estructura para almacenar los nodos del árbol de búsqueda

    State state;
    struct Node* parent;

} Node;


void mostrarMenuPrincipal() { // Función para mostrar el menú principal

    limpiarPantalla();
    puts("========================================\n");
    puts("     Escoge método de búsqueda\n");
    puts("========================================\n");

    puts("1) Búsqueda en Profundidad");
    puts("2) Buscar en Anchura");
    puts("3) Buscar Mejor Primero");
    puts("4) Salir\n");

}

int isValidMove(int x, int y) { return (x >= 0 && x < 3 && y >= 0 && y < 3); } // Función para verificar si un movimiento es válido

void imprimirEstado(const State *estado) { // Función para imprimir el estado del tablero
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            
            if (estado->square[i][j] == 0)
                printf("x ");
            else
                printf("%d ", estado->square[i][j]);
            
        }
        printf("\n");
    }
}

int isFinal(const State* estado) { // Función para verificar si el estado actual es el estado final

    State finalState = {
        {{0, 1, 2},
         {3, 4, 5},
        {6, 7, 8}},
        0,0
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            if (estado->square[i][j] != finalState.square[i][j])
                return 0;
            
        }
    }

    return 1;
}

void copyState(State original, State* new) { // Función para copiar un estado

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            new->square[i][j] = original.square[i][j];

    new->x = original.x;
    new->y = original.y;
    new->nActions = original.nActions;
    
}

void move(State* current, int choice) { // Función para realizar un movimiento en el tablero

    int x = current->x;
    int y = current->y;
    int temp;

    switch (choice) {

        case 1: // Mover espacio vacío hacia arriba

            if (isValidMove(x , y - 1)) {

                temp = current->square[x][y - 1];
                current->square[x][y - 1] = current->square[x][y];
                current->square[x][y] = temp;
                current->y = y - 1;

            }

            break;

        case 2: // Mover espacio vacío hacia abajo

            if (isValidMove(x , y + 1)) {

                temp = current->square[x][y + 1];
                current->square[x][y + 1] = current->square[x][y];
                current->square[x][y] = temp;
                current->y = y + 1;

            }

            break;
        case 3: // Mover espacio vacío hacia la izquierda

            if (isValidMove(x - 1, y)) {

                temp = current->square[x - 1][y];
                current->square[x - 1][y] = current->square[x][y];
                current->square[x][y] = temp;
                current->x = x - 1;

            }

            break;
        case 4: // Mover espacio vacío hacia la derecha
            if (isValidMove(x + 1, y)) {

                temp = current->square[x + 1][y];
                current->square[x + 1][y] = current->square[x][y];
                current->square[x][y] = temp;
                current->x = x + 1;

            }
            break;
    }
}

State* transition(State* oldState, int action) { // Función para realizar una transición en el estado actual

    State *newState = (State*) malloc(sizeof(State)); // Crear un nuevo estado

    copyState(*oldState, newState); // Copiar el estado actual al nuevo estado
    move(newState, action); // Realizar el movimiento en el nuevo estado
    newState->nActions++; // Incrementar el número de acciones realizadas

    return newState;
    
}

List *getAdjNodes(Node* parentNode) { // Función para obtener los nodos adyacentes al nodo padre

    List *adjList = list_create();

    int x = parentNode->state.x;
    int y = parentNode->state.y;

    for (int i = 1; i <= 4; i++) { // Iterar a través de los cuatro movimientos posibles

        State *newState = transition(&parentNode->state, i); // Crear un nuevo estado con el movimiento actual

        if (newState->x != x || newState->y != y) { // Verificar si se hizo un movimiento válido

            Node *newNode = (Node*) malloc(sizeof(Node)); // Crear un nuevo nodo

            newNode->state = *newState; // Asignar el estado al nuevo nodo
            newNode->parent = parentNode; // Asignar el nodo padre al nuevo nodo
            list_pushBack(adjList, newNode); // Agregar el nuevo nodo a la lista de nodos adyacentes
            
        } else {
            free(newState); // Liberar el estado si no se hizo un movimiento válido
        }
    }
    return adjList; 
}

void dfs(State initialState, int count) { // Función para realizar el recorrido en profundidad

    Stack* stack = stack_create(stack); // Crear una pila para almacenar los nodos del árbol de búsqueda

    printf("\nEstado Original:\n\n"); 
    imprimirEstado(&initialState); // Imprimir el estado inicial
    printf("\n");

    Node *root = (Node *) malloc(sizeof(Node)); // Crear un nodo raíz

    root->parent = NULL; // Establecer el nodo padre como nulo
    root->state = initialState; // Asignar el estado inicial al nodo raíz

    stack_push(stack, root); // Agregar el nodo raíz a la pila

    while (list_size(stack) > 0) { // Mientras la pila no esté vacía

        Node *currentNode = (Node *) stack_pop(stack); // Obtener el nodo en la cima de la pila

        // printf("%d\n", currentNode->state.nActions);
        
        if (currentNode->state.nActions >= 15) // Verificar si se alcanzó el límite de acciones
            continue;

        if (isFinal(&currentNode->state)) { // Verificar si el estado actual es el estado final

            printf("¡Solución encontrada!\n");
            printf("Iteraciones: %d\n\n", count);

            Node *node = currentNode; // Inicializar un nodo auxiliar
            int steps = currentNode->state.nActions; // Inicializar el número de pasos

            while (node != NULL) { // Recorrer el árbol de búsqueda hasta el nodo raíz

                if (steps == 0) 
                    printf("Estado Inicial:\n\n");  // Imprimir el estado inicial

                else
                    printf("Paso %d:\n\n", steps);  // Imprimir el estado actual                
                
                imprimirEstado(&node->state);
                printf("\n");
                
                node = node->parent;
                steps--;
                
            }

            stack_clean(stack); // Limpiar la pila
            free(node); // Liberar el nodo auxiliar
            
            return; // Salir de la función
        }

        List *adjNodes = getAdjNodes(currentNode); // Obtener los nodos adyacentes al nodo actual
        void *aux = list_first(adjNodes); // Obtener el primer nodo de la lista de nodos adyacentes

        while (aux != NULL) {

            stack_push(stack, aux); // Agregar cada nodo adyacente a la pila
            aux = list_next(adjNodes); // Obtener el siguiente nodo de la lista de nodos adyacentes
            
        }

        list_clean(adjNodes); // Limpiar la lista de nodos adyacentes
        count++; // Incrementar el contador de iteraciones

    }

    printf("La solución no se ha encontrado en el rango limitado (15).\n"); 
    stack_clean(stack); // Limpiar la pila
}

void bfs(State initialState, int count) { // Función para realizar el recorrido en amplitud

    Queue* queue = queue_create(queue); // Crear una cola para almacenar los nodos del árbol de búsqueda

    printf("Estado Inicial:\n\n");
    imprimirEstado(&initialState); // Imprimir el estado inicial
    printf("\n");

    Node *root = (Node *) malloc(sizeof(Node ));
    
    root->parent = NULL; // Establecer el nodo padre como nulo
    root->state = initialState; // Asignar el estado inicial al nodo raíz
    queue_insert(queue, root); // Agregar el nodo raíz a la cola

    while (list_size(queue) > 0) { // Mientras la cola no esté vacía

        Node *currentNode = (Node *) queue_remove(queue);

        if (count >= 15000000) { // Verificar si se alcanzó el límite de iteraciones
            
            printf("Proceso abortado: Límite de iteraciones excedido (15.000.000)\n");
            return;
            
        }

        if (isFinal(&currentNode->state)) { // Verificar si el estado actual es el estado final

            printf("¡Solución encontrada!\n");
            printf("Iteraciones: %d\n\n", count);

            Node *node = currentNode; // Inicializar un nodo auxiliar
            int steps = currentNode->state.nActions; // Inicializar el número de pasos

            while (node != NULL) { // Recorrer el árbol de búsqueda hasta el nodo raíz

                if (steps == 0) 
                    printf("Estado Inicial:\n\n");  // Imprimir el estado inicial

                else
                    printf("Paso %d:\n\n", steps); // Imprimir el estado actual             

                imprimirEstado(&node->state); // 
                printf("\n");

                node = node->parent;
                steps--;

            }

            queue_clean(queue); // Limpiar la cola
            free(node); // Liberar el nodo auxiliar

            return;
        }

        List *adjNodes = getAdjNodes(currentNode); // Obtener los nodos adyacentes al nodo actual
        void *aux = list_first(adjNodes); // Obtener el primer nodo de la lista de nodos adyacentes

        while (aux != NULL) {

            queue_insert(queue, aux); // Agregar cada nodo adyacente a la cola
            aux = list_next(adjNodes); // Obtener el siguiente nodo de la lista de nodos adyacentes
            
        }

        list_clean(adjNodes); // Limpiar la lista de nodos adyacentes
        count++; // Incrementar el contador de iteraciones
        
    }

    printf("No se ha encontrado la solución.\n"); 
    queue_clean(queue); // Limpiar la cola
    
}

int main() {

    State estado_inicial = {
        {{0, 2, 8}, // Primera fila (0 representa espacio vacío)
         {1, 3, 4}, // Segunda fila
         {6, 5, 7}, // Tercera fila
         },  
        0, 0   // Posición del espacio vacío (fila 0, columna 0)
    };

    estado_inicial.nActions = 0; // Inicializar el número de acciones realizadas en el estado inicial

    int opcion; // Variable para almacenar la opción seleccionada por el usuario
    int cont = 0; // Variable para contar el número de iteraciones
    
    do { // Bucle para mostrar el menú y realizar las operaciones seleccionadas por el usuario
        
        mostrarMenuPrincipal(); // Mostrar el menú principal
        printf("Ingrese su opción: ");
        scanf(" %d", &opcion); // Leer la opción seleccionada por el usuario
    
        switch (opcion) {
            
        case 1: // Opción 1: Resolver el puzzle usando DFS
            
          dfs(estado_inicial, cont);
          break;
            
        case 2: // Opción 2: Resolver el puzzle usando BFS
            
          bfs(estado_inicial, cont);
          break;
            
        case 3: // Opción 3: Salir del programa
            
          printf("This option is not available in this version of the program.\n");
          break;
            
        case 4: // Opción 4: Salir del sistema.
            
            printf("Saliendo del programa...\n");
            break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();

  } while (opcion != 4);

  return 0;
}
