#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

void vector_init(Vector *v, uint32_t capacity,
                 size_t data_size,
                 void (*free_element)(void *)) {
    v->capacity = capacity;
    v->size = 0;
    v->data_size = data_size;
    v->data = calloc(v->capacity, v->data_size);
    v->free_element = free_element;
}

void vector_pushback(Vector *v, void *datum) {
    if (v->size == v->capacity - 2) {
        v->capacity *= 2;
        void *new_arr = calloc(v->capacity, v->data_size);
        memcpy(new_arr, v->data, v->size * v->data_size);
        free(v->data);
        v->data = new_arr;
    }
    void *data_start = (uint8_t *)v->data + v->size * v->data_size;
    memcpy(data_start, datum, v->data_size);
    v->size++;
}

void vector_popback(Vector *v) {
    if (v->size <= 0) {
        fprintf(stderr, "Error: vector popback() on empty vector");
        exit(1);
    }

    v->size--;
    //this is slow, but i like the behavior
    //vector_set(v, 0, v->size);
}

void vector_set(Vector *v, void *data, size_t index) {
    if (index >= v->capacity) {
        fprintf(stderr, "Error: vector set() index greater than vector size");
        exit(1);
    }
    uint8_t *data_start = (uint8_t *)v->data + index * v->data_size;
    memcpy(data_start, data, v->data_size);
}

void *vector_get(Vector *v, size_t index) {
    if (index >= v->capacity) {
        fprintf(stderr, "Error: vector get() index greater than vector size\n");
        exit(1);
    }
    return (uint8_t *)(v->data) + v->data_size * index;
}

void vector_free(Vector *v) {
    if (v->free_element != NULL) {
        for (size_t i = 0; i < v->capacity; i++) {
            void *datum = vector_get(v, i);
            (v->free_element)(datum);
        }
    }

    free(v->data);
}
