#ifndef MRTEST_INTERNAL_H
# define MRTEST_INTERNAL_H

# include <unistd.h>

/* Colors */

# define __RED_BOLD		"\033[1;31m"
# define __GREEN_BOLD	"\033[1;32m"
# define __RESET_COLOR	"\033[0m"

/*
Helper macros for __ERROR_MSG
*/

#define __TRUE_TEXT "[" __GREEN_BOLD "PASS" __RESET_COLOR "]"
#define __FALSE_TEXT "[" __RED_BOLD "FAIL" __RESET_COLOR "]"

#define __STRINGIZING(x) #x
#define __STR(x) __STRINGIZING(x)
#define __FILE_LINE __FILE__ ":" __STR(__LINE__)
#define __LENGTH(x) \
	(sizeof(x) \
	+ sizeof(__FILE_LINE) \
	+ sizeof(": MR_ASSERT(): " __FALSE_TEXT "\n") - 3)

/*
False assertion message
[file]:[line_number]: [assertion]: [fail_message]
*/

#define __ERROR_MSG(x) \
	do { \
		write(STDOUT_FILENO, \
			__FILE_LINE ": MR_ASSERT(" __STR(x) "): " __FALSE_TEXT "\n", \
			__LENGTH(__STR(x))); \
	} while (0);

/*
Main assertion macro
*/

#define __MR_ASSERT(x) \
do { \
	if (!(x)) { \
		__ERROR_MSG(x) \
	} \
} while (0);

#endif /* MRTEST_INTERNAL_H */
