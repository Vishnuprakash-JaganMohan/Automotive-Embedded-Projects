/*
 * ============================================================================
 * Project       : Automotive CAN Message Simulator
 * File Name     : can_simulator.c
 * Author        : Vishnuprakash Jagan Mohan
 * Date          : 21 October 2026
 * Place         : Chemnitz, Germany
 * Description   : Implements simulated CAN message transmission, reception,
 *                 payload interpretation, and basic message validation.
 * ============================================================================
 */

#include <stdio.h>
#include "can_simulator.h"

/*
 * Function Name : send_message
 * Description   : Simulates transmission of a CAN message by displaying
 *                 its identifier, data length, and payload bytes.
 * Input         : Pointer to a CAN message.
 * Return        : None.
 */
void send_message(const CanMessage *message)
{
    /* Check whether the message pointer is valid */
    if (message == NULL)
    {
        printf("TX Error: NULL message pointer.\n");
        return;
    }

    /* Validate the payload length */
    if (message->length > CAN_MAX_DATA_LENGTH)
    {
        printf("TX Error: Invalid message length.\n");
        return;
    }

    /* Display CAN message information */
    printf("TX | ID: 0x%03X | DLC: %u | Data:",
           (unsigned int)message->id,
           (unsigned int)message->length);

    /* Display each payload byte */
    for (uint8_t i = 0; i < message->length; i++)
    {
        printf(" %02X", (unsigned int)message->data[i]);
    }

    printf("\n");
}

/*
 * Function Name : receive_message
 * Description   : Simulates receiving and interpreting a CAN message
 *                 based on its message identifier.
 * Input         : Pointer to a CAN message.
 * Return        : None.
 */
void receive_message(const CanMessage *message)
{
    /* Check whether the message pointer is valid */
    if (message == NULL)
    {
        printf("RX Error: NULL message pointer.\n");
        return;
    }

    /* Validate the payload length */
    if (message->length > CAN_MAX_DATA_LENGTH)
    {
        printf("RX Error: Invalid message length.\n");
        return;
    }

    printf("RX | ID: 0x%03X | ",
           (unsigned int)message->id);

    /* Process engine ECU message */
    if (message->id == ENGINE_ECU_ID)
    {
        /* Engine speed requires two bytes */
        if (message->length < 2U)
        {
            printf("Error: Engine message is too short.\n");
            return;
        }

        /*
         * Decode the two-byte little-endian value.
         * The decoded value represents units of 100 RPM.
         */
        uint16_t rpm_units =
            (uint16_t)message->data[0]
            | ((uint16_t)message->data[1] << 8);

        uint32_t engine_rpm = (uint32_t)rpm_units * 100U;

        printf("Engine Speed: %lu RPM\n",
               (unsigned long)engine_rpm);
    }

    /* Process brake ECU message */
    else if (message->id == BRAKE_ECU_ID)
    {
        /* Brake status requires at least one byte */
        if (message->length < 1U)
        {
            printf("Error: Brake message is empty.\n");
            return;
        }

        if (message->data[0] == 0U)
        {
            printf("Brake Status: RELEASED\n");
        }
        else
        {
            printf("Brake Status: PRESSED\n");
        }
    }

    /* Handle unsupported message identifiers */
    else
    {
        printf("Unknown CAN Message ID.\n");
    }
}
