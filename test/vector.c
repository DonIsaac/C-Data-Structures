#include "../src/lists/vector.h"
#include "minunit.h"
#include <stdio.h>
#include <string.h>

int tests_failed = 0;
int tests_run = 0;
int num_assertions = 0;


mu_test(test_vector_empty) {
	Vector v;
	vector_init(&v, 16, 4, NULL);

	mu_assert("Capacity not 16.", v.capacity == 16);
	mu_assert("Data size not 4.", v.data_size == 4);
	mu_assert("Free element is not null.", v.free_element == NULL);

	vector_free(&v);

	return 0;
}



mu_test(test_vector_grow) {
	Vector v;
	vector_init(&v, 4, 4, NULL);
	for (size_t i = 0; i < 100; i++) {
		vector_pushback(&v, &i);
	}

	char buffer[100];
	for(size_t i = 0; i < v.size; i++) {
		sprintf(buffer, "Expected: %ld, Received: %ld at index: %ld\n", i,i,i);
		int *element = vector_get(&v, i);
		mu_assert(buffer, *element == (int)i);

	}
	
	vector_free(&v);

	return 0;

}


mu_test(test_vector_grow_and_delete) {
	Vector v;
	vector_init(&v, 4, 4, NULL);
	for (size_t i = 0; i < 100; i++) {
		vector_pushback(&v, &i);
	}

	for (int i =0; i<100; i++) {
		vector_popback(&v);
		mu_assert("Push back resulted in bad size", v.size == (uint32_t)(100 - i -1));
	}
	vector_free(&v);
	return 0;

}


typedef struct _n {
	int *i;
} Node;

void free_node(void *n) {
	Node *nn = n;

	free(nn->i);
	
}

mu_test(test_vector_free_element) {
	Vector v;
	vector_init(&v, 4, sizeof(Node *), free_node);
	mu_assert("free element not passed", v.free_element != NULL);
	printf("\n");
	for (size_t i = 0; i <100; i++) {
		Node n;
		n.i = malloc(sizeof(int));
		memcpy(n.i, &i, 4);
		
		vector_pushback(&v, &n);
	}

	mu_assert("Gotten element is not right!", *(((Node *)vector_get(&v, 20))->i) == 20);
	
	vector_free(&v);

	return 0;
}



void all_tests() {
	mu_run_test(test_vector_empty);
	mu_run_test(test_vector_grow);
	mu_run_test(test_vector_grow_and_delete);
	mu_run_test(test_vector_free_element)
}


int  main() {
	all_tests();
	printf("\nTests run: %d\nTests failed: %d\nTotal assertions: %d\n\n", 
		tests_run, tests_failed, num_assertions);

	if (!tests_failed) {
		printf("All tests passed\n");
		return EXIT_SUCCESS;
	} else {
		return EXIT_FAILURE;
	}

}