#ifndef MRTEST_INTERNAL_H
# define MRTEST_INTERNAL_H

# include <unistd.h>

/* Colors */

# define _MR_RED_BOLD		"\033[1;31m"
# define _MR_GREEN_BOLD		"\033[1;32m"
# define _MR_RESET_COLOR	"\033[0m"

/*
Helper macros for _MR_MSG
*/

#define _MR_STRINGIZING(x) #x
#define _MR_STR(x) _MR_STRINGIZING(x)
#define _MR_FILE_LINE __FILE__ ":" _MR_STR(__LINE__)

#define _MR_MSG_LEN(x) (sizeof(x) - 1)
#define _MR_CONST_MSG_LEN (sizeof("]: MRTEST(): \n") - 1)

/*
Assertion message
[file]:[line_number]: [function_name]: [expression]: [message_type]
*/
#define _MR_PASS_TEXT "[" _MR_GREEN_BOLD "PASS" _MR_RESET_COLOR "]"
#define _MR_FAIL_TEXT "[" _MR_RED_BOLD "FAIL" _MR_RESET_COLOR "]"

#define _MR_MSG(expr, type) \
	do { \
		write(STDOUT_FILENO, \
			_MR_FILE_LINE " [", \
			sizeof(_MR_FILE_LINE) + 1); \
		write(STDOUT_FILENO, \
			__func__, \
			strlen(__func__)); \
		write(STDOUT_FILENO, \
			"]: MRTEST(" _MR_STR(expr) "): " type "\n", \
			_MR_MSG_LEN(_MR_STR(expr)) \
			+ _MR_MSG_LEN(type) \
			+ _MR_CONST_MSG_LEN); \
	} while (0);

#define _MR_PASS_MSG(expr) _MR_MSG(expr, _MR_PASS_TEXT)
#define _MR_FAIL_MSG(expr) _MR_MSG(expr, _MR_FAIL_TEXT)

/*
Main assertion macro
*/

#define _MR_TEST(expression) \
do { \
	if (!(expression)) { \
		_MR_FAIL_MSG(expression) \
	} else { \
		_MR_PASS_MSG(expression) \
	}\
} while (0);

#endif /* MRTEST_INTERNAL_H */
#ifndef MR_FUNCTION_VECTOR_H
# define MR_FUNCTION_VECTOR_H

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
	char* tag;
	char* name;
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
int _MR_FunctionVectorPushback(_MR_FunctionVectorType** v_ptr, _MR_FunctionType x);
_MR_FunctionVectorIteratorType _MR_FunctionVectorGetIterator(_MR_FunctionVectorType* v);

#endif /* MR_FUNCTION_VECTOR_H */
#ifndef MR_TESTCASE_H
# define MR_TESTCASE_H


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
#ifndef MRTEST_H
# define MRTEST_H


# include <string.h> // Need strdup in copy function

# define MRTEST(x) _MR_TEST(x)
# define TEST_CASE(name, tag) _MR_TEST_CASE(name, tag)

extern _MR_FunctionVectorType* _MR_global_function_vector;

#ifdef MRTEST_MAIN
void _MR_executeTestCase(_MR_FunctionType* it);
int _MR_shouldExecuteTag(int argc, char *argv[], char *tag);
int main(int argc, char *argv[]) {
	_MR_FunctionVectorType* v = _MR_global_function_vector;

	if (v == NULL) {
		return 0;
	}

/* Skip program name */
	--argc; ++argv;

/* Execute Testcases */
	_MR_FunctionVectorIteratorType it = _MR_FunctionVectorGetIterator(v);
	while (it.begin != it.end) {
		if (_MR_shouldExecuteTag(argc, argv, it.begin->tag)) {
			_MR_executeTestCase(it.begin);
		}
		++it.begin;
	}

	_MR_FunctionVectorDestructor(v);
	return 0;
}
#endif /* MRTEST_MAIN */

#endif /* MRTEST_H */