#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t a; // 4
    char b;    // 1
    // RELLENO (3)
    float c;   // 4
} Struct1;

typedef struct {
    char a; // 1
    int32_t b; // 4
    double c; // 8
} Struct2;

typedef struct {
    char a; // 1
    char b; // 1
    // RELLENO 2
    int32_t c; // 4
    int64_t d; // 8
} Struct3;

typedef struct {
    int16_t a; // 2 -
    // RELLENO 2    -
    int32_t b; // 4
    float c;   // 4
    char d;    // 1
} Struct4;

typedef struct {
    char a; // 1
    char b; // 1
    char c; // 1
    char d; // 1
    int16_t e; // 2
} Struct5;

// El compilador tiene un "stack / pila" propio

#pragma pack(push, 1)

typedef struct {
    int32_t a;// 4
    char b;   // 1
    float c;  // 4
} PackedStruct1;

typedef struct {
    char a;   // 1
    int32_t b;// 4
    double c; // 8 (En mi caso, al ser un sistema de 64 bits)
} PackedStruct2;

typedef struct {
    char a;   // 1
    char b;   // 1
    int32_t c;// 4
    int64_t d;// 8
} PackedStruct3;

typedef struct {
    int16_t a; // 2
    int32_t b; // 4
    float c;   // 4
    char d;    // 1
} PackedStruct4;

typedef struct {
    char a; // 1
    char b; // 1
    char c; // 1
    char d; // 1
    int16_t e; // 2
} PackedStruct5;

#pragma pack(pop)

// Esto es importante porque te permite aprovechar mejor el espacio
// Pero por otro lado, hacerlo a lo loco, puede causar que no podais 
// aprovechar al maximo la velocidad de los ciclos de lectura
// ya que para una CPU es mas eficiente leer 4 Bytes de informacion de golpe
// que leer 1


// Siguiendo esta misma linea, tambien podemos especificar el tamano de cualquier miembro dentro de un struct en lo que se llama bitfield

typedef struct {
    unsigned int edad: 7; // Max 127! 4B - 7b
    // 3B1b
    char *nombre;
} Person;

int main() {
    printf("Tamano sin empaquetar:\n");
    printf("Struct1: %zu bytes\n", sizeof(Struct1));
    printf("Struct2: %zu bytes\n", sizeof(Struct2));
    printf("Struct3: %zu bytes\n", sizeof(Struct3));
    printf("Struct4: %zu bytes\n", sizeof(Struct4));
    printf("Struct5: %zu bytes\n", sizeof(Struct5));
    
    printf("\n\nTamano empaquetados:\n");
    printf("PackedStruct1: %zu bytes\n", sizeof(PackedStruct1));
    printf("PackedStruct2: %zu bytes\n", sizeof(PackedStruct2));
    printf("PackedStruct3: %zu bytes\n", sizeof(PackedStruct3));
    printf("PackedStruct4: %zu bytes\n", sizeof(PackedStruct4));
    printf("PackedStruct5: %zu bytes\n", sizeof(PackedStruct5));
    
    printf("\nEjemplo de Persona usando bitfields\n");
    
    Person persona = { .edad = 127, .nombre = "Juan"};
    
    printf("%s -> %d\n", persona.nombre, persona.edad);
    
    persona.edad++;
    
    printf("%s -> %d\n", persona.nombre, persona.edad);
    
    return 0;
}