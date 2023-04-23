#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **crearArrayDinamico(int numStrings, int* longitudes) {
    char** arrayDinamico = (char**) malloc(numStrings * sizeof(char *));
    
    if (arrayDinamico == NULL) {
        printf("Fallo en reserva de memoria.\n");
        exit(1);
    }
    
    for (int i = 0; i < numStrings; ++i) {
        // Q1: Necesitamos reservar longitudes[i] + 1
        // ¿Quien me dice por que?
        arrayDinamico[i] = (char *)malloc((longitudes[i] + 1) * sizeof(char));
        
        if (arrayDinamico[i] == NULL) {
            printf("Fallo en reserva de memoria.\n");
            exit(1);
        }
        
        // Terminamos el String con NULL CHAR
        arrayDinamico[i][longitudes[i]] = '\0';
    }
    
    return arrayDinamico;
}

void liberarArrayDinamico(char **arrayDinamico, int numStrings) {
    for (int i = 0; i < numStrings; ++i) {
        free(arrayDinamico[i]);
    }
    free(arrayDinamico);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <longitud de Strings>\n", argv[0]);
        return 1;
    }
    // El numero de char* que queremos es el numero de argumentos sin contar el primer elemento (que siempre es el nombre del programa)
    int numStrings = argc - 1;
    
    // Cada char* tendra una determinada longitud.
    // Por ello, necesitamos un array de longitudes que tenga la misma cantidad de longitudes que el numero de strings
    // pero malloc sin embargo requiere que pongamos el tamano en bytes
    // por lo tanto, si cada elemento del array de longitudes sera un int, el tamano total de un elemento sera sizeof(int) y el de todo el array sera num_elementos * sizeof(int)
    int *longitudes = (int *)malloc(numStrings * sizeof(int));
    
    for (int i = 0; i < numStrings; ++i) {
        longitudes[i] = atoi(argv[i + 1]);
    }
    
    char **arrayDinamico = crearArrayDinamico(numStrings, longitudes);
    
    // Llenamos los arrays de As porque si
    for (int i = 0; i <= numStrings; ++i) {
        memset(arrayDinamico[i], 'A', longitudes[i]);
        printf("arrayDinamico[%d]: %s\n", i, arrayDinamico[i]);
    }
    
    liberarArrayDinamico(arrayDinamico, numStrings);
    free(longitudes);
    
    return 0;
}