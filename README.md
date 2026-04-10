# 🕹️ Shooter PacMan & Hardware Joystick Control

This project consists of two main parts: a modern, action-packed twist on the classic **PacMan** game and a custom **Hardware Joystick** implementation to control it.

---

## 🎮 Part 1: Shooter PacMan (Software)
**Repository:** [Shooter_PacMan_Aoft](https://github.com/alireza928/Shooter_PacMan_Aoft)

In this version, PacMan is no longer the victim. He is armed and ready to fight back!

### Features
* **Combat Mechanics:** Shoot at ghosts to neutralize them.
* **Classic Maze:** Enhanced arcade gameplay with modern shooter elements.
* **Dynamic AI:** Ghosts with strategic movement patterns.
* **Score System:** Track your performance as you clear the maze.

---

## 🕹️ Part 2: Joystick Controller (Hardware)
**Repository:** [Joystick](https://github.com/alireza928/Joystick)

A custom hardware integration designed to provide a real arcade feel using an Arduino-based joystick module.

### Technical Details
* **Analog Input:** Uses X and Y axis potentiometers for precise movement.
* **Digital Trigger:** The joystick's push-button (Z-axis) is used for shooting.
* **Microcontroller:** Optimized for Arduino (Uno/Nano) interfacing.
* **Connectivity:** Simple 5-pin configuration (VCC, GND, VRx, VRy, SW).

---

## 🚀 Getting Started

### 1. Hardware Setup (Joystick)
Connect your joystick to your Arduino as follows:
* **GND** → GND
* **+5V** → 5V
* **VRx** → Analog Pin (e.g., A0)
* **VRy** → Analog Pin (e.g., A1)
* **SW** → Digital Pin (e.g., D2)

### 2. Software Installation
1.  **Clone the repositories:**
    ```bash
    git clone [https://github.com/alireza928/Shooter_PacMan_Aoft.git](https://github.com/alireza928/Shooter_PacMan_Aoft.git)
    git clone [https://github.com/alireza928/Joystick.git](https://github.com/alireza928/Joystick.git)
    ```
2.  **Flash the Arduino:** Upload the code from the Joystick repository to your board.
3.  **Run the Game:** Open the Shooter PacMan project in your IDE and start the application.

---

## 🏗 Architecture
This project utilizes a modular approach:
* **Hardware Layer:** Translates physical movement into data signals.
* **Communication Layer:** Sends joystick coordinates to the game engine.
* **Logic Layer (MVC):** Processes game rules, collisions, and rendering.

---

## 📄 License
This project is licensed under the MIT License.

---

**Developed by [Alireza928](https://github.com/alireza928)**
