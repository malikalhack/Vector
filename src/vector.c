/**
 * @file    vector.c
 * @version 1.0.0
 * @authors Anton Chernov
 * @date    24/09/2022
 */

/****************************** Included files ********************************/
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
/******************************** Definition **********************************/
#define warning_print(fmt, ...) {\
        fprintf(\
            stdout,\
            "[WARNING] " fmt " in %s, Line %i\n",\
            __VA_ARGS__,\
            __FILE__,\
            __LINE__\
        );\
        fflush(stdout);\
    }
/*----------------------------------------------------------------------------*/
#define error_print(fmt, ...) {\
        fprintf(\
            stdout,\
            "[ERROR] " fmt " in %s, Line %i\n",\
            __VA_ARGS__,\
            __FILE__,\
            __LINE__\
        );\
        fflush(stdout);\
    }
/*----------------------------------------------------------------------------*/
#define UNKNOWN_TYPE  (255)
/****************************** Private  functions ****************************/
static uint8_t calc_elem_size(data_type_t *data_type) {
    uint8_t result;
    switch (*data_type) {
        case U8:
        case S8:
            result = 1; break;
        case U16:
        case S16:
            result = 2; break;
        case U32:
        case S32:
        case F32:
            result = 4; break;
        case U64:
        case S64:
        case F64:
            result = 8; break;
        default:
            result = UNKNOWN_TYPE;
    }
    return result;
}
/*----------------------------------------------------------------------------*/
static size_t calc_full_data_size(
    data_type_t *data_type,
    size_t const * const data_size
) {
    size_t result = calc_elem_size(data_type);
    if (result != UNKNOWN_TYPE) {
        result *= *data_size;
    }
    else result = 0;

    return result;
}
/*----------------------------------------------------------------------------*/
static void fill_data(
    Vector * const self,
    const size_t start_pos,
    void * input_data
) {
    uint8_t * vector_data_ = (uint8_t*)self->data;
    size_t full_data_size = calc_full_data_size(&(self->type), &(self->max_size));
    if (input_data) {
        uint8_t * input_data_ = (uint8_t*)input_data;
        for (size_t i = start_pos; i < full_data_size; i++) {
            *(vector_data_ + i) = *(input_data_ + i);
        }
    }
    else {
        for (size_t i = start_pos; i < full_data_size; i++) {
            *(vector_data_ + i) = 0;
        }
    }
}
/*----------------------------------------------------------------------------*/
static void reallocate(Vector * const self, size_t const * const new_size) {
    size_t full_data_size = calc_full_data_size(&(self->type), new_size);
    if (full_data_size) {
        self->data = realloc(self->data, full_data_size);
        if (!self->data) {
            warning_print("Failed to allocate space for the vector");
            self->curr_size = 0;
            self->max_size = 0;
        }
        else {
            self->max_size = *new_size;
            size_t pos = calc_elem_size(&self->type) * self->curr_size;
            fill_data(self, pos, NULL);
            if (*new_size < self->curr_size) self->curr_size = *new_size;
        }
    }
    else warning_print("Incorrect new size for the vector");
}
/*----------------------------------------------------------------------------*/
static data_value_t get_element(Vector * const self, const size_t pos) {

}
/*----------------------------------------------------------------------------*/
static void set_element(
    Vector * const self,
    const size_t pos,
    const data_value_t value
) {

}
/********************* Application Programming Interface **********************/
void Vector_ctor(
    Vector * const self,
    data_type_t data_type,
    size_t data_size,
    void * data
) {
    self->type = data_type < TYPE_LIMIT ? data_type : UNKNOWN_TYPE;
    size_t full_data_size = calc_full_data_size(&data_type, &data_size);
    self->data = full_data_size ? self->data = malloc(full_data_size) : NULL;
    if (!self->data) {
        self->curr_size = 0;
        self->max_size = 0;
        error_print("Failed to allocate space for the vector");
        assert(0);
    }
    else {
        self->max_size = data_size;
        if (data) {
            fill_data(self, 0, data);
            self->curr_size = data_size;
        }
        else {
            fill_data(self, 0, NULL);
            self->curr_size = 0;
        }
    }
}
/*----------------------------------------------------------------------------*/
void Vector_dctor(Vector * const self) {
    assert(self->data);
    free(self->data);
    self->data = NULL;
    self->max_size = 0;
    self->curr_size = 0;
    self->type = UNKNOWN_TYPE;
}
/*----------------------------------------------------------------------------*/
void reserve(Vector * const self, const size_t new_size) {
    assert(self->data);
    reallocate(self, &new_size);
}
/*----------------------------------------------------------------------------*/
void resize(Vector * const self, const size_t new_size) {
    assert(self->data);
    size_t pos = self->curr_size < new_size ? self->curr_size : new_size;
    pos *= calc_elem_size(&self->type);
    if (new_size > self->max_size) {
        reallocate(self, &new_size);
        self->curr_size = new_size;
    }
    else {
        fill_data(self, pos, NULL);
        self->curr_size = new_size;
    }
}
/*----------------------------------------------------------------------------*/
void clear(Vector * const self) {
    assert(self->data);
    fill_data(self, 0, NULL);
    self->curr_size = 0;
}
/*----------------------------------------------------------------------------*/
void push_back(Vector * const self, data_value_t value) {
    assert(self->data);
    if (self->curr_size < self->max_size) {
        
    }
    else {

    }
}
/*----------------------------------------------------------------------------*/
void set_at(Vector * const self, const size_t pos, data_value_t value) {
    assert(self->data);
}
/*----------------------------------------------------------------------------*/
size_t size(Vector const * const self) {
    assert(self->data);
    return self->curr_size;
}
/*----------------------------------------------------------------------------*/
size_t capacity(Vector const * const self) {
    assert(self->data);
    return self->max_size;
}
/*----------------------------------------------------------------------------*/
data_value_t pop_back(Vector * const self) {
    assert(self->data);
    data_value_t result = {.u8 = 0};
    return result;
}
/*----------------------------------------------------------------------------*/
data_value_t get_at(Vector const * const self, const size_t pos) {
    assert(self->data);
    data_value_t result = { .u8 = 0 };
    return result;
}
/*----------------------------------------------------------------------------*/
void insert(Vector * const self, const size_t pos, data_value_t value) {
    assert(self->data);
}
/*----------------------------------------------------------------------------*/
void insert_array(
    Vector * const self,
    const size_t pos,
    void * new_data,
    const size_t data_size
) {
    assert(self->data);
}
/*----------------------------------------------------------------------------*/
void insert_group(
    Vector * const self,
    const size_t start_pos,
    const size_t finish_pos,
    data_value_t value
) {
    assert(self->data);
}
/*----------------------------------------------------------------------------*/
void erase(Vector * const self, const size_t pos) {

}
/*----------------------------------------------------------------------------*/
void erase_group(
    Vector * const self,
    const size_t start_pos,
    const size_t finish_pos
) {
    assert(self->data);
}
/******************************************************************************/
