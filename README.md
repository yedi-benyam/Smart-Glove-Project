# Smart-Glove-Project

## Overview
Arduino-based smart glove that converts hand gestures into text and speech output. Designed as an assistive communication system for people with speech impairments.

## Features
- Gesture recognition using flex sensors
- LCD display output
- Bluetooth communication with mobile app
- Text-to-speech output via mobile application

## Components Used
- Arduino Uno
- Flex Sensors
- LCD Display (I2C)
- HC-05 Bluetooth Module
- Glove
- Resistors and wiring

## Files in this Repository
- Smart Glove.pdf → Full project documentation
- smartglove_buttons.ino → Alternative control version
- smartglove_flexsensor.ino → main Arduino code
- smart_glove.aia → MIT App Inventor mobile app project

## Working Principle
1. User bends fingers
2. Flex sensors detect movement
3. Arduino processes gesture
4. Output is shown on LCD
5. Data is sent to mobile app via Bluetooth
6. Mobile app converts text to speech

## Challenges Faced
- Flex sensor calibration issues
- Bluetooth communication instability
- Wiring and connection reliability

## Future Improvements
- Custom PCB design to reduce size
- Improved gesture recognition accuracy
- AI-based gesture classification
- Fully standalone speech output system

## Skills Demonstrated
- Embedded Systems
- Arduino Programming
- Sensor Integration
- Bluetooth Communication
- Mobile App Integration

## Author
Yedi Benyam
