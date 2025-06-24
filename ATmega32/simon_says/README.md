# Simon Says Game - ATmega32 Implementation

## 🎮 Overview
A classic Simon Says memory game implemented on ATmega32 microcontroller featuring:
- 4-color LED sequence generation
- Button input validation
- Progressive difficulty levels
- LCD feedback and scoring

---

## ⚙️ Game Features
- 🔵🟡🟢🔴 Color sequence memorization
- 📈 Progressive difficulty
- ✅ Input validation with debouncing
- 🎯 Score tracking via LCD

---

## 📋 Code Structure

1. **APP_Init()**
   - Initializes peripherals (ADC, LCD, buttons, LEDs)
   - Seeds random number generator using floating ADC pin

2. **DisplayCommands()**
   - Shows the sequence using LEDs
   - 900ms ON / 100ms OFF timing

3. **CheckCommands()**
   - Validates player input against sequence
   - Implements button debouncing
   - Handles single/multiple button presses

4. **APP_main_loop()**
   - Manages game progression
   - Generates random sequences
   - Provides motivational messages
   - Handles level advancement

---

## 🕹️ Game Flow

1. System displays color sequence
2. Player repeats sequence via buttons
3. Correct answer → Level up + new sequence
4. Wrong answer → Game over + reset
5. Max level (50) → Celebration + reset

---

## Components Used
- **ATmega32 microcontroller** (16MHz)
- **4 LEDs** (Blue, Yellow, Green, Red)
- **4 push buttons** (color-matched to LEDs)
- **16x2 LCD display** for game feedback
- **ADC channel** for random seed generation

---

## 📜 License
MIT License - Free for educational and personal use

---

## 👨‍💻 Author

**Poles Medhat** – Embedded Systems Developer
**Contact**:  
[LinkedIn](https://www.linkedin.com/in/boles-medhat) | 
[GitHub](https://github.com/BolesMedhat)

---

