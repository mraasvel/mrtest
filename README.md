# MrTest
Simple C testing framework
---

## Usage

Copy the `mrtest.c` and `mrtest.h` file into your project.
In order to use the mrtest main: create a `.c` file that has the following:
```
#define MRTEST_MAIN
#include "mrtest.h"
```
Write as many testcases, in as many different files as you want.
Compile with `gcc` or `clang`

---

## Example Usage

```
#define MRTEST_MAIN
#include "mrtest.h"

TEST_CASE(unique_test_identifier) {
	MRTEST(true);
	MRTEST(false);
}
```
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
