#define MRTEST_MAIN
#include "mrtest.h"
#include <stdlib.h>

int Factorial(int n) {
	if (n <= 1) {
		return 1;
	}

	return n * Factorial(n - 1);
}

TEST_CASE(ThisIsATest) {
	MRTEST(1 == 0);
	MRTEST(Factorial(1) == 2);
}

TEST_CASE(SecondTest) {
	MRTEST(1 == 1);
}

TEST_CASE(atoi_tests) {
	MRTEST(atoi("5") == 5);
	MRTEST(atoi("5") == 4);
	MRTEST(atoi("5") == 4);
	MRTEST(atoi("5") == 4);
	MRTEST(atoi("5") == 4);
	MRTEST(atoi("5") == 4);
}

TEST_CASE(atoi_overflow) {
	MRTEST(atoi("419823749812739487234") == 0);
}

TEST_CASE(new_tester) {
	MRTEST(1 == 424827347);
}
