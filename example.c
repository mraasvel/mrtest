#define MRTEST_MAIN
#include "mrtest.h"
#include <stdbool.h>
#include <signal.h>

TEST_CASE(TestName, "test_tag") {
	MRTEST(true);
	MRTEST(false);
}

TEST_CASE(CrashingTestSegv, "crash") {
	void* x = NULL;
	MRTEST(*(int*)x); // dereferenc NULL pointer
}

TEST_CASE(CrashingTestInt, "crash") {
	kill(getpid(), SIGINT);
}
