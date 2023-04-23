// Ejemplos: trenes, ¿caza del tesoro? aka Scavenger Hunt
#include <stdio.h> // printf
#include <stddef.h> // NULL
#include <stdlib.h> // malloc, calloc, realloc, ...

struct Vagon {
    int num_vagon;
    int cap_pasajeros;
    struct Vagon* siguiente_vagon;
};

#define TAM_VAGON sizeof(struct Vagon)

// Esto usa MALLOC para evitar Copy on Return
struct Vagon* malloc_vagon(int num_vagon, int cap_pasajeros, struct Vagon* sig_vagon) {
    struct Vagon* vagoncito = malloc(TAM_VAGON);
    vagoncito->num_vagon = num_vagon;
    vagoncito->cap_pasajeros = cap_pasajeros;
    vagoncito->siguiente_vagon = sig_vagon;
    
    // Aqui estamos devolviendo un puntero a la direccion de memoria que hemos reservado
    // Esa memoria va a persistir incluso al terminar la funcion
    return vagoncito;
}

int main(int argc, char *argv[]) {
    
    struct Vagon* cafeteria = malloc_vagon(3, 12, NULL);
    struct Vagon* vagon2 = malloc_vagon(2, 30, cafeteria);
    struct Vagon* vagon1 = malloc_vagon(1, 30, vagon2);
    struct Vagon* cabeza_locomotora = malloc_vagon(0, 1, vagon1);
    
    struct Vagon* vagon = cabeza_locomotora;
    
    while(vagon != NULL) {
        printf("Vagon %d, capacidad %d pasajeros\n", vagon->num_vagon, vagon->cap_pasajeros);
        struct Vagon* old_vagon = vagon;
        vagon = vagon->siguiente_vagon;
        free(old_vagon); // Liberamos memoria que hemos reservado antes
    }
    
    return 0;
}