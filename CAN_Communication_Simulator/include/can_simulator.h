/*
 * ============================================================================
 * Project       : Automotive CAN Message Simulator
 * File Name     : can_simulator.h
 * Author        : Vishnuprakash Jagan Mohan
 * Date          : 21 October 2026
 * Place         : Chemnitz, Germany
 * Description   : Defines CAN message IDs, message structure, and function
 *                 declarations for a simple automotive communication
 *                 simulator.
 * ============================================================================
 */

#ifndef CAN_SIMULATOR_H
#define CAN_SIMULATOR_H

#include <stdint.h>

/* Maximum payload size for a Classic CAN data frame */
#define CAN_MAX_DATA_LENGTH 8U

/* CAN message identifiers */
#define ENGINE_ECU_ID  0x100U
#define BRAKE_ECU_ID   0x200U

/* Structure representing a simulated CAN message */
typedef struct
{
    uint16_t id;
    uint8_t length;
    uint8_t data[CAN_MAX_DATA_LENGTH];

} CanMessage;

/* Function declarations */
void send_message(const CanMessage *message);
void receive_message(const CanMessage *message);

#endif /* CAN_SIMULATOR_H */
