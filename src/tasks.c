#include "functional.h"
#include "tasks.h"
#include "tests.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Frees the memory of the number string
void number_destructor(void *num) {
	free(((number_t *)num)->string);
}

// Frees the memory malloc'd by a list
void list_destructor(void *list) {
	free(((array_t *)list)->data);
}

/*
	Moves len - 1 characters to the right then copies the new character to
	the first position
*/
void reverse_list(void *acc, void *source) {
	array_t new = *(array_t *)acc;
	memmove(new.data + new.elem_size, new.data, (new.len - 1) * new.elem_size);
	memcpy(new.data, source, new.elem_size);
}

// Malloc's one number_t variable
void create_number(void *number, void **elems) {
	number_t *num = (number_t *)number;
	num->integer_part = *(int *)elems[0];
	num->fractional_part = *(int *)elems[1];
	num->string = malloc(100);
	sprintf(num->string, "%d.%d", num->integer_part, num->fractional_part);
}

// Checks if the student is passing
boolean is_passing(void *student) {
	return ((student_t *)student)->grade >= 5.0;
}

// Extracts the name of the student
void extract_name(void *dest, void *src) {
	*(char **)dest = malloc(100);
	strcpy(*(char **)dest, ((student_t *)src)->name);
}

// Adds number to accumulator
void add_num(void *acc, void *num) {
	*(int *)acc += *(int *)num;
}

// Checks if sum is greater than the respective integer
void check_sum(void *new, void **elems) {
	int sum = 0;
	reduce(add_num, &sum, *(array_t *)elems[0]);
	*(char *)new = (sum >= *(int *)elems[1]);
}

// Sets the elements of the list as 1 0 1 0 1 ...
void set_index(void *index) {
	int *num = (int *)index;
	if (*num == 0)
		*num = (*(num - 1) + 1) % 2;
}

/*
	Extracts only the strings that have the equivalent index in the
	previours array equal to 1
*/
void extract_strings(void *acc, void **elems) {
	if (*(int *)elems[0]) {
		array_t *list = (array_t *)acc;
		char **data = list->data + (list->len++) * list->elem_size;
		*data = malloc(100);
		strcpy(*data, *(char **)elems[1]);
	}
	free(*(char **)elems[1]);
}

// Initialises the matrix with the first column as 1;2;3;4;5...
void init_matrix(void *elem) {
	array_t *list = (array_t *)elem;
	if (list->len == 0) {
		list->len = (list - 1)->len;
		list->elem_size = (list - 1)->elem_size;
		list->data = calloc(list->len, list->elem_size);
		*(int *)list->data = *(int *)(list - 1)->data + 1;
	} else {
		*(int *)list->data = 1;
	}
}

// Sets the curent number as the previous + 1
void set_num(void *num) {
	if (*(int *)num == 0)
		*(int *)num = *(int *)((int *)num - 1) + 1;
}

// Completes the matrix with the desired values
void set_matrix(void *elem) {
	array_t *list = (array_t *)elem;
	for_each(set_num, *list);
}

// Reverses the string
array_t reverse(array_t list) {
	array_t new_list = {calloc(list.len, list.elem_size),
						list.elem_size,
						list.len,
						NULL};
	reduce(reverse_list, &new_list, list);
	return new_list;
}

// Creates the array of number_t's
array_t create_number_array(array_t integer_part, array_t fractional_part) {
	return map_multiple(create_number, sizeof(number_t),
						number_destructor, 2, integer_part,
						fractional_part);
}

// Extracts the name of the passing students
array_t get_passing_students_names(array_t list) {
	return map(extract_name, 100, NULL, filter(is_passing, list));
}

// Checks if the list sum is greater of equal to the equivalent integer
array_t check_bigger_sum(array_t list_list, array_t int_list) {
	return map_multiple(check_sum, sizeof(boolean), NULL, 2,
						list_list, int_list);
}

// Extractds the strings on even indexes
array_t get_even_indexed_strings(array_t list) {
	array_t index_list = {calloc(list.len, sizeof(int)),
						  sizeof(int),
						  list.len,
						  NULL};

	*(int *)index_list.data = 1;
	for_each(set_index, index_list);

	int len = ((list.len - 1) / 2) + 1;
	array_t new_list = {calloc(len, list.elem_size),
						list.elem_size,
						0,
						NULL};

	reduce_multiple(extract_strings, &new_list, 2, index_list, list);

	free(index_list.data);
	free(list.data);

	return new_list;
}

// Generates the desired square matrix
array_t generate_square_matrix(int n) {
	array_t matrix = {calloc(n, sizeof(array_t)),
					  sizeof(array_t),
					  n,
					  list_destructor};

	array_t *first_list = (array_t *)matrix.data;
	first_list->len = n;
	first_list->elem_size = sizeof(int);
	first_list->data = calloc(n, first_list->elem_size);

	for_each(init_matrix, matrix);
	for_each(set_matrix, matrix);

	return matrix;
}
