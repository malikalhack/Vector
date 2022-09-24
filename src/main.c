/**
 * @file    main.c
 * @version 1.0.0
 * @authors Anton Chernov
 * @date    24/09/2022
 */

#include "vector.h"
#include <stdio.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define DISCARD_RETURN(f)   ((void)f)

static void u8_vector_print(Vector * const self) {
    if (size(self)) {
        uint8_t * data = (uint8_t*)(self->data);
        for (uint8_t i = 0; i < size(self); i++) {
            printf("V[%d] = %d\n", i, *(data + i));
        }
    } else printf("Vector is empty\n");
}

int main (void) {
    Vector vector;
    uint8_t v_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Vector_ctor(&vector, U8, sizeof(v_data), (void*)v_data);
    printf("Vector size: %d,\tvector capacity: %d\n", size(&vector), capacity(&vector));

    resize(&vector, 12);
    printf("New vector size: %d,\tnew vector capacity: %d\n", size(&vector), capacity(&vector));

    u8_vector_print(&vector);

    Vector_dctor(&vector);
    getchar();
    return 0;
}
