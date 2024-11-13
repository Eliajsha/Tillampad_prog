# Tillampad_prog
 
# Clock and Temperature Project

## Project Overview

This project, created by Elias Svensson on 2024-10-10, is a simple clock and temperature monitoring system. It uses an **RTC DS3231** module to keep track of time and displays the information on a **1306 OLED** display. Additionally, it measures temperature through an analog temperature sensor and displays the corresponding mapped value on a **9g servo motor**. When the temperature exceeds a certain threshold, LEDs flash as a warning.

## Features

- **Time Display**: Uses the DS3231 module to measure and display the current time.
- **Temperature Measurement**: Reads temperature through an analog sensor.
- **Visual Temperature Output**: Maps the temperature to the angle of a 9g servo motor.
- **Temperature Warning System**: Flashes LEDs if the temperature goes above 27°C.
- **OLED Display**: Displays both time and temperature readings.

## Hardware Requirements

- **DS3231 Real-Time Clock Module**
- **1306 OLED Display**
- **Analog Temperature Sensor**
- **9g Servo Motor**
- **4 LEDs** (for temperature warning signal)

## Libraries Used

- **RTClib**: For interfacing with the DS3231 RTC.
- **Wire**: For I2C communication.
- **U8glib**: For OLED display control.
- **Servo**: For controlling the servo motor.

## Code Structure

### Initialization

- `setup()`: Initializes serial communication, hardware components, OLED display font, and pins for input/output.

### Main Loop

- `loop()`: Continuously displays time and temperature on the OLED display, writes temperature to the servo, and checks for the temperature threshold to activate the LED warning.

### Functions

1. **`getTime()`**: Reads and formats the time from the DS3231 module.
2. **`getTemp()`**: Reads the temperature from an analog sensor, converts it to Celsius.
3. **`oledWrite(text, temp)`**: Displays the time and temperature on the OLED.
4. **`servoWrite(value)`**: Maps the temperature to the servo motor's angle.
5. **`blinkblonk()`**: Activates the LEDs in a flashing pattern if the temperature exceeds 27°C.

## Usage

1. Connect the components as per the schematic.
2. Upload the code to your microcontroller.
3. Monitor the OLED display for real-time clock and temperature.
4. Observe the servo motor and LEDs for temperature-based responses.

## Future Improvements

- Expand temperature ranges or implement temperature calibration.
- Add further customization options for display settings or alert thresholds. 

