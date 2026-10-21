/*
 * ============================================================================
 * Project       : Automotive CAN Message Simulator
 * File Name     : main.c
 * Author        : Vishnuprakash Jagan Mohan
 * Date          : 21 October 2026
 * Place         : Chemnitz, Germany
 * Description   : Main application demonstrating simulated communication
 *                 between engine and brake electronic control units (ECUs).
 * ============================================================================
 */

#include <stdio.h>
#include "can_simulator.h"

int main(void)
{
    /*
     * Engine ECU message
     *
     * Data value = 30
     * Scaling factor = 100 RPM
     * Actual engine speed = 3000 RPM
     */
    CanMessage engine_message =
    {
        .id = ENGINE_ECU_ID,
        .length = 2U,
        .data = {30U, 0U}
    };

    /*
     * Brake ECU message
     *
     * 0 = Brake released
     * 1 = Brake pressed
     */
    CanMessage brake_message =
    {
        .id = BRAKE_ECU_ID,
        .length = 1U,
        .data = {1U}
    };

    /* Example message with an unsupported identifier */
    CanMessage unknown_message =
    {
        .id = 0x555U,
        .length = 1U,
        .data = {0xAAU}
    };

    printf("========================================\n");
    printf("   AUTOMOTIVE CAN MESSAGE SIMULATOR\n");
    printf("========================================\n\n");

    /* Simulate engine ECU communication */
    printf("--- Engine ECU ---\n");

    send_message(&engine_message);
    receive_message(&engine_message);

    printf("\n");

    /* Simulate brake ECU communication */
    printf("--- Brake ECU ---\n");

    send_message(&brake_message);
    receive_message(&brake_message);

    printf("\n");

    /* Test unknown message handling */
    printf("--- Unknown ECU Message ---\n");

    send_message(&unknown_message);
    receive_message(&unknown_message);

    printf("\nSimulation completed.\n");

    return 0;
}
