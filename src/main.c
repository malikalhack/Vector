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

static void vector_print(Vector * const self) {
    if (size(self)) {
        switch (self->type) {
            case U8: {
                uint8_t * data = (uint8_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%u] = %u\n", i, *(data + i));
                }
                break;
            }
            case S8: {
                int8_t * data = (int8_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%u] = %d\n", i, *(data + i));
                }
                break;
            }
            case U16: {
                uint16_t * data = (uint16_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%u] = %u\n", i, *(data + i));
                }
                break;
            }
            case S16: {
                int16_t * data = (int16_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%u] = %d\n", i, *(data + i));
                }
                break;
            }
            case U32: {
                uint32_t * data = (uint32_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%u] = %u\n", i, *(data + i));
                }
                break;
            }
            case S32: {
                int32_t * data = (int32_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%u] = %d\n", i, *(data + i));
                }
                break; 
            }
            case F32: {
                float * data = (float*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%u] = %f\n", i, *(data + i));
                }
                break;
            }
            case U64: {
                uint64_t * data = (uint64_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%u] = %llu\n", i, *(data + i));
                }
                break;
            }
            case S64: {
                int64_t * data = (int64_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%u] = %lld\n", i, *(data + i));
                }
                break;
            }
            case F64: {
                double * data = (double*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%d] = %f\n", i, *(data + i));
                }
                break; 
            }
        default:
            printf("UNKNOWN TYPE\n");
            break;
        }
        
    } else printf("Vector is empty\n");
    printf("\r\n");
}

int main (void) {
    Vector vector;
    float v_data[] = { 1.0f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 10.5f };

    printf("Create vector\n");
    Vector_ctor(&vector, F32, sizeof(v_data)/sizeof(v_data[0]), (void*)v_data);
    printf("Vector size: %3u, vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Reserve new capacity for vector\n");
    reserve(&vector, 12);
    printf("New vector size: %3u, new vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Resize vector\n");
    resize(&vector, 16);
    printf("New vector size: %3u, new vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Resize vector again\n");
    resize(&vector, 8);
    printf("New vector size: %3u, new vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Clear vector\n");
    clear(&vector);
    printf("New vector size: %3u, new vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    Vector_dctor(&vector);
    getchar();
    return 0;
}
