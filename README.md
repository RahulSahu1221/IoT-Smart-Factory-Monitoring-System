# Smart Factory IoT Monitoring System

An Industrial Internet of Things (IIoT) project that simulates a smart factory environment using **Arduino Uno**, **PICSimLab**, **MQTT**, and **ThingsBoard Cloud**. The system consists of two distributed embedded nodes that monitor production and warehouse environments, publish real-time telemetry to the cloud, support remote device control through RPC, and provide live dashboards for visualization and monitoring.

---

## Table of Contents

- [Project Overview](#project-overview)
- [Key Features](#key-features)
- [System Architecture](#system-architecture)
- [Hardware Architecture](#hardware-architecture)
- [Software Architecture](#software-architecture)
- [ThingsBoard Dashboards](#thingsboard-dashboards)
- [Repository Structure](#repository-structure)
- [Technologies Used](#technologies-used)
- [Telemetry Parameters](#telemetry-parameters)
- [MQTT Communication](#mqtt-communication)
- [Remote Procedure Calls (RPC)](#remote-procedure-calls-rpc)
- [Getting Started](#getting-started)
- [Running the Simulation](#running-the-simulation)
- [Testing](#testing)
- [Future Improvements](#future-improvements)
- [Author](#author)

---

# Project Overview

Modern manufacturing industries increasingly rely on Industrial Internet of Things (IIoT) technologies to improve operational efficiency, predictive maintenance, and real-time monitoring.

This project demonstrates a complete smart factory monitoring solution where two independent embedded nodes continuously collect environmental and operational data and transmit it to **ThingsBoard Cloud** over **MQTT**.

The complete system has been developed using **Arduino Uno**, simulated entirely in **PICSimLab**, eliminating the need for physical hardware while maintaining the functionality of an actual industrial monitoring system.

---

# Key Features

## Production Line (Node 1)

- Air Temperature Monitoring
- Surface Temperature Monitoring (LM35)
- Humidity Monitoring
- Machine Status Detection
- Vibration Monitoring
- Production Relay Control
- Sensor Fault Detection
- Remote Relay Control using RPC

---

## Warehouse (Node 2)

- Temperature Monitoring
- Humidity Monitoring
- Ambient Light Detection (LDR)
- Motion Detection (PIR)
- Door Status Monitoring
- Automatic Ventilation
- Remote Relay Override
- Sensor Error Detection

---

## Cloud Features

- Real-Time Telemetry
- Historical Data Storage
- Interactive Dashboards
- Time-Series Charts
- Remote Device Control
- Alarm Generation
- Device Status Monitoring
- RPC Communication

---

# System Architecture

```
                        ThingsBoard Cloud
                   (MQTT Broker + Dashboard)
                              │
                 MQTT Telemetry / RPC Commands
                              │
        ┌─────────────────────┴─────────────────────┐
        │                                           │
        │                                           │
 ┌───────────────┐                         ┌───────────────┐
 │ Production    │                         │ Warehouse     │
 │ Line Node     │                         │ Node          │
 │ Arduino Uno   │                         │ Arduino Uno   │
 └───────────────┘                         └───────────────┘
        │                                           │
        │                                           │
 DHT22 Temperature                         DHT22 Temperature
 LM35 Temperature                          LDR Sensor
 Vibration Sensor                          PIR Motion Sensor
 Machine Button                            Reed Switch
 Relay                                     Ventilation Relay
 LEDs                                      LEDs

```

---

# Hardware Architecture

## Node 1 – Production Line

| Component               | Purpose                 |
|-------------------------|-------------------------|
| Arduino Uno             | Main Controller         |
| DHT22                   | Temperature & Humidity  |
| LM35                    | Surface Temperature     |
| Potentiometer           | Vibration Simulation    |
| Push Button             | Machine Status          |
| Relay                   | Production Control      |
| LEDs                    | Status Indicators       |

---

## Node 2 – Warehouse

| Component               | Purpose                 |
|-------------------------|-------------------------|
| Arduino Uno             | Main Controller         |
| DHT22                   | Temperature & Humidity  |
| LDR                     | Ambient Light           |
| PIR Sensor              | Motion Detection        |
| Reed Switch             | Door Status             |
| Relay                   | Ventilation Control     |
| LEDs                    | Status Indicators |

---

# Software Architecture

The project follows a modular software architecture.

```
NODE1/
│
├── config
├── SensorManager
├── ActuatorManager
├── NetworkManager
├── TelemetryManager
├── RPCHandler
└── NODE1.ino

NODE2/
│
├── config
├── SensorManager
├── ActuatorManager
├── NetworkManager
├── TelemetryManager
├── RPCHandler
└── NODE2.ino
```

Each module is responsible for a single functionality, making the project easy to maintain and extend.

---

# ThingsBoard Dashboards

The project contains three ThingsBoard dashboards.

## 1. Smart Factory Dashboard

Provides a centralized overview of both nodes.

Displays:

- Production Line Data
- Warehouse Data
- Combined Factory Status
- Historical Temperature Trends

---

## 2. Production Line Dashboard

Displays

- Temperature Gauge
- Surface Temperature Gauge
- Humidity Gauge
- Machine Status
- Relay Status
- Sensor Error Status
- Relay RPC Switch
- Time-Series Charts

---

## 3. Warehouse Dashboard

Displays

- Temperature
- Humidity
- LDR Value
- Motion Detection
- Door Status
- Ventilation Relay
- Relay RPC Switch
- Historical Humidity Graph

---

# Repository Structure

```
Smart-Factory-IoT-Monitoring-System
│
├── NODE1/
│
├── NODE2/
│
├── Production_Line.pzw
├── Warehouse.pzw
│
├── Smart Factory IoT Monitoring System.pdf
├── Smart_Factory_IoT_Requirements_Design.pdf
│
├── README.md
│
└── screenshots/
```

---

# Technologies Used

| Category | Technology |
|-----------|------------|
| Programming Language | C++ |
| IDE | Arduino IDE |
| Simulator | PICSimLab |
| Cloud Platform | ThingsBoard Cloud |
| Communication | MQTT |
| Network | Ethernet |
| Version Control | Git & GitHub |

---

# Telemetry Parameters

## Production Line

- temperature
- humidity
- lm35Temp
- vibration
- machineStatus
- relayState
- sensorError
- uptime

---

## Warehouse

- temperature
- humidity
- ldrValue
- isDark
- motionDetected
- doorOpen
- relayState
- sensorError
- uptime

---

# MQTT Communication

Telemetry is published every **5 seconds** to ThingsBoard Cloud using MQTT.

### Publish Topic

```
v1/devices/me/telemetry
```

### RPC Topic

```
v1/devices/me/rpc/request/+
```

### Attribute Topic

```
v1/devices/me/attributes
```

---

# Remote Procedure Calls (RPC)

Supported RPC commands:

| Method | Description |
|----------|-------------|
| setRelay | Turns relay ON/OFF |
| setLED | Controls individual LEDs |
| getStatus | Returns current device status |

---

# Getting Started

## Requirements

- Arduino IDE
- PICSimLab
- Internet Connection
- ThingsBoard Cloud Account

---

## Clone Repository

```bash
git clone https://github.com/RahulSahu1221/IoT-Smart-Factory-Monitoring-System.git
```

---

## Compile

Open

```
NODE1/NODE1.ino
```

or

```
NODE2/NODE2.ino
```

Compile using Arduino IDE.

---

# Running the Simulation

1. Open PICSimLab.
2. Load `Production_Line.pzw` or `Warehouse.pzw`.
3. Export the compiled firmware (`.hex`) from Arduino IDE.
4. Load the firmware into the simulated Arduino Uno.
5. Start the simulation.
6. Open ThingsBoard Cloud.
7. Observe live telemetry, dashboards, and RPC communication.

---

# Testing

The system has been tested for:

- Sensor Integration
- MQTT Connectivity
- Dashboard Updates
- Relay RPC Commands
- Auto Ventilation Logic
- Alarm Generation
- Node Communication
- Sensor Error Handling

---

# Future Improvements

- ESP32 Wi-Fi Support
- OTA Firmware Updates
- Predictive Maintenance
- Cloud Database Integration
- Mobile Dashboard
- Multi-Factory Support
- AI-Based Fault Detection
- PLC Integration
- Edge Computing
- Digital Twin Implementation

---

# Documentation

The repository includes the complete project report and requirements/design document describing the system architecture, telemetry model, dashboard layout, communication protocol, alarm logic, and testing methodology. :contentReference[oaicite:1]{index=1}

---

# Author

**Rahul Sahu**

Electrical & Electronics Engineering

### Areas of Interest

- Embedded Systems
- Industrial IoT
- Robotics
- Automation
- Industry 4.0
- Smart Manufacturing

GitHub: https://github.com/RahulSahu1221

---

## Acknowledgements

This project was developed as part of an Embedded Systems and Industrial IoT learning program using Arduino, PICSimLab, MQTT, and ThingsBoard Cloud to demonstrate a realistic smart factory monitoring solution.

---

## License

This project is intended for educational and demonstration purposes.
