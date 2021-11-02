#ifndef FUNCTION_VECTOR_H
# define FUNCTION_VECTOR_H


typedef struct _MR_FunctionType _MR_FunctionType;
typedef struct _MR_FunctionVectorType _MR_FunctionVectorType;

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

struct _MR_FunctionVectorType {

};

#endif /* FUNCTION_VECTOR_H */
