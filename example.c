#define MRTEST_MAIN
#include "mrtest.h"
#include <stdbool.h>
#include <signal.h>

TEST_CASE(TestName, TestTag) {
	MRTEST(true);
	MRTEST(false);
}

TEST_CASE(PassTest, PassTag) {
	MRTEST(true);
}

TEST_CASE(CrashingTestSegv, crash) {
	void* x = NULL;
	MRTEST(*(int*)x); // dereference NULL pointer causing SIGSEGV
}

TEST_CASE(CrashingTestInt, crash) {
	kill(getpid(), SIGINT);
}
