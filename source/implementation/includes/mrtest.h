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
int _MR_executeTestCase(_MR_FunctionType* it);
int _MR_shouldExecuteTag(int argc, char *argv[], char *tag);
void _MR_printEndMessage(size_t num_testcases, size_t num_failed);

int main(int argc, char *argv[]) {
	_MR_FunctionVectorType* v = _MR_global_function_vector;

	if (v == NULL) {
		return 0;
	}

/* Skip program name */
	--argc; ++argv;

	size_t num_testcases = 0;
	size_t num_failed = 0;
/* Execute Testcases */
	_MR_FunctionVectorIteratorType it = _MR_FunctionVectorGetIterator(v);
	while (it.begin != it.end) {
		if (_MR_shouldExecuteTag(argc, argv, it.begin->tag)) {
			++num_testcases;
			if (_MR_executeTestCase(it.begin) != 0) {
				++num_failed;
			}
		}
		++it.begin;
	}

	_MR_FunctionVectorDestructor(v);

	_MR_printEndMessage(num_testcases, num_failed);
	return num_failed == 0 ? 0 : 1;
}
#endif /* MRTEST_MAIN */

#endif /* MRTEST_H */
