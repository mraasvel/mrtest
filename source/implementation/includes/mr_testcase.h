#ifndef MR_TESTCASE_H
# define MR_TESTCASE_H

#include "mrtest_internal.h" // IGNORE_TAG

/*
Simple prototype of void id(void)
*/
#define _MR_FUNCTION(x) static void x (void)

#define _MR_CONC_(x, y) x##y
#define _MR_CONC(x, y) _MR_CONC_(x, y)
#define _MR_UNIQUE_NAME(x) _MR_CONC(x, __COUNTER__)

/*
Function body of the dynamic test function

Will return the key and value of NAME and FUNCTION_POINTER
*/
#define _MR_TEST_FUNCTION_BODY(_MR_F_NAME, _MR_F_TAG) \
	do { \
		_MR_FunctionType x; \
		x.tag = (strdup(_MR_F_TAG)); \
		x.name = (strdup(_MR_STR(_MR_F_NAME))); \
		x.function = (_MR_F_NAME); \
		_MR_FunctionVectorPushback(&_MR_global_function_vector, x); \
	} while (0);

#define _MR_TEST_FUNCTION(id, tag, unique_name) \
			static void unique_name (void) __attribute__ ((constructor)); \
			static void unique_name (void) \
			{ _MR_TEST_FUNCTION_BODY(id, tag) }

/*
Generates the TEST_CASE(unique_id) {}

1. prototype for main tester function so we can get the function pointer
2. prefunction with dynamic naming so we can get it with dlsym:
	- Returns a pointer and identifier to the previous function (id)
3. prototype for main tester function, the braces after define the body
*/
#define _MR_TEST_CASE(id, tag) \
			_MR_FUNCTION(id); \
			_MR_TEST_FUNCTION(id, tag, _MR_UNIQUE_NAME(_MR_TestFunction)) \
			_MR_FUNCTION(id)

#endif /* MR_TESTCASE_H */
