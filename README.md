<div align="center">

# 🚗 Automotive Embedded Projects

**Simulation-based projects in ECU control, vehicle communication, diagnostics and fault handling**

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/C++-00427E?style=for-the-badge&logo=cplusplus&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white)

![Status](https://img.shields.io/badge/status-in%20planning-F5A623?style=flat-square)
![Domain](https://img.shields.io/badge/domain-automotive%20embedded-0A9396?style=flat-square)
![Focus](https://img.shields.io/badge/focus-CAN%20%7C%20ECU%20%7C%20diagnostics-005F73?style=flat-square)
![License](https://img.shields.io/badge/license-MIT-2D9C5A?style=flat-square)

[Overview](#-overview) · [Projects](#-projects) · [Architecture](#-planned-architecture) · [Roadmap](#-roadmap) · [Getting Started](#-getting-started) · [Contact](#-contact)

</div>

---

## 🎯 Overview

Modern vehicles are networks of electronic control units (ECUs) exchanging signals over in-vehicle buses. This repository explores the software side of that world through simulation projects that run on a development machine, with the aim of porting selected parts to microcontroller targets later.

| | |
|---|---|
| 🎓 **Goal** | Build practical skills in ECU logic, CAN communication, diagnostics and fault handling |
| 🧪 **Method** | Requirements, design, implementation and automated tests for every project |
| 📦 **Format** | Self-contained projects, each with its own README, build steps and test results |
| ⚠️ **Scope** | Learning simulations. Not production software and not safety-certified |

---

## 👤 Author

**Vishnuprakash Jagan Mohan** · M.Sc. Embedded Systems, TU Chemnitz, Germany

Over four years of industrial R&D experience in embedded hardware, firmware and microcontroller-based control systems, including PCB design, Embedded C, CAN / RS485 / Modbus RTU communication and hardware-software integration. This repository extends that background into automotive embedded software.

---

## 🛠️ Projects

| # | Project | Focus | Topics | Status |
|:-:|---------|-------|--------|:------:|
| 1 | 🔵 [ECU Simulator](#-1-automotive-ecu-simulator) | Control logic | Sensor inputs, state machines, actuator outputs | ![Planned](https://img.shields.io/badge/-Planned-F5A623?style=flat-square) |
| 2 | 🟢 [Communication Simulator](#-2-automotive-communication-simulator) | Networking | CAN frames, message handling between virtual ECUs | ![Planned](https://img.shields.io/badge/-Planned-F5A623?style=flat-square) |
| 3 | 🟣 [Diagnostic Engine](#-3-ecu-diagnostic-engine) | Diagnostics | Fault identification, trouble codes, event logging | ![Planned](https://img.shields.io/badge/-Planned-F5A623?style=flat-square) |
| 4 | 🟠 [Sensor Monitor](#-4-vehicle-sensor-monitor) | Signal handling | Thresholds, plausibility checks, visualization | ![Planned](https://img.shields.io/badge/-Planned-F5A623?style=flat-square) |
| 5 | 🔴 [Fault Detection System](#-5-ecu-fault-detection-system) | Robustness | Fault injection, timeouts, safe states | ![Planned](https://img.shields.io/badge/-Planned-F5A623?style=flat-square) |

> Status values: **Planned**, **In Progress**, **Complete**. The table is updated as work is committed.

### 🔵 1. Automotive ECU Simulator
A software ECU model that reads simulated sensor inputs, tracks operating states and drives simulated actuator outputs.
- **Objectives:** explicit state machine for operating modes; separate input, logic and output modules; deterministic, testable behavior
- **Deliverables:** source code, state diagram, requirements list, unit tests, usage docs
- **Tech:** `Embedded-style C` `State machines` `Automated tests`

### 🟢 2. Automotive Communication Simulator
A simulation of message exchange between virtual ECUs using CAN concepts.
- **Objectives:** message and signal definitions; frame packing and unpacking; handling of malformed or missing messages
- **Deliverables:** message definition file, communication module, test cases, example bus-traffic logs
- **Tech:** `C / C++` `CAN concepts` `Message processing`

### 🟣 3. ECU Diagnostic Engine
A diagnostic simulation covering how an ECU detects, records and reports abnormal conditions.
- **Objectives:** defined fault conditions; diagnostic trouble codes with status; inspectable event log
- **Deliverables:** fault catalog, diagnostic module, test scenarios, example logs
- **Tech:** `C` `Diagnostics` `Fault handling`

### 🟠 4. Vehicle Sensor Monitor
A monitor for virtual vehicle signals with validation and visualization.
- **Objectives:** threshold detection; range and plausibility checks; signal plots over time
- **Deliverables:** monitoring module, validation rules, plotting scripts, sample datasets
- **Tech:** `C / C++` `Python` `Signal processing basics`

### 🔴 5. ECU Fault Detection System
A fault-handling study built around fault injection and defined safe behavior.
- **Objectives:** inject signal loss and communication timeouts; measure detection time and reaction; define and test a safe state
- **Deliverables:** fault injection harness, fault-reaction logic, test report
- **Tech:** `Embedded-style C` `Fault detection` `Structured testing`

---

## 🧭 Planned Architecture

How the projects are intended to fit together (planned design, not yet implemented):

```mermaid
flowchart LR
    S[Sensor Inputs<br/>simulated] --> E1[ECU Simulator<br/>state machine]
    E1 -->|CAN frames| B((Virtual CAN Bus))
    B --> E2[Peer ECU<br/>virtual]
    E1 --> A[Actuator Outputs<br/>simulated]
    E1 --> D[Diagnostic Engine<br/>DTCs + event log]
    F[Fault Injection<br/>timeouts, signal loss] -.-> S
    F -.-> B
    D --> M[Sensor Monitor<br/>plots + validation]

    style S fill:#E0F2F1,stroke:#0A9396,color:#003B3B
    style E1 fill:#DCEBFA,stroke:#005F73,color:#0B2F4A
    style B fill:#FFF3D6,stroke:#F5A623,color:#5A3A00
    style E2 fill:#DCEBFA,stroke:#005F73,color:#0B2F4A
    style A fill:#E0F2F1,stroke:#0A9396,color:#003B3B
    style D fill:#EADCF8,stroke:#7B2CBF,color:#2E1252
    style F fill:#FBE0E0,stroke:#C0392B,color:#5A1010
    style M fill:#FFE8D6,stroke:#E67E22,color:#5A2A00
```

### Development workflow

```mermaid
flowchart LR
    R[Requirements] --> D[Design] --> I[Implementation] --> T[Testing] --> G[Debugging] --> V[Review]
    V -.->|iterate| R

    style R fill:#DCEBFA,stroke:#005F73,color:#0B2F4A
    style D fill:#E0F2F1,stroke:#0A9396,color:#003B3B
    style I fill:#EADCF8,stroke:#7B2CBF,color:#2E1252
    style T fill:#FFF3D6,stroke:#F5A623,color:#5A3A00
    style G fill:#FBE0E0,stroke:#C0392B,color:#5A1010
    style V fill:#E3F4E8,stroke:#2D9C5A,color:#0F3B22
```

**Working principles**

- ✅ **Requirements first:** every project starts with a short list of testable requirements
- 🧩 **Separation of concerns:** input handling, logic and output handling live in separate modules
- 🧪 **Test as you build:** normal behavior and edge cases (invalid inputs, timeouts, boundaries) are automated
- 🔗 **Traceability:** tests reference the requirements they verify
- 📏 **Coding standards:** MISRA C is the reference target where practical; compliance is not claimed unless checked with tooling and documented
- 📝 **Documentation:** assumptions, limitations and results are recorded per project

---

## 🧰 Technology Stack

| Area | Tools and Concepts |
|------|--------------------|
| 💻 Languages | C, C++, Python |
| 🔨 Build | GCC, CMake |
| 🌿 Version control | Git, GitHub |
| 🚘 Domain concepts | ECU architecture, CAN, state machines, diagnostics, fault handling, real-time fundamentals |
| 🔧 Background tools | Altium Designer, STM32 tooling, B&R Automation Studio, MATLAB, LabVIEW |

Each project lists its exact tools and versions in its own README.

---

## 📁 Repository Structure

Target layout once projects are added:

```text
Automotive-Embedded-Projects/
├── README.md
├── LICENSE
├── docs/                       # shared notes and design references
├── 01-ecu-simulator/
│   ├── README.md               # overview, build and test instructions
│   ├── src/
│   ├── include/
│   ├── tests/
│   ├── docs/                   # requirements, diagrams, test results
│   └── CMakeLists.txt
├── 02-communication-simulator/
├── 03-diagnostic-engine/
├── 04-sensor-monitor/
└── 05-fault-detection/
```

---

## 🗺️ Roadmap

| Phase | Objective | Status |
|:-----:|-----------|:------:|
| 1 | Strengthen Embedded C and C++ fundamentals | ![Ongoing](https://img.shields.io/badge/-Ongoing-0A9396?style=flat-square) |
| 2 | Develop the automotive ECU simulator | ![Planned](https://img.shields.io/badge/-Planned-F5A623?style=flat-square) |
| 3 | Add CAN-based communication between virtual ECUs | ![Planned](https://img.shields.io/badge/-Planned-F5A623?style=flat-square) |
| 4 | Implement diagnostics and fault handling | ![Planned](https://img.shields.io/badge/-Planned-F5A623?style=flat-square) |
| 5 | Build automated testing workflows (unit tests, CI) | ![Planned](https://img.shields.io/badge/-Planned-F5A623?style=flat-square) |
| 6 | Study AUTOSAR concepts and software architecture | ![Planned](https://img.shields.io/badge/-Planned-F5A623?style=flat-square) |
| 7 | Extend to advanced projects, including microcontroller targets | ![Planned](https://img.shields.io/badge/-Planned-F5A623?style=flat-square) |

---

## 🚀 Getting Started

Project code is added incrementally. The steps below describe the intended workflow and will be confirmed per project as each one is published.

**Prerequisites:** Git · GCC or compatible C/C++ compiler · CMake 3.15+ · Python 3.9+ (where visualization scripts are used)

```bash
# Clone
git clone https://github.com/Vishnuprakash-JaganMohan/Automotive-Embedded-Projects.git
cd Automotive-Embedded-Projects

# Build and test a project (template; see each project's README)
cd 01-ecu-simulator
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

---

## 🤝 Contributing and Feedback

This is a personal learning repository, but technical feedback is welcome. Please open an issue with the project and file concerned, what you observed, and what you would suggest instead. For pull requests, please open an issue first to discuss the change.

---

## 📄 License

Released under the MIT License. See [LICENSE](LICENSE) for details.

---

## 📬 Contact

<div align="center">

**Vishnuprakash Jagan Mohan** · Chemnitz, Germany

[![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/Vishnuprakash-JaganMohan)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/YOUR-PROFILE)
[![Email](https://img.shields.io/badge/Email-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:YOUR-EMAIL)

</div>
