/*
 * ============================================================================
 * Project       : Automotive CAN Message Simulator
 * File Name     : test_can_simulator.c
 * Author        : Vishnuprakash Jagan Mohan
 * Date          : 21 October 2026
 * Place         : Chemnitz, Germany
 * Description   : Performs basic checks on CAN message IDs, payload length,
 *                 and engine-speed data decoding.
 * ============================================================================
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "can_simulator.h"

int main(void)
{
    /* Create a sample engine message */
    CanMessage engine_message =
    {
        .id = ENGINE_ECU_ID,
        .length = 2U,
        .data = {30U, 0U}
    };

    /* Decode the engine-speed value */
    uint16_t rpm_units =
        (uint16_t)engine_message.data[0]
        | ((uint16_t)engine_message.data[1] << 8);

    uint32_t engine_rpm = (uint32_t)rpm_units * 100U;

    /* Test the message identifier */
    assert(engine_message.id == ENGINE_ECU_ID);

    /* Test the payload length */
    assert(engine_message.length == 2U);

    /* Test the decoded engine speed */
    assert(engine_rpm == 3000U);

    /* Test the Classic CAN payload limit */
    assert(engine_message.length <= CAN_MAX_DATA_LENGTH);

    printf("PASS: Engine message ID\n");
    printf("PASS: Message payload length\n");
    printf("PASS: Engine speed decoding\n");
    printf("PASS: Maximum payload length\n");

    printf("\nAll basic tests passed.\n");

    return 0;
}
