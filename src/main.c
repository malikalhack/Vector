/**
 * @file    main.c
 * @version 1.0.0
 * @authors Anton Chernov
 * @date    24/09/2022
 */

#include "vector.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define DISCARD_RETURN(f)   ((void)f)

int main (void) {
    Vector vector;
    uint8_t v_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Vector_ctor(&vector, U8, sizeof(v_data), (void*)v_data);

    Vector_dctor(&vector);
    return 0;
}
