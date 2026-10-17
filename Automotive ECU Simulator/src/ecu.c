#include "ecu.h"

/* Initialize ECU outputs */
void ECU_Init(EcuOutputs *outputs)
{
    if (outputs == NULL)
    {
        return;
    }

    outputs->state = ECU_STATE_OFF;
    outputs->engine_rpm = 0U;
    outputs->overtemperature_fault = false;
    outputs->dtc = DTC_NONE;
    outputs->cycle_count = 0U;
}

/* Validate simulated sensor inputs */
bool ECU_ValidateInputs(const EcuInputs *inputs)
{
    if (inputs == NULL)
    {
        return false;
    }

    if (inputs->throttle_percent < 0.0f ||
        inputs->throttle_percent > 100.0f)
    {
        return false;
    }

    if (inputs->temperature_c < -40.0f ||
        inputs->temperature_c > 150.0f)
    {
        return false;
    }

    return true;
}

/* Execute one ECU control cycle */
void ECU_Update(
    const EcuInputs *inputs,
    EcuOutputs *outputs)
{
    if (inputs == NULL || outputs == NULL)
    {
        return;
    }

    outputs->cycle_count++;

    outputs->overtemperature_fault = false;
    outputs->dtc = DTC_NONE;

    /* Check sensor input validity */
    if (!ECU_ValidateInputs(inputs))
    {
        outputs->state = ECU_STATE_FAULT;
        outputs->engine_rpm = 0U;

        if (inputs->throttle_percent < 0.0f)
        {
            outputs->dtc = DTC_THROTTLE_LOW;
        }
        else if (inputs->throttle_percent > 100.0f)
        {
            outputs->dtc = DTC_THROTTLE_HIGH;
        }
        else if (inputs->temperature_c < -40.0f)
        {
            outputs->dtc = DTC_TEMP_LOW;
        }
        else if (inputs->temperature_c > 150.0f)
        {
            outputs->dtc = DTC_TEMP_HIGH;
        }

        return;
    }

    /* Check overtemperature */
    if (inputs->temperature_c > 120.0f)
    {
        outputs->state = ECU_STATE_FAULT;
        outputs->engine_rpm = 0U;
        outputs->overtemperature_fault = true;
        outputs->dtc = DTC_OVERTEMPERATURE;

        return;
    }

    /* Check ignition state */
    if (!inputs->ignition_on)
    {
        outputs->state = ECU_STATE_OFF;
        outputs->engine_rpm = 0U;

        return;
    }

    /* Normal operating state */
    outputs->state = ECU_STATE_RUNNING;

    /*
     * Educational RPM model:
     * 800 RPM idle + 40 RPM per throttle percentage point.
     *
     * This is not a physical engine model.
     */
    outputs->engine_rpm =
        800U + (uint32_t)(inputs->throttle_percent * 40.0f);
}

/* Convert ECU state to readable text */
const char *ECU_GetStateName(EcuState state)
{
    switch (state)
    {
        case ECU_STATE_OFF:
            return "OFF";

        case ECU_STATE_RUNNING:
            return "RUNNING";

        case ECU_STATE_FAULT:
            return "FAULT";

        default:
            return "UNKNOWN";
    }
}

/* Return a simulated diagnostic code label */
const char *ECU_GetDtcName(DtcCode dtc)
{
    switch (dtc)
    {
        case DTC_NONE:
            return "NONE";

        case DTC_THROTTLE_LOW:
            return "SIM-P0122";

        case DTC_THROTTLE_HIGH:
            return "SIM-P0123";

        case DTC_TEMP_LOW:
            return "SIM-TEMP-LOW";

        case DTC_TEMP_HIGH:
            return "SIM-TEMP-HIGH";

        case DTC_OVERTEMPERATURE:
            return "SIM-P0217";

        default:
            return "SIM-UNKNOWN";
    }
}

/* Return a readable fault description */
const char *ECU_GetDtcDescription(DtcCode dtc)
{
    switch (dtc)
    {
        case DTC_NONE:
            return "No fault detected";

        case DTC_THROTTLE_LOW:
            return "Throttle input below valid range";

        case DTC_THROTTLE_HIGH:
            return "Throttle input above valid range";

        case DTC_TEMP_LOW:
            return "Temperature input below valid range";

        case DTC_TEMP_HIGH:
            return "Temperature input above valid range";

        case DTC_OVERTEMPERATURE:
            return "Simulated engine overtemperature";

        default:
            return "Unknown diagnostic code";
    }
}
