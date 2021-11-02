#define _GNU_SOURCE
#include <dlfcn.h>
#include "mrtest.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MRTEST_MAIN

TEST_CASE(a) {
	MRTEST(1 == 1);
}

TEST_CASE(b) {
	MRTEST(0 == 1);
	MRTEST(0 == 1);
	MRTEST(0 == 1);
}

TEST_CASE(c) {
	MRTEST("Nice");
}

#ifdef MRTEST_MAIN
int main(void) {
	_MR_FunctionVectorType* v = _MR_FunctionVectorConstructor(100);

/* Add functions to vector using dlsym */
	size_t i = 0;
	char buf[32];
	_MR_TestFunctionPointer fptr;
	while (true) {
		snprintf(buf, 32, "_MR_TestFunction%lu", i);
		fptr = dlsym(RTLD_DEFAULT, buf);
		if (fptr == NULL) {
			break;
		}

		if (_MR_FunctionVectorPushback(v, fptr()) == -1) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		++i;
	}

/* Execute Testcases */
	_MR_FunctionVectorIteratorType it = _MR_FunctionVectorGetIterator(v);
	while (it.begin != it.end) {
		printf("-- TestCase: [%s] --\n", it.begin->id);

		it.begin->function();
		++it.begin;

		if (it.begin != it.end) {
			printf("\n");
		}
	}

	_MR_FunctionVectorDestructor(v);
	return 0;
}
#endif /* MRTEST_MAIN */
