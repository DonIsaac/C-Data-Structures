/**
 * @file vector.h
 * @brief A resizeable list.
 *
 * @author Eli Lichtblau
 * @version 0.0.1
 * @date 2021-09-29
 *
 * @defgroup vector Vector
 * A resizeable vector list.
 *
 * TODO: Add some descriptions here
 */
#ifndef VECTOR_H
#define VECTOR_H

#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief A Vector list
 *
 * @ingroup vector
 */
typedef struct _vector {
    /** @brief Array where data is stored. */
    void *data;
    /** @brief The running size of the data array. */
    uint32_t size;
    /** @brief how many elementscan be held in the Vector. */
    uint32_t capacity;
    /** @brief Size of the stored data. */
    size_t data_size;

    /**
	 * @brief optional function to free data associated with element.
	 *
	 * i.e if element in data was struct with field `char *`; this function would
	 * be called when freeing the array and would free the char field in every
	 * element.
	 *
	 * @param An element of the Vector. 
	 */
    void (*free_element)(void *);

} Vector;

/**
 * @brief 
 *
 * @ingroup vector
 *
 * @param v
 * @param capacity
 * @param data_size
 * @param free_element
 *
 */
void vector_init(Vector *v, uint32_t capacity,
                 size_t data_size,
                 void (*free_element)(void *));

/**
 * @brief 
 *
 * Does not call free_element() on element removed from array!!! Can cause a
 * memory leak!
 *
 * @ingroup vector
 *
 * @param v
 */
void vector_popback(Vector *v);

/**
 * @brief Sets the stored value for a list element.
 *
 * This can be set past vector_back limited by capacity not size 
 *
 * @ingroup vector
 *
 * @param v
 * @param data
 * @param index
 */
void vector_set(Vector *v, void *data, size_t index);

/**
 * @brief Gets the data stored in a list entry.
 *
 * @ingroup vector
 *
 * @param v
 * @param index
 *
 * @return 
 */
void *vector_get(Vector *v, size_t index);

/**
 * @brief This pushes to the back of size.
 *
 * @ingroup vector
 *
 * @param v
 * @param datum
 */
void vector_pushback(Vector *v, void *datum);

/**
 * @brief Frees all memory resources associated with a Vector.
 *
 * Frees all elements in list with free element then frees all data pointed to
 * by the data in the vector.
 *
 * I.e if the vector holds `Node *` of:
 *
 * ```c
 * typedef struct _Node {
 * 	 int *i;
 * } Node;
 * ```
 *
 * then `i` will be freed. The node itself can not be.
 * To be precise what is freed is dependent on the passed `free_element` function
 * If it is null only `vector->data` will be freed.
 * 
 * This is because the data sent is copied.
 *
 * @ingroup vector
 *
 * @param v
 */
void vector_free(Vector *v);

#endif
