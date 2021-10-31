# MrTest
Simple C testing framework
---

## Example Usage

```
TEST_CASE(test_tag) {
	MRTEST(true);
	MRTEST(false);
}
```

## Implementation

### Assertions

The assertion simply expands the expression into an if statement that prints an error message if false

### TEST_CASE

The TEST_CASE macro expands the TagName into a function prototype, which is added to a global HashTable,
using the tag as key so that arguments can be used to execute specific tags
