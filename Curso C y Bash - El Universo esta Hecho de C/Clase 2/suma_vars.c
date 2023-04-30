#include <stdio.h>
#include <stdarg.h> // VA = Varible Arguments!

int suma(int num_args, ...) {
    int total = 0;
    va_list args;
    
    va_start(args, num_args);
    
    for (int i = 0; i < num_args; i++) {
        total += va_arg(args, int);
    }
    
    va_end(args);
    
    return total;
}

// Esto no se hace demasiado a menudo, porque la mayor parte del tiempo no es necesario para casi nada
// pero por ejemplo si intentais implementar vuestra propia version de printf, os ayudara!
int main() {
    int resultado1 = suma(4, 1, 2, 3, 4);
    int resultado2 = suma(5, 10, 20, 30, 40, 50);
    
    printf("Suma de 1, 2, 3, 4: %d\n", resultado1);
    printf("Suma de 10, 20, 30, 40, 50: %d\n", resultado2);
    
    return 0;
}