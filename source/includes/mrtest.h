#ifndef MRTEST_H
# define MRTEST_H

# include "mrtest_internal.h"
# include "test_case.h"
# include "function_vector.h"
# include <string.h> // Need strdup in copy function

# define MRTEST(x) _MR_TEST(x)
# define TEST_CASE(x) _MR_TEST_CASE(x)

extern _MR_FunctionVectorType* _MR_global_function_vector;

#ifdef MRTEST_MAIN
int main(void) {
	_MR_FunctionVectorType* v = _MR_global_function_vector;

	if (v == NULL) {
		return 0;
	}

/* Execute Testcases */
	_MR_FunctionVectorIteratorType it = _MR_FunctionVectorGetIterator(v);
	while (it.begin != it.end) {
		it.begin->function();
		++it.begin;
	}

	_MR_FunctionVectorDestructor(v);
	return 0;
}
#endif /* MRTEST_MAIN */

#endif /* MRTEST_H */
