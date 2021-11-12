#ifndef MRTEST_H
# define MRTEST_H

# include "mrtest_internal.h" // IGNORE_TAG
# include "mr_testcase.h" // IGNORE_TAG
# include "mr_function_vector.h" // IGNORE_TAG

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
