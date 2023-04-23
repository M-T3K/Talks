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

// Esto es caso 1: COPY ON RETURN
struct Vagon crea_vagon(int num_vagon, int cap_pasajeros, struct Vagon* sig_vagon) {
    struct Vagon* vagoncito;
    vagoncito.num_vagon = num_vagon;
    vagoncito.cap_pasajeros = cap_pasajeros;
    vagoncito.siguiente_vagon = sig_vagon;
    
    // !!!!!!!! Esto puede resultar muy caro !!!!!!!!!
    
    // &vagoncito
    return vagoncito; // Se esta creando una COPIA
}

int main(int argc, char *argv[]) {
    
    struct Vagon cafeteria = crea_vagon(3, 12, NULL); 
    struct Vagon vagon2 = crea_vagon(2, 30, &cafeteria);
    struct Vagon vagon1 = crea_vagon(1, 30, &vagon2);
    struct Vagon cabeza_locomotora = crea_vagon(0, 1, &vagon1);
    
    struct Vagon vagon = cabeza_locomotora;
    
    while(1) {
        printf("Vagon %d, capacidad %d pasajeros\n", vagon.num_vagon, vagon.cap_pasajeros);
        if(vagon.siguiente_vagon == NULL) {
            break;
        }
        vagon = *vagon.siguiente_vagon;
    }
    
    return 0;
}