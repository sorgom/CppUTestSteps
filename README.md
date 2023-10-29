# Test Stepper for CppUTest

#CppUTest

The test stepper solves a great disadvantage of CppUTest:

When CppUTest exits a test due to an unmatched expectation it only provides
- the test name
- the source line of the test's begin

So if you have a test with some amount of lines
you will have a hard time to figure out
where exactly the mismatch happens.

Using TestStepper's STEP() macro
will provide you with line of the last STEP() macro placed.

The STEP() macro also helps
to give your tests a more readable structure.


