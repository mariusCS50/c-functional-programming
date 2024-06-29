#include "functional.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void for_each(void (*func)(void *), array_t list)
{
	for (int i = 0; i < list.len; i++)
		func(list.data + i * list.elem_size);
}

array_t map(void (*func)(void *, void *),
			int new_list_elem_size,
			void (*new_list_destructor)(void *),
			array_t list)
{
	array_t new = {malloc(list.len * new_list_elem_size),
				   new_list_elem_size,
				   list.len,
				   new_list_destructor};

	for (int i = 0; i < list.len; i++)
		func(new.data + i * new.elem_size, list.data + i * list.elem_size);

	if (list.destructor) {
		for (int i = 0; i < list.len; i++)
			list.destructor(list.data + i * list.elem_size);
	}

	free(list.data);
	return new;
}

array_t filter(boolean(*func)(void *), array_t list)
{
	array_t new = {NULL,
				   list.elem_size,
				   0,
				   list.destructor};

	for (int i = 0; i < list.len; i++) {
		if (func(list.data + i * list.elem_size)) {
			new.data = realloc(new.data, (new.len + 1) * new.elem_size);
			memcpy(new.data + new.len * new.elem_size,
				   list.data + i * list.elem_size, list.elem_size);
			new.len++;
		} else if (list.destructor) {
			list.destructor(list.data + i * list.elem_size);
		}
	}

	free(list.data);

	return new;
}

void *reduce(void (*func)(void *, void *), void *acc, array_t list)
{
	for (int i = 0; i < list.len; i++)
		func(acc, list.data + i * list.elem_size);

	return acc;
}

void for_each_multiple(void (*func)(void **), int varg_c, ...) {
	array_t *lists = (array_t *)malloc(varg_c * sizeof(array_t));

	va_list arg;
	va_start(arg, varg_c);

	for (int i = 0; i < varg_c; i++)
		lists[i] = va_arg(arg, array_t);

	va_end(arg);

	int min_list_len = lists[0].len;
	for (int i = 1; i < varg_c; i++) {
		if (lists[i].len < min_list_len)
			min_list_len = lists[i].len;
	}

	void **vec = (void **)malloc(varg_c * sizeof(void *));
	for (int col = 0; col < min_list_len; col++) {
		for (int i = 0; i < varg_c; i++)
			vec[i] = lists[i].data + col * lists[i].elem_size;

		func(vec);
	}
	free(vec);

	free(lists);
}

array_t map_multiple(void (*func)(void *, void **),
					 int new_list_elem_size,
					 void (*new_list_destructor)(void *),
					 int varg_c, ...)
{
	array_t *lists = (array_t *)malloc(varg_c * sizeof(array_t));

	va_list arg;
	va_start(arg, varg_c);

	for (int i = 0; i < varg_c; i++)
		lists[i] = va_arg(arg, array_t);

	va_end(arg);

	int min_list_len = lists[0].len;
	for (int i = 1; i < varg_c; i++) {
		if (lists[i].len < min_list_len)
			min_list_len = lists[i].len;
	}

	array_t new = {malloc(min_list_len * new_list_elem_size),
				   new_list_elem_size,
				   min_list_len,
				   new_list_destructor};

	void **vec = (void **)malloc(varg_c * sizeof(void *));
	for (int col = 0; col < min_list_len; col++) {
		for (int i = 0; i < varg_c; i++)
			vec[i] = lists[i].data + col * lists[i].elem_size;

		func(new.data + col * new.elem_size, vec);
	}

	free(vec);

	for (int id = 0; id < varg_c; id++) {
		if (lists[id].destructor) {
			for (int i = 0; i < lists[id].len; i++)
				lists[id].destructor(lists[id].data + i * lists[id].elem_size);
		}
		free(lists[id].data);
	}

	free(lists);

	return new;
}

void *reduce_multiple(void(*func)(void *, void **), void *acc, int varg_c, ...)
{
	array_t *lists = (array_t *)malloc(varg_c * sizeof(array_t));

	va_list arg;
	va_start(arg, varg_c);

	for (int i = 0; i < varg_c; i++)
		lists[i] = va_arg(arg, array_t);

	va_end(arg);

	int min_list_len = lists[0].len;
	for (int i = 1; i < varg_c; i++) {
		if (lists[i].len < min_list_len)
			min_list_len = lists[i].len;
	}

	void **vec = (void **)malloc(varg_c * sizeof(void *));
	for (int col = 0; col < min_list_len; col++) {
		for (int i = 0; i < varg_c; i++)
			vec[i] = lists[i].data + col * lists[i].elem_size;

		func(acc, vec);
	}
	free(vec);

	free(lists);

	return acc;
}
