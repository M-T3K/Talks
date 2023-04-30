#include <stdio.h>

int variable_global = 100;

void funcion_ejemplo() {
    
    printf("\nfuncion_ejemplo():\n\n");
    
    int variable_local = 200;
    
    printf("Dentro de funcion_ejemplo():\n");
    printf("Variable global desde funcion_ejemplo(): %d\n", variable_global);
    printf("Variable local desde funcion_ejemplo(): %d\n", variable_local);
    {
        printf("\nscope_interno: {}\n\n");
        int variable_interna = 300;
        printf("Dentro del bloque interno:\n");
        printf("Variable global: %d\n", variable_global);
        printf("Variable local: %d\n", variable_local);
        printf("Variable interna: %d\n", variable_interna);
    }
    
    // La siguiente línea generaría un error de compilación, ya que variable_interna no está en el mismo scope.
    // printf("Variable interna fuera del scope interno: %d\n", variable_interna);
}

int main() {
    printf("main():\n");
    printf("Variable global: %d\n", variable_global);
    // La siguiente línea generaría un error de compilación, ya que variable_local no está en la misma scope:
    // printf("Variable local fuera de la función: %d\n", variable_local);
    
    funcion_ejemplo();
    
    return 0;
}