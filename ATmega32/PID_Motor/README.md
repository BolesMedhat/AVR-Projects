# PID Motor Control System - ATmega32 Implementation

## 🎯 Overview
A real-time PID control system for DC motor position control implemented on ATmega32 microcontroller featuring:
- Dual-mode operation (Digital/Analog)
- Real-time tuning via UART or potentiometers
- PWM motor control with direction management
- Visual feedback via DAC output

---

## ⚙️ System Features

### Control Modes
- **Digital Mode**:
  - UART-based PID parameter input
  - Manual setpoint entry
  - Real-time error monitoring

- **Analog Mode**:
  - Autonomous operation
  - Potentiometer-adjusted gains
  - Continuous status reporting

### Interrupt-Driven Architecture
- **Timer2 ISR**: Triggers every 20ms (50Hz) for deterministic timing
  - Maintains fixed sampling interval regardless of main loop activity
  - Calls `PID_Update()` for control computation
  - Automatic timer reload ensures consistent periodicity

### Main Loop Responsibilities:
- **User I/O Handling**: UART communication and monitoring
- **System Monitoring**: Status reporting and setpoint management
- **Non-Time-Critical Tasks**: Configuration changes and diagnostics

---

## 📋 Code Architecture
1. **APP_Init()**
   - Peripherals initialization (UART, ADC, Timers)
   - Mode selection (5s timeout)
   - PID parameter setup

2. **PID_Update()**
   - Position feedback reading
   - Error calculation
   - PID computation
   - Motor output generation

3. **Control_ISR()**
   - Timer2-based periodic control
   - Maintains consistent sampling rate

4. **APP_main_loop()**
   - User interaction handling
   - System status reporting
   - Setpoint management

---

## 🔧 Configuration

### Key Parameters (`APP_config.h`)
```c
#define KP_MAX          5     // Max proportional gain
#define KI_MAX          1     // Max integral gain
#define KD_MAX          1     // Max derivative gain
#define SAMPLE_MS       20    // Control loop period
#define DEADBAND        5     // Error deadzone threshold
```

---

## 🏗️ Hardware Setup
- **ATmega32 microcontroller** (16MHz)
- **DC motor** with H-bridge driver
- **5 potentiometers** (feedback, setpoint, Kp/Ki/Kd)
- **UART interface** (for digital mode)
- **R-2R ladder DAC** (optional visualization)

---

## 📜 License
MIT License - Free for educational and personal use

---

## 👨‍💻 Author

**Poles Medhat** – Embedded Systems Developer
**Contact**:  
[LinkedIn](https://www.linkedin.com/in/boles-medhat)

---
