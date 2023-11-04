//  ============================================================
//  failing tests samples
//  ============================================================
//  created by Manfred Sorgo

#include <CppUTestExt/MockSupport.h>
#include <TestSteps/TestSteps.h>

TEST_GROUP(TSTS_01)
{};

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
        LSTEP(n)
        L_CHECK_TRUE(n < 5)
    }
    ENDSTEPS()
}
