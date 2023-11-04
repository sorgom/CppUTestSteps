
#include <TestSteps/TestStepsPlugin.h>
#include <CppUTest/CommandLineTestRunner.h>

int main(const int argc, const char* const* const argv)
{
    TestStepsPlugin::setup();
    return CommandLineTestRunner::RunAllTests(argc, argv);
}