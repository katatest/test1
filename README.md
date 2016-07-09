libroman
Jake Knickerbocker
July 9, 2006

----------
Desription
----------

A simple shared library for adding and subtracting roman numeral strings.
See "roman.h" for usage.  There's clearly room for refactoring, but
this is at least a solution that works.

The basic idea is that we convert the string, roman numeral
representations to integers, do our arithmetic, and then convert
back to string representation for the result.

Roman numeral rules assumed:
- Zero is not represented.
- Negative values are not represented.
- Subtraction rule, where a smaller roman numeral char precedes
	a larger one to combine for a value, is limited to:

	IV, IX, XL, XC, CD, CM

Also built is a testing program that makes use of libcheck for basic unit
tests.

--------------------------------------------------
Build for Linux (tested on Ubuntu 16.04 and 15.04)
Builds both .so file and tester.
--------------------------------------------------

sudo apt-get install check
make

----------
Run Tests
----------

./tester

Voila.
