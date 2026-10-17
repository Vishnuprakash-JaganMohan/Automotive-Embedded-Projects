# ECU Software Architecture

## Overview

The Automotive ECU Simulator uses a modular C11 software architecture.

## Modules

### ecu.h
Defines ECU data structures, operating states, diagnostic codes, and function declarations.

### ecu.c
Implements ECU initialization, input validation, control logic, state management, RPM calculation, and diagnostic reporting.

### main.c
Provides an interactive terminal interface for configuring simulated inputs and observing ECU outputs.

### test_ecu.c
Contains unit tests for selected normal and fault conditions.

## ECU Operating States

- OFF
- RUNNING
- FAULT

## Simulated Inputs

- Throttle position
- Temperature
- Ignition status
- Brake status

## Simulated Outputs

- Engine RPM
- ECU state
- Diagnostic code
- Overtemperature status
- Control-cycle count

## Limitations

This project is an educational PC-based simulator. It does not communicate with a physical ECU or implement production automotive safety functions.
