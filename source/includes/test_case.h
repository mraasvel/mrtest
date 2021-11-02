#ifndef TEST_CASE_H
# define TEST_CASE_H

#include "mrtest_internal.h"

/*
Simple prototype of void id(void)
*/
#define _MR_FUNCTION(x) void x (void)

#define _MR_CONC(x, y) x##y
#define _MR_CONC_(x, y) _MR_CONC(x, y)

/*
Function body of the dynamic test function

Will return the key and value of NAME and FUNCTION_POINTER
*/
#define _MR_TEST_FUNCTION_BODY(name) \
	do { \
		_MR_FunctionType x; \
		x.id = strdup(_MR_STR(name)); \
		x.function = (name); \
		return x; \
	} while (0);

#define _MR_TEST_FUNCTION(id) \
			_MR_FunctionType _MR_CONC_(_MR_TestFunction, __COUNTER__) (void) \
			{ _MR_TEST_FUNCTION_BODY(id) }

/*
Generates the TEST_CASE(unique_id) {}

1. prototype for main tester function so we can get the function pointer
2. prefunction with dynamic naming so we can get it with dlsym:
	- Returns a pointer and identifier to the previous function (id)
3. prototype for main tester function, the braces after define the body
*/
#define _MR_TEST_CASE(id) \
			_MR_FUNCTION(id); \
			_MR_TEST_FUNCTION(id) \
			_MR_FUNCTION(id)

#endif /* TEST_CASE_H */
