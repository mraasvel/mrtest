#ifndef FUNCTION_VECTOR_H
# define FUNCTION_VECTOR_H

# include <stddef.h>

typedef struct _MR_FunctionType _MR_FunctionType;
typedef struct _MR_FunctionVectorType _MR_FunctionVectorType;
typedef struct _MR_FunctionVectorIteratorType _MR_FunctionVectorIteratorType;

/*
_MR_TestFunctionPointer: Setup function for each TestCase (dynamically named)
_MR_TestCaseFunction: Main TestCase function, named by parameter given by user
*/
typedef _MR_FunctionType (*_MR_TestFunctionPointer)(void);
typedef void (*_MR_TestCaseFunction)(void);

/*
The data the vector will hold
This can also be easily converted to be stored in a hashtable later (id = key, function = value)
*/
struct _MR_FunctionType {
	char *id;
	_MR_TestCaseFunction function;
};


/*
Basic vector implementation

WARNING:
	DO NOT change the member variables of this struct
	Use the related functions
*/
struct _MR_FunctionVectorType {
	size_t size;
	size_t capacity;
	_MR_FunctionType* table;
};

/*
Basic iterator functionality
*/
struct _MR_FunctionVectorIteratorType {
	_MR_FunctionType* begin;
	_MR_FunctionType* end;
};

/*
Defined Public Functions
	_MR_FunctionVectorConstructor
	_MR_FunctionVectorDestructor
	_MR_FunctionVectorPushback
	_MR_FunctionVectorGetIterator
*/

_MR_FunctionVectorType* _MR_FunctionVectorConstructor(size_t initial_capacity);
void _MR_FunctionVectorDestructor(_MR_FunctionVectorType* v);
int _MR_FunctionVectorPushback(_MR_FunctionVectorType* v, _MR_FunctionType x);
_MR_FunctionVectorIteratorType _MR_FunctionVectorGetIterator(_MR_FunctionVectorType* v);

#endif /* FUNCTION_VECTOR_H */
