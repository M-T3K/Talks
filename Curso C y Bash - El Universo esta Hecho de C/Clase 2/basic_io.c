#include <stdio.h>

int main() {
    int numero;
    float decimal;
    char cadena[50];
    
    // Leer un número entero desde stdin
    printf("Número entero: ");
    scanf("%d", &numero);
    
    // Leer un número decimal desde stdin
    printf("Número decimal: ");
    scanf("%f", &decimal);
    
    // Leer una cadena de caracteres desde stdin
    printf("String: ");
    scanf(" %[^\n]", cadena); // El espacio antes de % y [^\n] permiten leer un string con espacios! (avanzado, nos os preocupeis)
    
    // Escribir los valores leídos en stdout
    printf("Número entero: %d\n", numero);
    printf("Número decimal: %.2f\n", decimal);
    printf("Cadena de texto: %s\n", cadena);
    
    // Escribir un mensaje en stderr
    fprintf(stderr, "Este es un mensaje de error.\n");
    
    return 0;
}