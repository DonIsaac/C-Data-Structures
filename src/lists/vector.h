#ifndef VECTOR_H
#define VECTOR_H
#include <inttypes.h>
#include <stdlib.h>
#include <stddef.h>
typedef struct _vector {
	void *data; //array
	uint32_t size; //running size of array
	uint32_t capacity;  //how many elements can be held
	size_t data_size; //actual size of element

	//optional function to free data associated with element
	//i.e if element in data was struct with field char *;
	//this function would be called when freeing the array
	//and would free the char field in every element
	void (*free_element)(void *);

} Vector; 



void vector_init(Vector *v, uint32_t capacity, 
	size_t data_size, 
	void (*free_element)(void *));



//Does not call free_element() on element removed from array!!!
//Can cause memory leak!!!
void vector_popback(Vector *v);


//This can be set past vector_back limited by capacity not size
void vector_set(Vector *v, void *data, size_t index);


void *vector_get(Vector *v, size_t index);



//this pushes to the back of size
void vector_pushback(Vector *v, void *datum);

//frees all elements in list with free element
//then frees all data pointed to by the data in the vector
/*
I.e if the vector holds Node * of:
typedef struct _Node {
	int *i;
} Node;

"i" will be freed. The node itself can not be.
To be precise what is freed is dependent on the passed free_element function
If it is null only vector->data will be freed.

This is because the data sent is copied
*/
void vector_free(Vector *v);





#endif