# Snake Game - ATmega32 Implementation

## 🎮 Overview
A classic Snake game implemented on ATmega32 microcontroller featuring:
- Dot matrix display rendering via shift registers
- 7-segment score display
- Four-button directional control
- Configurable gameplay options

---

## ⚙️ Game Features

### Core Gameplay
- 🐍 Snake grows when eating fruit
- 🍎 Random fruit generation with collision avoidance
- ⏱️ Progressive speed increase with score
- 🎯 Score tracking (0-99)

### Configuration Options
```c
#define MAP_WIDTH           16    // Game grid width
#define MAP_HEIGHT          16    // Game grid height
#define SNAKE_SPEED_BASE    20    // Initial game speed
```

### Game Modes
- **Wrapping Mode**: Snake appears on opposite side when hitting edges
- **Wall Collision Mode**: Game ends on wall hit (default)

---

## 📋 Code Structure
1. **APP_Init()**
   - Initializes peripherals (ADC, displays, buttons)
   - Seeds random number generator
   - Sets up initial snake and fruit positions

2. **Input_handle()**
   - Reads button inputs
   - Prevents 180-degree turns

3. **Snake_Logic()**
   - Handles movement, growth, and collision
   - Manages fruit generation

4. **Display()**
   - Renders game state on dot matrix
   - Updates 7-segment score display

5. **APP_main_loop()**
   - Core game timing and control flow
   - Implements speed scaling

---

## Game Controls
| Button | Pin | Action |
|--------|-----|--------|
| UP     | PD3 | Move Up |
| DOWN   | PD4 | Move Down |
| LEFT   | PD5 | Move Left |
| RIGHT  | PD6 | Move Right |

---

## Components Used
- **ATmega32 microcontroller** (16MHz)
- **4 8x8 Dot Matrix Display** (driven via shift registers)
- **2-digit 7-segment display** for score
- **4 push buttons** (Up/Down/Left/Right)
- **4 Shift registers** (74HC595) for display multiplexing

---

## 📜 License
MIT License - Free for educational and personal use

---

**Developer**: Boles Medhat  
**Contact**:  
[LinkedIn](https://www.linkedin.com/in/boles-medhat) | 
[GitHub](https://github.com/BolesMedhat)

