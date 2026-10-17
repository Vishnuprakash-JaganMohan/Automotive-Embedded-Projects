#include "ecu.h"

#include <assert.h>
#include <stdio.h>

static void TestIgnitionOff(void)
{
    EcuInputs inputs = {
        0.0f,
        25.0f,
        false,
        false
    };

    EcuOutputs outputs;

    ECU_Init(&outputs);
    ECU_Update(&inputs, &outputs);

    assert(outputs.state == ECU_STATE_OFF);
    assert(outputs.engine_rpm == 0U);

    printf("PASS: Ignition OFF test\n");
}

static void TestNormalOperation(void)
{
    EcuInputs inputs = {
        50.0f,
        85.0f,
        true,
        false
    };

    EcuOutputs outputs;

    ECU_Init(&outputs);
    ECU_Update(&inputs, &outputs);

    assert(outputs.state == ECU_STATE_RUNNING);
    assert(outputs.engine_rpm == 2800U);
    assert(outputs.dtc == DTC_NONE);

    printf("PASS: Normal operation test\n");
}

static void TestOvertemperature(void)
{
    EcuInputs inputs = {
        20.0f,
        125.0f,
        true,
        false
    };

    EcuOutputs outputs;

    ECU_Init(&outputs);
    ECU_Update(&inputs, &outputs);

    assert(outputs.state == ECU_STATE_FAULT);
    assert(outputs.engine_rpm == 0U);
    assert(outputs.overtemperature_fault == true);
    assert(outputs.dtc == DTC_OVERTEMPERATURE);

    printf("PASS: Overtemperature test\n");
}

static void TestInvalidThrottle(void)
{
    EcuInputs inputs = {
        120.0f,
        85.0f,
        true,
        false
    };

    EcuOutputs outputs;

    ECU_Init(&outputs);
    ECU_Update(&inputs, &outputs);

    assert(outputs.state == ECU_STATE_FAULT);
    assert(outputs.engine_rpm == 0U);
    assert(outputs.dtc == DTC_THROTTLE_HIGH);

    printf("PASS: Invalid throttle test\n");
}

int main(void)
{
    TestIgnitionOff();
    TestNormalOperation();
    TestOvertemperature();
    TestInvalidThrottle();

    printf("\nAll ECU tests passed.\n");

    return 0;
}
