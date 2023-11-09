#include <CppUTestExt/MockSupport.h>
#include <TestSteps/TestSteps.h>

TEST_GROUP(TSTS_02)
{
    void check010(const int i)
    {
        SUBSTEPS()
        STEP(1)
        L_CHECK_TRUE(i >= 0)
        STEP(2)
        L_CHECK_TRUE(i <= 10)
        ENDSTEPS()
    }
};

//  failure in STEP(2.1)
TEST(TSTS_02, T01)
{
    STEP(1)
    check010(1);

    STEP(2)
    check010(-1);
}

//  failure in STEP(2.12.2)
TEST(TSTS_02, T02)
{
    STEP(1)
    SUBSTEPS()
    for (int i = 0; i < 20; ++i)
    {
        LSTEP(i)
        check010(i);
    }
    ENDSTEPS()
}
