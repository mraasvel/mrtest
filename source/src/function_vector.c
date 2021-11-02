#include "function_vector.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

_MR_FunctionVectorType* _MR_FunctionVectorConstructor(size_t initial_capacity) {

	assert(initial_capacity > 0);

	_MR_FunctionVectorType* v = malloc(1 * sizeof(_MR_FunctionVectorType));
	if (v == NULL) {
		return NULL;
	}

	v->capacity = initial_capacity;
	v->size = 0;
	v->table = malloc(initial_capacity * sizeof(_MR_FunctionType));
	if (v->table == NULL) {
		free(v);
		return NULL;
	}
	return v;
}

void _MR_FunctionVectorDestructor(_MR_FunctionVectorType* v) {
	_MR_FunctionVectorIteratorType it = _MR_FunctionVectorGetIterator(v);
	while (it.begin != it.end) {
		free(it.begin->id);
		++it.begin;
	}
	free(v->table);
	free(v);
}

/*
Resize the table if there's no more room for new elements
*/
static int _MR_FunctionVectorEnsureCapacity(_MR_FunctionVectorType* v) {
	if (v->size == v->capacity) {
		_MR_FunctionType* new_table = malloc(v->capacity * 2 * sizeof(_MR_FunctionType));
		if (new_table == NULL) {
			return -1;
		}
		memcpy(new_table, v->table, v->size);
		v->capacity *= 2;
		free(v->table);
		v->table = new_table;
	}
	return 0;
}

/*
Return: -1 on malloc failure, 0 on success
*/
int _MR_FunctionVectorPushback(_MR_FunctionVectorType* v, _MR_FunctionType x) {
	if (_MR_FunctionVectorEnsureCapacity(v) == -1) {
		return -1;
	}
	assert(v->size < v->capacity);
	v->table[v->size++] = x;
	return 0;
}

/*
WARNING: DO NOT dereference the it.end pointer.

-- USAGE --
	it = _MR_FunctionVectorGetIterator(v);
	while (it.begin != it.end) {
		++it.begin;
	}
*/
_MR_FunctionVectorIteratorType _MR_FunctionVectorGetIterator(_MR_FunctionVectorType* v) {
	return (_MR_FunctionVectorIteratorType) {
		.begin = v->table,
		.end = v->table + v->size
	};
}