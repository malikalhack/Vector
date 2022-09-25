/**
* @file    vector.h
* @version 1.0.0
* @authors Anton Chernov
* @date    24/09/2022
*/

#ifndef VECTOR_H
#define VECTOR_H
/****************************** Included files ********************************/
#include <stdint.h>
/******************************** Definition **********************************/
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
/*----------------------------------------------------------------------------*/
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
/*----------------------------------------------------------------------------*/
typedef void* data_t;
/*----------------------------------------------------------------------------*/
typedef struct {
    data_t      data;
    size_t      max_size;
    size_t      curr_size;
    data_type_t type;
} Vector;
/*************************** Function's prototypes ****************************/
void Vector_ctor(Vector * const, data_type_t, size_t, void*);
void Vector_dctor(Vector * const);
void resize(Vector * const, const size_t);
void reserve(Vector * const, const size_t);
void clear(Vector * const);
void push_back(Vector * const, data_value_t);
void set_at(Vector * const, const size_t, data_value_t);
void insert(Vector * const, const size_t, data_value_t);
void insert_array(Vector * const, const size_t, void*, const size_t);
void insert_group(Vector * const, const size_t, const size_t, data_value_t);
void erase(Vector * const, const size_t);
void erase_group(Vector * const, const size_t, const size_t);
size_t size(Vector const * const);
size_t capacity(Vector const * const);
data_value_t pop_back(Vector * const);
data_value_t get_at(Vector const * const, const size_t);
/******************************************************************************/
#endif /* !VECTOR_H */
