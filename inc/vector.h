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

typedef union {
    uint8_t  u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    int8_t   s8;
    int16_t  s16;
    int32_t  s32;
    int64_t  s64;
    float    f32;
    double   f64;
} data_value_t;

typedef void* data_t;

typedef struct {
    data_t      data;
    size_t      max_size;
    size_t      curr_size;
    data_type_t type;
} Vector;

void Vector_ctor(Vector * const, data_type_t, size_t, void*);
void Vector_dctor(Vector * const);
void resize(Vector * const, size_t);
void reserve(Vector * const, size_t);
void clear(Vector * const);
void push_back(Vector * const, data_value_t);
void push_front(Vector * const, data_value_t);
size_t size(Vector * const);
size_t capacity(Vector * const);
data_value_t pop_back(Vector * const);
data_value_t pop_front(Vector * const);

#endif /* !VECTOR_H */
