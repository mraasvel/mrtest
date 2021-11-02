#ifndef FUNCTION_VECTOR_H
# define FUNCTION_VECTOR_H

typedef struct _MR_FunctionType _MR_FunctionType;
typedef struct _MR_FunctionVectorType _MR_FunctionVectorType;

typedef _MR_FunctionType (*_MR_TestFunctionPointer)(void);
typedef void (*_MR_TestCaseFunction)(void);

struct _MR_FunctionType {
	char *id;
	_MR_TestCaseFunction function;
};

struct _MR_FunctionVectorType {

};

#endif /* FUNCTION_VECTOR_H */
