// Cosas a tratar

// 1. Mandatos basicos de Bash para navegar directorios
// CD, MV, CP, mkdir, touch, ...

// 2. Compilar un codigo C en entorno unix con GCC
// gcc -flags 
// Ej. Comun : gcc -o nombre_ejecutable fichero_a_compilar
// Flags mas avanzadas en clases futuras!

// 3. Algunas curiosidades de C
// 3.1 Flags -> Utilidad en entornos profesionales, sobretodo por aprovechamiento de memoria
// 3.2 Strings en C

// 4. Punteros
// 4.1 Manejar memoria != Punteros (quitaros el miedo!) - Ej. Golang vs Java vs C, Recoleccion de Basura (Casi todos los lenguajes tienen punteros aunque no los veamos de forma evidente)
// 4.2 Caso Ejemplo / Google, Biblitoeca, enlaces, etc
// 4.3 Caso Ejemplo / Gamehacking

// 5. Mallocs y reserva dinamica de memoria.
// 5.1 Cuando se usa Malloc y la memoria dinamica
// 5.2 Malloc, Calloc, Realloc, Memset, Free, ...
// 5.3 ¿Por que son importantes los punteros? 

// 6. Void *: o lo que yo llamo Programar C a lo Python sin tener ni idea

// 7. Dudas y demas, lo que surja

// PREGUNTA 1: ¿CUANDO SE USA MALLOC?

// Existen 3 casos (que yo sepa) en los que se debe usar 
// una reserva (memory allocation, reserva de memoria) dinamica
// de memoria para un programa en HEAP (siempre se reserva memoria
// aunque sea en el stack aka Pila)

// 1) Si se trata de una cantidad / tamaño de datos dinamico, es decir que no conoces su tamaño real. Ej. Su tam depende de argumentos

// 2) cuando quieres que los datos perduren mas alla del bloque de ejecucion, por ejemplo, en una funcion.

// 3) Cuando los datos ocupan mas que tu stack y no te queda otra.
// Esta no la vamos a ver porque es muy absurda en la actualidad

#include <stdio.h>

int main(int argc, char* argv[]) {
    
    //for(int i = 0; i < argc; ++i) {
    //printf("[i]: %d -> %s\n", i, argv[i]);
    //}
    int numero = 0;
    
    int* dir_de_numero = &numero;
    printf("%ls %d", dir_de_numero, numero);
    return 0;
}
// Hay soluciones a algunas preguntas al final del archivo





































































// Algunas soluciones a preguntas que haya por ahi en el codigo


// Q1: porque sino no puedes meter el caracter nulo \0