#define MRTEST_MAIN
#include "mrtest.h"

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
