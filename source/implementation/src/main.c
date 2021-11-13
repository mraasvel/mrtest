#define MRTEST_MAIN
#include "mrtest.h"

TEST_CASE("a", "tag1") {
	MRTEST(1 == 1);
}

TEST_CASE("b", "tag1") {
	MRTEST(1 == 1);
}

TEST_CASE("c", "tag2") {
	MRTEST(1 == 1);
}

TEST_CASE("d", "tag3") {
	MRTEST(1 == 1);
}
