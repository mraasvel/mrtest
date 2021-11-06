#define MRTEST_MAIN
#include "mrtest.h"
#include <stdbool.h>
#include <stdlib.h>

TEST_CASE(TestName, "test_tag") {
	MRTEST(true);
	MRTEST(false);
}

TEST_CASE(CrashingTestSegv, "Crash") {
	void* x = NULL;
	MRTEST(*(int*)x); // dereferenc NULL pointer
}
