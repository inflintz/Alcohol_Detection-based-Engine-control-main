# Alcohol Detection-based Engine Control

This project is an embedded system designed to detect the presence of alcohol using a gas sensor and provide a visual indication along with an LCD readout. In a complete application, this logic can be extended to control a relay that disables a vehicle's engine if alcohol is detected.

## Features
- **Alcohol Detection:** Uses an MQ-series gas sensor (defined as MQ05 in the code, typical for gas/alcohol sensing) to detect alcohol levels.
- **Visual Display:** Interfaces with a 16x2 Text LCD to show the current status ("Alcohol Detected" or "No Alcohol").
- **Alert Indicator:** Toggles an LED (or a relay for engine control) based on the sensor's input.
- **Microcontroller:** Built for the 8051 microcontroller architecture.

## Hardware Components
- 8051 Microcontroller (e.g., AT89C51/AT89S52)
- MQ-Series Gas/Alcohol Sensor (Output connected to `P1.0`)
- 16x2 LCD Display 
  - Data pins connected to Port 0 (`P0`)
  - Control pins connected to Port 3: `RS` (`P3.0`), `RW` (`P3.1`), `EN` (`P3.2`)
- LED / Relay Module (Connected to `P3.5`)

## Software / Tools
- **Language:** Embedded C
- **IDE / Compiler:** Keil µVision (`.uvproj`, `.uvopt` files are included)

## Circuit Logic & Working
1. The 8051 microcontroller continuously polls the output of the gas sensor on pin `P1.0`.
2. The gas sensor module is expected to output a `LOW` (0) signal when alcohol is detected.
3. If alcohol is detected (`MQ05 == 0`):
   - The LED on pin `P3.5` is turned `ON`.
   - The LCD displays **"Alcohol Detected"**.
   - *(In engine control scenarios, `P3.5` would trigger a relay to disconnect the ignition circuit.)*
4. If no alcohol is detected (`MQ05 == 1`):
   - The LED on pin `P3.5` is turned `OFF`.
   - The LCD displays **"No Alcohol"**.

## Project Structure
- `alcoholcode.c`: The main C source code file containing the microcontroller logic.
- `STARTUP.A51`: Assembly startup code for the 8051 microcontroller.
- `alcohol.uvproj` / `alcohol.uvopt`: Keil µVision project files.
- `Reference Circuit.png`: Diagram showing the basic circuit connections.

## How to Build
1. Open Keil µVision.
2. Open the existing project file `alcohol.uvproj`.
3. Build the target (F7).
4. Flash the generated `.hex` file (if configured) onto your 8051 microcontroller using a compatible programmer.
