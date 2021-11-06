# MrTest
Simple C testing framework
---

## Usage

Copy the `mrtest.c` and `mrtest.h` file into your project.
In order to use the mrtest main: create a `.c` file that has the following:
```
#define MRTEST_MAIN
#include "mrtest.h"

TEST_CASE(TestName, "TestTag") {
	MRTEST(expression);
}
```
The MrTest main will automatically run TEST_CASES and the code inside of it.
If any arguments are specified, they will be matched with function tags (not unique),
only matching tags will be executed

There will only be output of failed test cases,
which prints the File, LineNumber, TestName, and assertion.
If any crash occurs within a TEST_CASE, it will be caught by the main and printed.

---

## Example Usage

```
1 #define MRTEST_MAIN
2 #include "mrtest.h"
3 #include <stdbool.h>
4
5 TEST_CASE(TestName, "test_tag") {
6 	MRTEST(true);
7 	MRTEST(false);
8 }
```

## Output
```
./run_example.sh TestTag
mrtest_main.c:7 [TestName]: MRTEST(0): [FAIL]
```

Running without arguments simply executes all the testcases.

---

## Language

Unique Test Identifier should be the same as a regular function name

---

## Implementation

### Main

The main iterates over a vector containing function pointers to each testcase.

### Assertions

The assertion simply expands the expression into an if statement that prints an error message if false

---

### TEST_CASE

TEST_CASE macro expands into a set of functions:

```
TEST_CASE(unique_identifier) {
	/* ASSERTIONS */
}
```

->

```
static void unique_identifier(void);

static void MR_UNIQUE_NAMExx (void) __attribute__ ((constructor));
static void MR_UNIQUE_NAMExx (void) {
	/* add unique_identifier to a global table of function pointers */
}

static void unique_identifier(void) {
	/* ASSERTIONS */
}
```

The constructor attribute is not C standard.
It makes it so that the function is called before the main is executed.
