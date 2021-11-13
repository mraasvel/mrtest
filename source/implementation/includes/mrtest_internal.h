#ifndef MRTEST_INTERNAL_H
# define MRTEST_INTERNAL_H

# include <stdio.h>
# include <stdlib.h>

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
		fprintf(stderr, _MR_FILE_LINE " MRTEST(" _MR_STR(expr) "): " type "\n"); \
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
		exit(EXIT_FAILURE); \
	} \
} while (0);

#endif /* MRTEST_INTERNAL_H */
