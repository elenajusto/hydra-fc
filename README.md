# Hydra Flight Computer

## Project Overview
### Minimum Viable Concept (MVC) Features:
1. Altitude Estimation
2. Dual Deployment
3. Data Logging

### Planned Major Iterations:
- V1: Achieve Basic MVC
- V2: MVC + Telemetry and GPS
- V3: MVC + Telemetry and GPS + Video Feed

## To Do List

### Software
- [ ] Learn sensor fusion
- [ ] Learn kalman filtering
- [ ] Filter IMU and Barometer readout
- [ ] Fuse IMU and Barometer readout
- [ ] Estimate rocket pose

### Electrical
- [ ] **INVESTIGATE:** Voltage Regulator - Capacitors meant to be in series instead of parallel.
- [ ] **QUESTION:** Has to interface with Joe's PCB (Tracker).
- [ ] **ISSUE:** Update fly back diode to different name (in the firing part) (Voltage protection thing).
- [ ] **INVESTIGATE:** Does USB-C connect via JTAG/ST-LINK to MCU or are they seperate?
- [ ] **ISSUE: I**indicators - LED
- [ ] **SUGGESTION:** Drive buzzer with a transistor or MOSFET to supply more current versus just going from the IO pins.
- [ ] **INFO ONLY:** Could use one decoupling capacitor if VDD pins were next to each other.
- [ ] **SUGGESTION:** Net labels for I2C and SPI instead of Bus Lines.
- [ ] **INVESTIGATE:** Decoupling capacitors for sensor components.
- [ ] **ISSUE:** Continuity testing for pyrotechnic channels.
- [ ] **INVESTIGATE:** Simulate the pyrotechnic channels.
- [ ] **ISSUE:** Not enough voltage for pyrotechnic channels (expected 0.5 to 1A current).
- [ ] **ISSUE:** Battery connector -> Remove the +5V symbols. Rename.
- [ ] **INVESTIGATE:** MOSFET turns on at +3.3V.
- [ ] **OTHER:** Clean schematic

## Achieve Basic MVC (v1)

### Schematic Draft 1

#### MCU
![image](https://github.com/user-attachments/assets/71e538f5-2c2c-45b5-b931-c62fb47d806f)

#### Power
![image](https://github.com/user-attachments/assets/d0687ab8-0100-4bc4-a931-971549e5f13b)

#### Peripherals
![image](https://github.com/user-attachments/assets/5f05c6f8-0901-483f-8ad9-0f1ccb8f340e)

#### Pyrotech
![image](https://github.com/user-attachments/assets/9505ffbd-1364-4005-b4e1-ca8460528ac2)

### Breadboard Prototype v1.1

#### Block Diagram
![image](https://github.com/user-attachments/assets/51bd0848-5fb7-4b26-a7a0-a43811c4bb36)

#### Serial Output
![image](https://github.com/user-attachments/assets/18f54629-b74a-4086-9311-96f9ce86077a)

#### Stationary Sensor Readout
![image](https://github.com/user-attachments/assets/16077b3a-ba7b-4dec-b253-1d564a5cbece)

#### Physical Setup
![image](https://github.com/user-attachments/assets/a78cfd2f-710b-43f6-b6cc-e33092d11337)
