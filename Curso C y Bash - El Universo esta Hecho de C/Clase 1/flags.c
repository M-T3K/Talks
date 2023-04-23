#include <stdio.h>

// Definimos las Flags
#define PRINT_UPPERCASE (1 << 0) // 0001
#define PRINT_LOWERCASE (1 << 1) // 0010
#define PRINT_NUMBERS   (1 << 2) // 0100

void print_data(unsigned int flags) {
    
    if (flags & PRINT_UPPERCASE) {
        printf("Uppercase letters: ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    }
    if (flags & PRINT_LOWERCASE) {
        printf("Lowercase letters: abcdefghijklmnopqrstuvwxyz\n");
    }
    if (flags & PRINT_NUMBERS) {
        printf("Numbers: 0123456789\n");
    }
    
}

// Un boolean es una variable, generalmente de tipo int
// Eso quiere decir que usa todo el espacio de un int, que puede ser 4 u 8 Bytes, generalmente
// Es decir, esto:

// 00000000 00000000 00000000 00000101

// Una flag, en cambio, solo ocupa 1 bit, es decir, esto:

// 0

// Ademas, varias flags se pueden combinar, resultando en que en el espacio de un boolean nada mas puedes tener muchas flags

int main() {
    unsigned int flags = PRINT_UPPERCASE | PRINT_NUMBERS;
    print_data(flags);
    
    char* str = "lkasjdlkajsdlkasd\n";
    return 0;
}