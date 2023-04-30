#include <stdio.h> // PRINTF
#include <stddef.h> // NULL
#include <stdlib.h> // malloc

typedef unsigned int edad; // Ahora "edad" es un tipo que se puede utilizar
typedef int *edad_puntero; // Ahora cuando queramos hacer un puntero al tipo edad, podemos usar simplemente el tipo edad_puntero

typedef struct CazaTesoros {
    char *pista;
    struct CazaTesoros *siguiente_pista;
} BuscaTesoros;

// El Typedef solo funciona A PARTIR de este punto porque typedef depende de scope!

// Tambien puedes hacer un #define
// #define BuscaTesoros struct Cazatesoros
// En este caso, se usa el preprocesador de C en lugar del compilador!
// Ademas, seria global y "copia/pega"

int main(int argc, char *argv[]) {
    
    // Si no usasemos typedef, al crear un struct tendriamos que hacer:
    // struct Struct nombre_variable;
    // Por ejemplo, como haciamos con el tren:
    // struct Vagon locomotora;
    // Con Typedef, podemos hacer:
    // BuscaTesoros busqueda;
    // A partir de C99:
    
    BuscaTesoros busqueda = { .pista = "Da 3 pasos a la derecha", .siguiente_pista = NULL};
    
    // Si no (como en PPS):
    
    BuscaTesoros busqueda2;
    busqueda2.pista = "Da 3 pasos a la izquierda";
    busqueda2.siguiente_pista = &busqueda;
    
    busqueda.siguiente_pista = &busqueda2;
    
    BuscaTesoros b = busqueda;
    for(int i = 0; i < 10; ++i) {
        printf("%s\n", b.pista);
        b = *b.siguiente_pista;
    }
    
    edad mi_edad = 100;
    edad_puntero puntero_a_mi_edad = &mi_edad;
    
    printf("%p -> %d: %d\n", puntero_a_mi_edad, *puntero_a_mi_edad, mi_edad);
    
    // Ahora para usar el ejemplo de edad:
    
    return 0;
}