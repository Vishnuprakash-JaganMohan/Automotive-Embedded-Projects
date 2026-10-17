#ifndef ECU_H
#define ECU_H

#include <stdbool.h>
#include <stdint.h>

/* ECU operating states */
typedef enum
{
    ECU_STATE_OFF,
    ECU_STATE_RUNNING,
    ECU_STATE_FAULT
} EcuState;

/* Simulated diagnostic trouble codes */
typedef enum
{
    DTC_NONE,
    DTC_THROTTLE_LOW,
    DTC_THROTTLE_HIGH,
    DTC_TEMP_LOW,
    DTC_TEMP_HIGH,
    DTC_OVERTEMPERATURE
} DtcCode;

/* Simulated sensor and driver inputs */
typedef struct
{
    float throttle_percent;
    float temperature_c;

    bool ignition_on;
    bool brake_pressed;
} EcuInputs;

/* ECU output data */
typedef struct
{
    EcuState state;
    uint32_t engine_rpm;

    bool overtemperature_fault;

    DtcCode dtc;

    uint32_t cycle_count;
} EcuOutputs;

/* ECU functions */
void ECU_Init(EcuOutputs *outputs);

bool ECU_ValidateInputs(const EcuInputs *inputs);

void ECU_Update(
    const EcuInputs *inputs,
    EcuOutputs *outputs
);

const char *ECU_GetStateName(EcuState state);

const char *ECU_GetDtcName(DtcCode dtc);

const char *ECU_GetDtcDescription(DtcCode dtc);

#endif
