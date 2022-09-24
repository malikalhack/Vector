#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>

typedef enum{
    U8 = 0,
    S8,
    U16,
    S16,
    U32,
    S32,
    U64,
    S64,
    F32,
    F64,
    TYPE_LIMIT
} data_type_t;

typedef void* data_t;

typedef struct {
    data_t      data;
    size_t      max_size;
    size_t      curr_size;
    data_type_t type;
} Vector;

void Vector_ctor(Vector * const, data_type_t, uint8_t, void*);
void Vector_dctor(Vector * const);

#endif /* !VECTOR_H */
