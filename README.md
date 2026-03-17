# pcf8574-i2c-bitbang-demo
Implementation of the I2C protocol using bit-banging to control LEDs through the PCF8574 I/O expander and read button inputs in an embedded system environment.


# PCF8574 I2C Bit-Banging LED Controller

This project demonstrates how to control LEDs and read button inputs using the **PCF8574 I/O expander** over the **I2C protocol**.  
Instead of using a built-in library (such as the Arduino `Wire` library), the I2C communication was implemented manually using **bit-banging** to better understand how the protocol works at the signal level.

The goal of this project was to explore how hardware and firmware interact in embedded systems by working directly with device documentation and implementing low-level communication.

---

## Project Overview

The system uses a **PCF8574 I/O expander** connected via I2C to control LEDs and read button inputs.  
The I2C communication is simulated through software by manually toggling the clock and data lines.

This allowed the project to demonstrate:

- Low-level I2C communication
- Interaction with an external I/O expander
- Hardware/software debugging
- Understanding of device datasheets

---

## Hardware Components

- Microcontroller (Arduino or compatible board)
- PCF8574 I/O Expander
- LEDs
- Push Buttons
- Resistors
- Breadboard and jumper wires

---

## Key Concepts Demonstrated

- I2C communication fundamentals
- Bit-banging implementation of I2C
- Reading and interpreting technical datasheets
- Addressing and communication timing
- Bidirectional I/O behavior of the PCF8574
- Hardware debugging and signal timing

---

## How It Works

1. The microcontroller generates the **I2C clock (SCL)** and **data (SDA)** signals using digital pins.
2. The program sends commands to the **PCF8574** using bit-banged I2C communication.
3. The PCF8574 controls the state of LEDs connected to its output pins.
4. Button inputs are read through the PCF8574 and the system responds accordingly.

---

## Challenges Encountered

One of the main challenges in this project was understanding how the **PCF8574 sinks current** and how the LEDs needed to be wired for proper operation.

Another challenge involved implementing **I2C communication without using a library**, which required carefully controlling the timing of the clock and data signals.

Debugging both the circuit wiring and the software timing helped reinforce how **hardware and firmware interact in embedded systems**.

---

## What I Learned

Through this project I learned how to:

- Use technical documentation such as the **PCF8574 datasheet**
- Implement the **I2C protocol manually**
- Debug hardware and firmware interactions
- Understand how external I/O expanders work in embedded systems
- Design circuits that correctly use current sinking outputs

---

## Future Improvements

Potential improvements to this project include:

- Expanding the system to control additional devices through I2C
- Adding interrupt-based input handling
- Optimizing timing for more reliable communication
- Implementing additional embedded peripherals

---

## Author

Created as part of an embedded systems learning project focused on understanding hardware communication and low-level protocol implementation.
