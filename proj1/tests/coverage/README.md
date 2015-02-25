# Testing Coverage

### According ot Abstract Syntax Trees Table 1,2 We have 15 test cases and still 61 test case unimplemented.

This is rough report about our test coverage, we should definitly add more test cases. I will continue working on it tomrrow.

**Important** When anyone of us write a test case, add test case name at the end of file `tests/coverage/test-check.lst` or mark current one as **Covered: True**. In this way, we will keep track the big picture of of test coverage.

**Name Format** For basic test case, please have `ast-` prefix for test file, like `ast-if_expr.py`, `ast-if_expr.std`

In the `team-repo/proj1` directory:

Check current **uncover** test cases:

	~/team-repo/proj1 $ cat tests/coverage/test-check.lst | grep "Covered: False"

Check number of current **uncover** test cases:
	
	~/team-repo/proj1 $ cat tests/coverage/test-check.lst | grep "Covered: False" | wc -l	

Check current **cover** test cases:

	~/team-repo/proj1 $ cat tests/coverage/test-check.lst | grep "Covered: True"

Check number of current **covered** test cases:

	~/team-repo/proj1 $ cat tests/coverage/test-check.lst | grep "Covered: False"


Hope we can collaborate well and achieve success!