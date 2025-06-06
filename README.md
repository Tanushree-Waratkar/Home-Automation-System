# Smart-Home-Automation-System
Smart Home Automation using ESP32 with Gesture Sensor, Custom made Touch Sensor, Google Assistant, and App Control to manage AC Bulb and LED, it also features real time data logging using Google Sheets.



This project is a comprehensive IoT-based Smart Home Automation System. It allows users to control home appliances like an AC Bulb and an LED using multiple intuitive interfaces:

- Gesture control via APDS9960 Sensor
- Touch control using a custom-made touch sensor built with aluminum foil
- Voice control using Google Assistant
- Mobile app-based control using the Sinric Pro app
- Real-time data logging to Google Sheets for monitoring system activity

 # Hardware Components

- ESP32 Microcontroller (Wi-Fi Enabled)
- APDS9960 Gesture Sensor
- Custom Touch Sensor (DIY using aluminum foil)
- Relay Module
- AC Bulb
- LED
- Breadboad
- Jumper Wires
- Insulated Electrical Wires 

 # How It Works

1. The ESP32 reads input from the gesture sensor or the DIY touch sensor.
2. Based on the input, it triggers a relay module to switch the AC Bulb or LED on/off.
3. Users can also send commands via Google Assistant (linked to Sinric Pro) or the mobile app.
4. Every control action is logged in real-time to a connected Google Sheet for record-keeping and analysis.



