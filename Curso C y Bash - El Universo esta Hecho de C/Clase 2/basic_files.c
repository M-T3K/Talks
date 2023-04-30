#include <stdio.h>

int main() {
    FILE *archivo;
    
    // Abrir el archivo en modo de escritura (w)
    archivo = fopen("ejemplo.txt", "w");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }
    
    // Escribir texto en el archivo
    fprintf(archivo, "Hola, mundo!\n");
    fprintf(archivo, "Esta es una prueba de escritura en un archivo.\n");
    
    // Cerrar el archivo
    fclose(archivo);
    
    // Abrir el archivo en modo de lectura (r)
    archivo = fopen("ejemplo.txt", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }
    
    // Leer el contenido del archivo y mostrarlo en la salida estándar
    char linea[100];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s", linea);
    }
    // Cerrar el archivo
    fclose(archivo);
    
    return 0;
}