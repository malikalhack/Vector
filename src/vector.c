/**
 * @file    vector.c
 * @version 1.0.0
 * @authors Anton Chernov
 * @date    24/09/2022
 * @date    25/09/2022
 */

/****************************** Included files ********************************/
#include "vector.h"
#include "log.h"
#include <stdlib.h>
#include <malloc.h>
/******************************** Definition **********************************/
#define UNKNOWN_TYPE  (255)
#define SIZE_uint32_t (4)
#define SIZE_uint64_t (8)
/****************************** Private  functions ****************************/
static uint8_t calc_elem_size(data_type_t const * const data_type) {
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
            self->curr_size = 0;
            self->max_size = 0;
            error_print("Failed to allocate space for the vector");
        }
        else {
            self->max_size = *new_size;
        }
    }
    else warning_print("Incorrect new size for the vector");
}
/*----------------------------------------------------------------------------*/
static data_value_t get_element(
    Vector const * const self,
    size_t const * const pos
) {
    size_t index = *pos * calc_elem_size(&self->type);
    uint8_t * start_point = (uint8_t*)self->data + index;
    data_value_t result = {.u64 = 0};
    switch (self->type) {
        case U8:
        case S8:
            result.u8 = *start_point;
            break;
        case U16:
        case S16:
            result.u16 = (*start_point) | (*(start_point + 1) << 8);
            break;
        case U32:
        case S32:
        case F32: {
            uint32_t temp = 0;
            uint8_t  index = SIZE_uint32_t;
            while (index--) {
                temp <<= 8;
                temp |= (start_point)[index];
            }
            result.u32 = temp;
            break;
        }
        case U64:
        case S64:
        case F64: {
            uint64_t temp = 0;
            uint8_t  index = SIZE_uint64_t;
            while (index--) {
                temp <<= 8;
                temp |= (start_point)[index];
            }
            result.u64 = temp;
            break;
        }
        default:
            warning_print("Incorrect type of the vector");
    }
    return result;
}
/*----------------------------------------------------------------------------*/
static void set_element(
    Vector * const self,
    size_t const * const pos,
    data_value_t const * const value
) {
    size_t index = *pos * calc_elem_size(&self->type);
    uint8_t * start_point = (uint8_t*)self->data + index;
    switch (self->type) {
        case U8:
        case S8:
            *start_point = value->u8;
            break;
        case U16:
        case S16:
            *start_point++ = (uint8_t)value->u16;
            *start_point++ = (uint8_t)(value->u16 >> 8);
            break;
        case U32:
        case S32:
        case F32: {
            uint32_t temp = value->u32;
            for (uint8_t i = 0; i < SIZE_uint32_t; i++) {
                *start_point++ = temp & 0xFF;
                temp >>= 8;
            }
            break;
        }
        case U64:
        case S64:
        case F64: {
            uint64_t temp = value->u64;
            for (uint8_t i = 0; i < SIZE_uint64_t; i++) {
                *start_point++ = temp & 0xFF;
                temp >>= 8;
            }
            break;
        }
        default:
            warning_print("Incorrect type of the vector");
    }
}
/*----------------------------------------------------------------------------*/
static void make_room(
    Vector * const self,
    size_t const * const pos,
    size_t const * const num
) {
    if (self->curr_size) {
        data_value_t temp;
        size_t dst_index = self->curr_size + *num - 1u;
        while (*pos < dst_index) {
            size_t src_index = dst_index - *num;
            temp = get_element(self, &src_index);
            set_element(self, &dst_index, &temp);
            dst_index--;
        }
    }
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
    if (new_size < self->curr_size) {
        self->curr_size = new_size;
    }
    else if (new_size > self->curr_size) {
        size_t pos = calc_elem_size(&self->type) * self->curr_size;
        fill_data(self, pos, NULL);
    }
}
/*----------------------------------------------------------------------------*/
void resize(Vector * const self, const size_t new_size) {
    assert(self->data);
    size_t pos = self->curr_size < new_size ? self->curr_size : new_size;
    pos *= calc_elem_size(&self->type);
    if (new_size > self->max_size) {
        reallocate(self, &new_size);
    }
    fill_data(self, pos, NULL);
    self->curr_size = new_size;
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
    if (!(self->curr_size < self->max_size)) {
        size_t new_size = self->max_size + 1;
        reallocate(self, &new_size);
    }
    set_element(self, &self->curr_size, &value);
    self->curr_size++;
}
/*----------------------------------------------------------------------------*/
void set_at(Vector * const self, const size_t pos, data_value_t value) {
    assert(self->data);
    if (self->curr_size) {
        if (!(pos + 1 > self->curr_size)) {
            set_element(self, &pos, &value);
        }
        else warning_print("The specified position is out of range");
    }
    else warning_print("The vector is empty");
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
    data_value_t result = {.u64 = 0};
    if (self->curr_size) {
        --self->curr_size;
        result = get_element(self, &self->curr_size);
    }
    else {
        warning_print("The vector is empty");
    }
    return result;
}
/*----------------------------------------------------------------------------*/
data_value_t get_at(Vector const * const self, const size_t pos) {
    assert(self->data);
    data_value_t result = { .u64 = 0 };
    if (self->curr_size) {
        if (!(pos + 1 > self->curr_size)) {
            result = get_element(self, &pos);
        }
        else warning_print("The specified position is out of range");
    }
    else warning_print("The vector is empty");
    return result;
}
/*----------------------------------------------------------------------------*/
void insert(Vector * const self, const size_t pos, data_value_t value) {
    assert(self->data);
    const size_t room = 1u;
    if (!(self->curr_size < self->max_size)) {
        size_t new_size = self->max_size + room;
        reallocate(self, &new_size);
    }
    if (!(pos > self->curr_size)) {
        make_room(self, &pos, &room);
        set_element(self, &pos, &value);
        self->curr_size++;
    }
    else warning_print("The specified position is out of range");
}
/*----------------------------------------------------------------------------*/
void insert_array(
    Vector * const self,
    const size_t pos,
    void * new_data,
    const size_t data_size
) {
    assert(self->data);
    if (new_data && data_size) {
        if (!(self->curr_size + data_size <= self->max_size)) {
            size_t new_size = 
                self->max_size + (self->curr_size + data_size - self->max_size);
            reallocate(self, &new_size);
        }
        if (!(pos > self->curr_size)) {
            uint8_t * vector_data_ = (uint8_t*)self->data;
            uint8_t * input_data_ = (uint8_t*)new_data;
            const size_t start_pos = pos * calc_elem_size(&self->type);
            const size_t finish_pos =
                start_pos + calc_full_data_size(&(self->type), &data_size);

            make_room(self, &pos, &data_size);
            for (size_t i = start_pos, j = 0; i < finish_pos; i++, j++) {
                *(vector_data_ + i) = *(input_data_ + j);
            }
            self->curr_size += data_size;
        }
        else warning_print("The specified position is out of range");
    }
    else warning_print("Array is empty");
}
/*----------------------------------------------------------------------------*/
void insert_group(
    Vector * const self,
    const size_t start_pos,
    const size_t finish_pos,
    data_value_t value
) {
    assert(self->data);
    if (finish_pos < start_pos) {
        warning_print("The start and end positions are incorrect");
    }
    else {
        const size_t room = finish_pos - start_pos + 1u;
        if (!(self->curr_size + room <= self->max_size)) {
            size_t new_size =
                self->max_size + (self->curr_size + room - self->max_size);
            reallocate(self, &new_size);
        }
        if (!(start_pos > self->curr_size)) {
            make_room(self, &start_pos, &room);
            for (size_t i = start_pos; i <= finish_pos; i++) {
                set_element(self, &i, &value);
            }
            self->curr_size += room;
        }
        else warning_print("The specified position is out of range");
    }
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
