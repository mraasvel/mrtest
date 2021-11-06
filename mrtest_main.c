#define MRTEST_MAIN
#include "mrtest.h"
#include <stdbool.h>

TEST_CASE(TestName, "TestTag") {
	MRTEST(true);
	MRTEST(false);
}

