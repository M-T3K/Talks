#include <stdio.h>
#include <stdlib.h>

// Esto es como un struct normal, pero nos permite ademas identificarlo como un tipo para no tener que poner "struct Vagon nombre_de_variable" todo el rato
// De esta forma podemos poner solo "nombre_de_variable"
typedef struct {
    int num_vagon;
    int cap_pasajeros;
} Vagon;

// Queremos añadir un vagon al tren: 
// TENEMOS QUE VOLVER A RESERVAR TODO! -> MUY INEFICIENTE
Vagon *anadir_vagon(Vagon *tren, int *num_vagones, int cap_pasajeros) {
    Vagon *nuevo_tren = (Vagon *)realloc(tren, (*num_vagones + 1) * sizeof(Vagon));
    if (nuevo_tren == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    
    nuevo_tren[*num_vagones].num_vagon = *num_vagones;
    nuevo_tren[*num_vagones].cap_pasajeros = cap_pasajeros;
    (*num_vagones)++;
    return nuevo_tren;
}

Vagon *quitar_vagon(Vagon *tren, int *num_vagones) {
    if (*num_vagones == 0) {
        printf("No hay vagones para quitar.\n");
        return tren;
    }
    
    Vagon *nuevo_tren = (Vagon *)realloc(tren, (*num_vagones - 1) * sizeof(Vagon));
    if (nuevo_tren == NULL && *num_vagones - 1 > 0) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    
    (*num_vagones)--;
    return nuevo_tren;
}

void imprimir_tren(const Vagon *tren, int num_vagones) {
    for (int i = 0; i < num_vagones; ++i) {
        printf("Vagon %d: Capacidad de pasajeros: %d\n", tren[i].num_vagon, tren[i].cap_pasajeros);
    }
}

int main() {
    Vagon *tren = NULL;
    
    // No tenemos porque guardar esta variable SI FUESE UN ARRAY Bien delimitado
    // pero hace este codigo un poco mas eficiente al no tener que calcular todo el rato las dimensiones del array
    // Para calcular estas dimensiones podriamos hacer:
    // sizeof(array) / sizeof(array[0]);
    // Lo que se traduce a sizeof(array) / sizeof(Vagon)
    // Es decir, tamano del array en bytes dividido por el tamano del tipo del array
    int num_vagones = 0;
    
    // Locomotora
    tren = anadir_vagon(tren, &num_vagones, 1);
    // Vagon1 y Vagon2
    tren = anadir_vagon(tren, &num_vagones, 30);
    tren = anadir_vagon(tren, &num_vagones, 30);
    // Cafeteria
    tren = anadir_vagon(tren, &num_vagones, 12);
    
    imprimir_tren(tren, num_vagones);
    
    tren = quitar_vagon(tren, &num_vagones);
    
    printf("Separacion\n");
    
    imprimir_tren(tren, num_vagones);
    
    free(tren);
    
    return 0;
}