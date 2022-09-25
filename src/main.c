/**
 * @file    main.c
 * @version 1.0.0
 * @authors Anton Chernov
 * @date    24/09/2022
 * @date    25/09/2022
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
                    printf("V[%2u] = %u\n", i, *(data + i));
                }
                break;
            }
            case S8: {
                int8_t * data = (int8_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%2u] = %d\n", i, *(data + i));
                }
                break;
            }
            case U16: {
                uint16_t * data = (uint16_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%2u] = %u\n", i, *(data + i));
                }
                break;
            }
            case S16: {
                int16_t * data = (int16_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%2u] = %d\n", i, *(data + i));
                }
                break;
            }
            case U32: {
                uint32_t * data = (uint32_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%2u] = %u\n", i, *(data + i));
                }
                break;
            }
            case S32: {
                int32_t * data = (int32_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%2u] = %d\n", i, *(data + i));
                }
                break; 
            }
            case F32: {
                float * data = (float*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%2u] = %f\n", i, *(data + i));
                }
                break;
            }
            case U64: {
                uint64_t * data = (uint64_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%2u] = %llu\n", i, *(data + i));
                }
                break;
            }
            case S64: {
                int64_t * data = (int64_t*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%2u] = %lld\n", i, *(data + i));
                }
                break;
            }
            case F64: {
                double * data = (double*)(self->data);
                for (uint8_t i = 0; i < size(self); i++) {
                    printf("V[%2d] = %f\n", i, *(data + i));
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
    data_value_t el;

    printf("Create a vector\n");
    Vector_ctor(&vector, F32, sizeof(v_data)/sizeof(v_data[0]), (void*)v_data);
    printf("The vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Reserve new capacity for the vector\n");
    reserve(&vector, 12);
    printf("The vector size: %3u, new vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Resize the vector\n");
    resize(&vector, 12);
    printf("New vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Resize the vector again\n");
    resize(&vector, 10);
    printf("New vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Push back a value into the vector\n");
    el.f32 = 98.7654f;
    push_back(&vector, el);
    printf("New vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Resize the vector one more time\n");
    resize(&vector, 14);
    printf("New vector size: %3u, new vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Push back a value into the vector\n");
    el.f32 = 65.4321f;
    push_back(&vector, el);
    printf("New vector size: %3u, new vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Get value from the vector\n");
    el = get_at(&vector, 10);
    printf("Value is: %f\n", el.f32);
    printf("The vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Set value from the vector\n");
    el.f32 = 123.456f;
    set_at(&vector, 11, el);
    printf("The vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Pop back value from the vector\n");
    el = pop_back(&vector);
    printf("Value is: %f\n", el.f32);
    printf("New vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Clear the vector\n");
    clear(&vector);
    printf("New vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Insert one element into the vector\n");
    el.f32 = 1.23456f;
    insert(&vector, 0, el);
    printf("New vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Insert another element into the vector\n");
    el.f32 = 2.222222f;
    insert(&vector, 0, el);
    printf("New vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Insert one more element into the vector\n");
    el.f32 = 3.33333f;
    insert(&vector, 0, el);
    printf("New vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Insert one more element into the vector\n");
    el.f32 = 4.44444f;
    insert(&vector, 1, el);
    printf("New vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Insert group of elements into the vector\n");
    el.f32 = 7.89123f;
    insert_group(&vector, 0, 5, el);
    printf("New vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Insert array of elements into the vector\n");
    insert_array(&vector, 3, (void*)v_data, 5);
    printf("New vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Erase one elements from the vector\n");
    erase(&vector, 0);
    printf("New vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Erase one more elements from the vector\n");
    erase(&vector, 13);
    printf("New vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    printf("Erase group of elements from the vector\n");
    erase_group(&vector, 3, 7);
    printf("New vector size: %3u, the vector capacity: %3u\n", size(&vector), capacity(&vector));
    vector_print(&vector);

    Vector_dctor(&vector);
    getchar();
    return 0;
}
