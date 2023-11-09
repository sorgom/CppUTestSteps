# Test Steps for #CppUTest

#CppUTest

The test steps solve a great disadvantage of CppUTest:

When CppUTest exits a test due to an unmatched expectation it only provides
- the test name
- the source line of the test's begin

So if you have a test with some amount of lines
you will have a hard time to figure out
where exactly the mismatch happens.

Using TestSteps's STEP() macro
will provide you with line of the last STEP() macro placed.

The STEP() macro also helps
to give your tests a more readable structure.

## samples

### simple test code
```cpp
01  #include <CppUTestExt/MockSupport.h>
02  #include <TestSteps/TestSteps.h>
03
04  TEST_GROUP(TSTS_01) {};
05
06  //  failure in STEP(2)
07  TEST(TSTS_01, T01)
08  {
09      STEP(1)
10      mock().expectOneCall("somecall").withParameter("value", 42);
11      mock().actualCall("somecall").withParameter("value", 42);   
12      mock().checkExpectations(); mock().clear();
13
14      STEP(2)
15      mock().expectOneCall("somecall").withParameter("value", 42);
16      mock().actualCall("somecall").withParameter("value", 43);   
17      mock().checkExpectations(); mock().clear();
18  }
19
20  //  failure in STEP(2.6)
21  TEST(TSTS_01, T02)
22  {
23      STEP(1)
24      L_CHECK_EQUAL(2, 2)
25
26      STEP(2)
27      SUBSTEPS()
28      for (unsigned n = 0; n < 10; ++n)
29      {
30          LSTEP(n)
31          L_CHECK_TRUE(n < 5)
32      }
33      ENDSTEPS()
34  }
35
```
### test ouput
```shell
$ bin/tests -b -v
TEST(TSTS_01, T01)
../samples/TSTS_01.cpp:14: error: Failure in TEST(TSTS_01, T01)
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
line: 14

TEST(TSTS_01, T02)
../samples/TSTS_01.cpp:31: error: Failure in TEST(TSTS_01, T02)
        expected <true>
        but was  <false>
        difference starts at position 0 at: <          false     >
                                                       ^

STEP(2.6)

STEP(2)
file: ../samples/TSTS_01.cpp
func: testBody
line: 26

STEP(6)
file: ../samples/TSTS_01.cpp
func: testBody
line: 31
```

### test code calling subroutine
```cpp
01  #include <CppUTestExt/MockSupport.h>
02  #include <TestSteps/TestSteps.h>
03
04  TEST_GROUP(TSTS_02)
05  {
06      void check010(const int i)
07      {
08          SUBSTEPS()
09          STEP(1)
10          L_CHECK_TRUE(i >= 0)
11          STEP(2)
12          L_CHECK_TRUE(i <= 10)
13          ENDSTEPS()
14      }
15  };
16
17  //  failure in STEP(2.1)
18  TEST(TSTS_02, T01)
19  {
20      STEP(1)
21      check010(1);
22
23      STEP(2)
24      check010(-1);
25  }
26
27  //  failure in STEP(2.12.2)
28  TEST(TSTS_02, T02)
29  {
30      STEP(1)
31      SUBSTEPS()
32      for (int i = 0; i < 20; ++i)
33      {
34          LSTEP(i)
35          check010(i);
36      }
37      ENDSTEPS()
38  }
39
```
### test ouput
```shell
$ bin/tests -b -v
TEST(TSTS_02, T01)
../samples/TSTS_02.cpp:10: error: Failure in TEST(TSTS_02, T01)
        expected <true>
        but was  <false>
        difference starts at position 0 at: <          false     >
                                                       ^

STEP(2.1)

STEP(2)
file: ../samples/TSTS_02.cpp
func: testBody
line: 23

STEP(1)
file: ../samples/TSTS_02.cpp
func: check010
line: 10

TEST(TSTS_02, T02)
../samples/TSTS_02.cpp:12: error: Failure in TEST(TSTS_02, T02)
        expected <true>
        but was  <false>
        difference starts at position 0 at: <          false     >
                                                       ^

STEP(1.12.2)

STEP(1)
file: ../samples/TSTS_02.cpp
func: testBody
line: 30

STEP(12)
file: ../samples/TSTS_02.cpp
func: testBody
line: 34

STEP(2)
file: ../samples/TSTS_02.cpp
func: check010
line: 12
```
