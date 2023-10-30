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

## samples

### test code
```cpp
#include <CppUTestExt/MockSupport.h>
#include <TestStepper/TestStepper.h>

TEST_GROUP(TSTS_01) {};

//  failure in STEP(2)
TEST(TSTS_01, T01)
{
    STEP(1)
    mock().expectOneCall("somecall").withParameter("value", 42);
    mock().actualCall("somecall").withParameter("value", 42);
    mock().checkExpectations(); mock().clear();
    
    STEP(2)
    mock().expectOneCall("somecall").withParameter("value", 42);
    mock().actualCall("somecall").withParameter("value", 43);
    mock().checkExpectations(); mock().clear();
}

//  failure in STEP(2.6)
TEST(TSTS_01, T02)
{
    STEP(1)
    L_CHECK_EQUAL(2, 2)
    
    STEP(2)
    //  valid 5 steps: 0 .. 4
    //  invalid 6th step: 5
    SUBSTEPS()
    for (unsigned n = 0; n < 10; ++n)
    {
        //  STEP(2.1) .. STEP(2.10)
        LSTEP(n)
        L_CHECK_TRUE(n < 5)
    }
    ENDSTEPS()
}
```
### test ouput
```shell
$ bin/tests -b

../samples/TSTS_01.cpp:13: error: Failure in TEST(TSTS_01, T01)
        Mock Failure: Unexpected parameter value to parameter "value" to function "somecall": <43 (0x2b)>
        EXPECTED calls that WERE NOT fulfilled related to function: somecall
                somecall -> int value: <42 (0x2a)> (expected 1 call, called 0 times)
        EXPECTED calls that WERE fulfilled related to function: somecall
                <none>
        ACTUAL unexpected parameter passed to function: somecall
                int value: <43 (0x2b)>

STEP(2)
file: ../samples/TSTS_01.cpp
func: testBody
line: 20
.
../samples/TSTS_01.cpp:39: error: Failure in TEST(TSTS_01, T02)
        expected <true>
        but was  <false>
        difference starts at position 0 at: <          false     >
                                                       ^

STEP(2.6)

STEP(2)
file: ../samples/TSTS_01.cpp
func: testBody
line: 32

STEP(6)
file: ../samples/TSTS_01.cpp
func: testBody
line: 39
.
Errors (2 failures, 2 tests, 2 ran, 9 checks, 0 ignored, 0 filtered out, 0 ms)
```



