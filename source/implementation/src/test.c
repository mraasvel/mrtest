#include "mrtest.h"
#include <stdbool.h>
#include <signal.h>

int f(char *s) {
	(void)s;
	return 0;
}

TEST_CASE(abcd, tag) {
	MRTEST(1 == 1);
	// MRTEST(false);
	// MRTEST(f("abcde"));
}

TEST_CASE(asdjf, tagging) {
	MRTEST(1 == 0);
}

TEST_CASE(ExampleTests1, tag) {
	MRTEST("Hello");
}

TEST_CASE(ExampleTest2, crash) {
	kill(getpid(), SIGSEGV);
}

/* Crashes are handled through fork and waitpid checking */
TEST_CASE(ExampleTest3, SIGKILL) {
	kill(getpid(), SIGKILL);
}
TEST_CASE(ExampleTest5, SIGKILL) {
	kill(getpid(), SIGINT);
}
TEST_CASE(ExampleTest6, SIGKILL) {
	kill(getpid(), SIGABRT);
}

TEST_CASE(ExampleTest4, Correct) {
	MRTEST(1);
	MRTEST(1);
	MRTEST(1);
	MRTEST(1);
	MRTEST(1);
	MRTEST(1);
}
