// 1. Funcion Main, argumentos / Revision Rapida
// 2. Constantes
#include <stdio.h>
// 3. PreIncremento vs PostIncremento (No quedó del todo claro en la anterior)
// El Postincremento crea una copia de la variable muchas veces => Con Preincremento te lo ahorras!
// clase2_pre.s vs clase2_pos.s
// Documentacion de Google, aunque para C++
//https://google.github.io/styleguide/cppguide.html#Preincrement_and_Predecrement

// Ficheros compilados de este codigo:
//int main(const int argc, const char *argv[]) {
//    for(int i = 0; i < argc; i++);
//    return 0;
//}

// 4. Scope

// 5. Structs
// 5.1 Typedef
// 5.2 Tight Packing

// 6. Parametros
// 6.1 Paso de parámetros por Valor vs Referencia
// 6.2 Listas de Argumentos de Longitud Variable
//     printf(".....", ...)?

// 7. I/O
// 7.1 Printf
// 7.2 Scanf
// 7.3 FILE -> Ficheros
// 7.5 Pipes Básicos: Ejemplos de Bash con fortune, cowsay, etc

// int main(const int argc, const char *argv[]) {
int main(int argc, char *argv[]) {
    
    printf("Cantidad de Argumentos: %d\n", argc);
    
    for(int i = 0; i < argc; ++i) {
        printf("%d -> %s\n", i, argv[i]);
    }
    
    return 0;
}

































