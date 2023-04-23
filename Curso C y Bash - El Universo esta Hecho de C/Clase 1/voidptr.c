#include <stdio.h>

typedef struct Vagon {
    int num_vagon;
    int cap_pasajeros;
    struct Vagon* siguiente_vagon;
} Vagon;

void print_int(void *data) {
    int *int_data = (int *)data;
    printf("Integer: %d\n", *int_data);
}

void print_float(void *data) {
    float *float_data = (float *)data;
    printf("Float: %f\n", *float_data);
}

void print_char(void *data) {
    char *char_data = (char *)data;
    printf("Character: %c\n", *char_data);
}

void print_vagon(void *data) {
    Vagon *vagon_data = (Vagon *)data;
    printf("Vagon: num_vagon = %d, cap_pasajeros = %d\n", vagon_data->num_vagon, vagon_data->cap_pasajeros);
}

int main() {
    int int_val = 42;
    float float_val = 3.14f;
    char char_val = 'A';
    Vagon vagon1 = {1, 50, NULL};
    
    void *void_int = (void *)&int_val;
    void *void_float = (void *)&float_val;
    void *void_char = (void *)&char_val;
    void *void_vagon = (void *)&vagon1;
    
    print_int(void_int);
    print_float(void_float);
    print_char(void_char);
    print_vagon(void_vagon);
    
    return 0;
}