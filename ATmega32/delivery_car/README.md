# Delivery Car System - ATmega32

## 🏆 Award-Winning Project
**1st Place Winner** at IEEE ComSoc Hackathon - Modifier 8.0 Embedded Systems

---

## Overview
A smart remote-controlled delivery car system featuring autonomous return functionality, obstacle detection, and secure package delivery.

---

## Key Features

### 🎮 Mobile Remote Control (Bluetooth):
- Simple button-based operation via custom mobile application
- No complex commands needed - just press and go

### 🔄 Smart Autonomous Return:
- Automatically returns to starting point if connection is lost
- Can also be triggered manually via app button

### 📦 Secure Package Delivery:
- Password-protected delivery box using servo mechanism
- 4-digit keypad entry for secure access
- Password change functionality
- EEPROM storage for password persistence
- Visual feedback via LCD screen

### 🛡️ Obstacle Detection:
  - Front and rear ultrasonic sensors detect obstacles
  - Automatic stopping when obstacles are too close
  - Resume movement when path is clear

### 💬 Customer Communication:
- Operator can send messages to customer via LCD display
- 4x4 keypad for password input
- Audio feedback via buzzer

### 💰 Cost-Effective Design
- Custom car body designed in AutoCAD for perfect fit and cost savings
- Optimized component selection

---

## Usage Instructions

### 1. **Initial Setup**:
   - **On first boot**, set a 4-digit password using the keypad
   - Password is stored in EEPROM for future use

### **2. Mobile App Commands**  
  | Command | Action |  
  |---------|--------|  
  | `1` | Move Forward |  
  | `2` | Move Backward |  
  | `3` | Stop |  
  | `4` | Steer Right |  
  | `5` | Steer Left |  
  | `6` | Gear Up |  
  | `7` | Gear Down |  
  | `8` | Clear LCD |  
  | `9` | Send LCD Message |  
  | `;` | Reverse Path Replay |  
  | `o` | Buzzer ON |  
  | `f` | Buzzer OFF |

### **3. Password Operations**  
   - **Press any key** (except '*') to enter password and open package box
   - **Press '*'** to change password (requires old password)

### **4. Safety Features**  
- **Path replay** if connection lost.  
- **Auto-stop** if obstacle detected (<10cm). 

---

## Components Used
- ATmega32 microcontroller
- HC-05 Bluetooth module
- DC Motors (x4) with H-bridge driver
- HC-SR04 Ultrasonic Sensors (x2)
- LCD Display
- 4x4 Keypad
- Servo Motor (for package delivery mechanism)
- Buzzer
- Lithium Batteries (x3)

---

## License
This project is open-source and available under the MIT License.

---

## 👨‍💻 Author

**Poles Medhat** – Embedded Systems Developer
**Contact**:  
[LinkedIn](https://www.linkedin.com/in/boles-medhat) | 
[GitHub](https://github.com/BolesMedhat)

---

