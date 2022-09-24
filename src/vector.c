#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

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

static size_t calc_full_data_size(data_type_t *data_type, size_t *data_size) {
    size_t result = calc_elem_size(data_type);
    if (result != UNKNOWN_TYPE) {
        result *= *data_size;
    }
    else result = 0;

    return result;
}

static void fill_data(
    Vector * const self,
    size_t start_pos,
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

static void clear_data(Vector * const self) {
    uint8_t * vector_data_ = (uint8_t*)self->data;
    size_t full_data_size = calc_full_data_size(&(self->type), &(self->max_size));
    for (size_t i = 0; i < full_data_size; i++) {
        *(vector_data_ + i) = 0;
    }
    self->curr_size = 0;
}

void Vector_ctor(Vector * const self, data_type_t data_type, size_t data_size, void * data) {
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
            fill_data(self, 0, data);
            self->curr_size = data_size;
        }
        else {
            fill_data(self, 0, NULL);
            self->curr_size = 0;
        }
    }
}

void Vector_dctor(Vector * const self) {
    assert(self->data);
    free(self->data);
    self->data = NULL;
    self->max_size = 0;
    self->curr_size = 0;
    self->type = UNKNOWN_TYPE;
}

void resize(Vector * const self, size_t new_size) {
    assert(self->data);
    size_t pos = self->curr_size < new_size ? self->curr_size : new_size;
    pos *= calc_elem_size(&self->type);
    fill_data(self, pos, NULL);
    self->curr_size = new_size;
}

void reserve(Vector * const self, size_t new_size) {
    assert(self->data);
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
            size_t pos = calc_elem_size(&self->type) * self->curr_size;
            fill_data(self, pos, NULL);
            if (new_size < self->curr_size) self->curr_size = new_size;
        }
    }
    else warning_print("Failed to allocate new space for the vector");
    
}

void clear(Vector * const self) {
    assert(self->data);
    fill_data(self, 0, NULL);
    self->curr_size = 0;
}

void push_back(Vector * const self, data_value_t value) {
    assert(self->data);

}

void push_front(Vector * const self, data_value_t value) {
    assert(self->data);
}

size_t size(Vector * const self) {
    assert(self->data);
    return self->curr_size;
}

size_t capacity(Vector * const self) {
    assert(self->data);
    return self->max_size;
}

data_value_t pop_back(Vector * const self) {
    assert(self->data);
    data_value_t result = {.u8 = 0};
    return result;
}

data_value_t pop_front(Vector * const self) {
    assert(self->data);
    data_value_t result = { .u8 = 0 };
    return result;
}
