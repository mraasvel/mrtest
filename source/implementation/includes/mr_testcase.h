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
#define _MR_TEST_FUNCTION_BODY(function_id, function_tag, function_name) \
	do { \
		_MR_FunctionType x; \
		x.name = (strdup(function_id)); \
		x.tag = (strdup(function_tag)); \
		if (!x.tag || !x.name) { \
			perror("mrtest: malloc"); \
			exit(EXIT_FAILURE); \
		} \
		x.function = (function_name); \
		_MR_FunctionVectorPushback(&_MR_global_function_vector, x); \
	} while (0);

#define _MR_TEST_FUNCTION(id, tag, fname, unique_name) \
			static void unique_name (void) __attribute__ ((constructor)); \
			static void unique_name (void) \
			{ _MR_TEST_FUNCTION_BODY(id, tag, fname) }

#define _MR_TEST_CASE_ID(id, tag, fname) \
		_MR_FUNCTION(fname); \
		_MR_TEST_FUNCTION(id, tag, fname, _MR_UNIQUE_NAME(_MR_TestFunction)) \
		_MR_FUNCTION(fname)

/*
Generates the TEST_CASE(unique_id) {}

1. prototype for main tester function so we can get the function pointer
2. prefunction with dynamic naming so we can get it with dlsym:
	- Returns a pointer and identifier to the previous function (id)
3. prototype for main tester function, the braces after define the body
*/
#define _MR_TEST_CASE(id, tag) _MR_TEST_CASE_ID(id, tag, _MR_UNIQUE_NAME(_MR_TestCase))

#endif /* MR_TESTCASE_H */
