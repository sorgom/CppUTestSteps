
#include <TestStepper/TestStepperPlugin.h>
#include <CppUTest/CommandLineTestRunner.h>

int main(const int argc, const char* const* const argv)
{
    TestStepperPlugin::setup();
    return CommandLineTestRunner::RunAllTests(argc, argv);
}