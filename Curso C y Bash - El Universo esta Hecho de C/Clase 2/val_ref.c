#include <stdio.h>

typedef struct {
    int x;
    int y;
} Punto;

void imprimir_punto(const char *mensaje, Punto punto) {
    printf("%s (%d, %d)\n", mensaje, punto.x, punto.y);
}

// Función que modifica la estructura pasada por valor
void modificar_punto_por_valor(Punto punto) {
    punto.x += 10;
    punto.y += 10;
    imprimir_punto("Punto en la funcion de modificacion por valor:", punto);
}

// Función que modifica la estructura pasada por referencia
void modificar_punto_por_referencia(Punto *punto) {
    punto->x += 10;
    punto->y += 10;
}

int main() {
    
    Punto punto1 = {5, 5};
    Punto punto2 = {5, 5};
    
    imprimir_punto("Punto original 1:", punto1);
    modificar_punto_por_valor(punto1);
    imprimir_punto("Punto 1 después de modificar por valor:", punto1);
    
    imprimir_punto("Punto original 2:", punto2);
    modificar_punto_por_referencia(&punto2);
    imprimir_punto("Punto 2 después de modificar por referencia:", punto2);
    
    return 0;
}