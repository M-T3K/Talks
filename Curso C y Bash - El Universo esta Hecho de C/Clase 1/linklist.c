// Ejemplos: trenes, ¿caza del tesoro? aka Scavenger Hunt
#include <stdio.h> // printf
#include <stddef.h> // NULL
#include <stdlib.h> // malloc

// PREGUNTA 1: ¿CUANDO SE USA MALLOC?

// Existen 3 casos (que yo sepa) en los que se debe usar 
// una reserva (memory allocation, reserva de memoria) dinamica
// de memoria para un programa en HEAP (siempre se reserva memoria
// aunque sea en el stack aka Pila)

// 1) Si se trata de una cantidad / tamaño de datos dinamico, es decir que no conoces su tamaño real. Ej. Su tam depende de argumentos

// 2) cuando quieres que los datos perduren mas alla del bloque de ejecucion, por ejemplo, en una funcion.

// 3) Cuando los datos ocupan mas que tu stack y no te queda otra.
// Esta no la vamos a ver porque es muy absurda en la actualidad

// LOCOMOTORA -> VAGON1 -> VAGON2 -> CAFETERIA -> FIN

struct Vagon {
    int num_vagon; 
    int cap_pasajeros;
    struct Vagon* siguiente_vagon;
};

#define TAM_VAGON sizeof(struct Vagon)

int main(int argc, char *argv[]) {
    // Version Malloc
    
    int dir_locomotora = 0;
    struct Vagon* cabeza_locomotora; // 4 u 8 Bytes
    struct Vagon* vagon1;
    struct Vagon* vagon2;
    struct Vagon* cafeteria;
    
    cabeza_locomotora = (struct Vagon*) malloc(TAM_VAGON);
    vagon1 = (struct Vagon*) malloc(TAM_VAGON);
    vagon2 = (struct Vagon*) malloc(TAM_VAGON);
    cafeteria = (struct Vagon*) malloc(TAM_VAGON);
    
    // Adjudicamos un numero y capacidad a los vagones
    cabeza_locomotora->num_vagon = 0;
    cabeza_locomotora->cap_pasajeros = 1;
    
    vagon1->num_vagon = 1;
    vagon1->cap_pasajeros = 30;
    
    vagon2->num_vagon = 2;
    vagon2->cap_pasajeros = 30;
    
    cafeteria->num_vagon = 3;
    cafeteria->cap_pasajeros = 12;
    
    // Enlazamos los Vagones
    
    cabeza_locomotora->siguiente_vagon = vagon1;
    vagon1->siguiente_vagon = vagon2;
    vagon2->siguiente_vagon = cafeteria;
    cafeteria->siguiente_vagon = NULL; // No hay otro vagon
    
    struct Vagon* vagon = cabeza_locomotora;
    
    while(vagon != NULL) {
        printf("Vagon %d, capacidad %d pasajeros\n", vagon->num_vagon, vagon->cap_pasajeros);
        vagon = vagon->siguiente_vagon;
    }
    
    return 0;
}