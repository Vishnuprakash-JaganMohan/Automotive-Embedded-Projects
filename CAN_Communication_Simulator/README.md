# Automotive CAN Communication Simulator

A lightweight automotive embedded C project that simulates CAN-style message
transmission and reception between virtual Electronic Control Units (ECUs).

The project demonstrates fundamental automotive communication concepts,
including message identifiers, payload encoding, data decoding, message
validation, and handling of unknown message identifiers.

---

## Project Information

| Property | Details |
|---|---|
| Project Name | Automotive CAN Communication Simulator |
| Author | Vishnuprakash Jagan Mohan |
| Location | Chemnitz, Germany |
| Programming Language | C11 |
| Compiler | GCC |
| Development Environment | Visual Studio Code |
| Domain | Automotive Embedded Systems |
| Communication Concept | Controller Area Network (CAN) |

---

## 1. Project Overview

Modern vehicles contain multiple Electronic Control Units (ECUs) that exchange
information to coordinate vehicle functions.

For example:
- The Engine ECU provides engine speed information.
- The Brake ECU provides brake status information.
- Other ECUs can identify messages using their message identifiers.

This project implements a simplified console-based simulation of these
communication concepts using C.

It demonstrates how a message can be represented, transmitted in a simulated
environment, received, and interpreted according to its identifier.

### Project Objectives

- Represent CAN-style messages using a C structure.
- Simulate message transmission and reception.
- Identify messages using predefined identifiers.
- Encode and decode engine speed data.
- Interpret brake status data.
- Validate message payload lengths.
- Detect unsupported message identifiers.
- Verify basic functionality using C assertions.

---

## 2. System Architecture

The project uses a simple three-file architecture.

```text
                  +----------------------+
                  |        main.c         |
                  |                      |
                  | Creates test messages|
                  +----------+-----------+
                             |
                             |
                    CanMessage structure
                             |
                             v
                  +----------------------+
                  |   can_simulator.c    |
                  |                      |
                  |  send_message()      |
                  |  receive_message()   |
                  +----------+-----------+
                             |
                +------------+------------+
                |            |            |
                v            v            v
          +-----------+ +-----------+ +-----------+
          | Engine ECU| | Brake ECU | | Unknown ID|
          |  0x100    | |  0x200    | |  0x555    |
          +-----------+ +-----------+ +-----------+

