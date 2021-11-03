#include "mrtest.h"
#include <stdbool.h>

int f(char *s) {
	(void)s;
	return 0;
}

TEST_CASE(abcd) {
	MRTEST(1 == 1);
	MRTEST(false);
	MRTEST(f("abcde"));
}

TEST_CASE(asdjf) {
	MRTEST(1 == 0);
}
