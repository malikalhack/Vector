#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define UNKNOWN_TYPE (255)
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

static size_t calc_full_data_size(data_type_t *data_type, uint8_t *data_size) {
    size_t result = calc_elem_size(data_type);
    if (result != UNKNOWN_TYPE) {
        result *= *data_size;
    }
    else result = 0;

    return result;
}

static void fill_data(
    Vector * const self,
    void * input_data,
    uint8_t *data_size
) {
    uint8_t * input_data_ = (uint8_t*)input_data;
    uint8_t * vector_data_ = (uint8_t*)self->data;
    size_t full_data_size = calc_full_data_size(&(self->type), data_size);
    for (size_t i = 0; i < full_data_size; i++) {
        *(vector_data_ + i) = *(input_data_ + i);
    }
}

static void clear_data(Vector * const self) {
    uint8_t * vector_data_ = (uint8_t*)self->data;
    size_t full_data_size = calc_full_data_size(&(self->type), &(self->max_size));
    for (size_t i = 0; i < full_data_size; i++) {
        *(vector_data_ + i) = 0;
    }
    self->curr_size = 0;
}

void Vector_ctor(Vector * const self, data_type_t data_type, uint8_t data_size, void * data) {
    self->type = data_type < TYPE_LIMIT ? data_type : UNKNOWN_TYPE;
    size_t full_data_size = calc_full_data_size(&data_type, &data_size);
    self->data = full_data_size ? self->data = malloc(full_data_size) : NULL;
    if (!self->data) {
        warning_print("Failed to allocate space for the vector");
        self->curr_size = 0;
        self->max_size = 0;
    }
    else {
        self->max_size = data_size;
        if (data) {
            fill_data(self, data, &data_size);
            self->curr_size = data_size;
        }
        else {
            clear_data(self);
        }
    }
}

void Vector_dctor(Vector * const self) {
    free(self->data);
    self->data = NULL;
    self->max_size = 0;
    self->curr_size = 0;
    self->type = UNKNOWN_TYPE;
}

void resize(Vector * const self, uint8_t new_size) {
    size_t full_data_size = calc_full_data_size(&(self->type), &new_size);
    if (full_data_size) {
        self->data = realloc(self->data, full_data_size);
        if (!self->data) {
            warning_print("Failed to allocate space for the vector");
            self->curr_size = 0;
            self->max_size = 0;
        }
        else {
            self->max_size = new_size;
        }
    }
    else warning_print("Failed to allocate new space for the vector");
    
}

void clear(Vector * const self) {
    clear_data(self);
}

size_t size(Vector * const self) {
    return self->curr_size;
}

size_t capacity(Vector * const self) {
    return self->max_size;
}
