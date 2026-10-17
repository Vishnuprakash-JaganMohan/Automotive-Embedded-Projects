# Automotive ECU Simulator | Embedded C

<p align="center">
  <strong>A Modular Automotive ECU Simulation Using C11</strong>
  <br>
  Exploring embedded control logic, ECU state management,
  sensor validation, fault handling, and unit testing.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C11-blue?style=for-the-badge&logo=c" alt="C11">
  <img src="https://img.shields.io/badge/Platform-Windows-lightgrey?style=for-the-badge&logo=windows" alt="Windows">
  <img src="https://img.shields.io/badge/Compiler-GCC-orange?style=for-the-badge&logo=gnu" alt="GCC">
  <img src="https://img.shields.io/badge/Testing-Unit%20Tests-success?style=for-the-badge" alt="Unit Testing">
  <img src="https://img.shields.io/badge/Status-%20Completed-green?style=for-the-badge" alt="Completed">
</p>

---

## Overview

This project implements a PC-based **Automotive Electronic Control Unit (ECU) Simulator** using standard C11.

The simulator reproduces selected ECU behaviours through software-generated sensor inputs, control logic, operating-state management, and diagnostic fault reporting.

It provides an interactive terminal interface for changing simulated vehicle inputs and observing the ECU's response.

The project is designed to explore the fundamentals of automotive embedded software development, with an emphasis on modular C programming, input validation, state-based control logic, and unit testing.

> **Project scope:** This is an educational software simulator. It is not connected to a real vehicle, does not implement a complete engine control strategy, and is not intended for safety-critical or production automotive use.

---

## Objectives

- Develop modular embedded-style software using C11.
- Implement an ECU operating-state model.
- Simulate throttle, temperature, ignition, and brake inputs.
- Validate simulated sensor values.
- Calculate a simplified engine RPM output.
- Detect invalid inputs and simulated overtemperature conditions.
- Report diagnostic fault codes.
- Verify ECU behaviour through automated unit tests.
- Establish a foundation for future automotive communication and microcontroller integration.

---

## System Architecture

```text
             User / Terminal Commands
                       |
                       v
              +------------------+
              |     main.c       |
              | Command Interface|
              +------------------+
                       |
                       v
              +------------------+
              |      ecu.c       |
              |   ECU Control    |
              +------------------+
                       |
          +------------+-------------+
          |            |             |
          v            v             v
     Input         State         Fault
    Validation   Management     Detection
          |            |             |
          +------------+-------------+
                       |
                       v
              +------------------+
              |   ECU Outputs    |
              | RPM / State / DTC|
              +------------------+
                       |
                       v
                 Terminal Output
