# Smart Home Automation System

An end-to-end IoT-based smart home automation system leveraging ESP32 to enable multi-modal appliance control via **gesture recognition**, **custom capacitive touch**, **Google Assistant integration**, and **mobile app**. The system includes **real-time data logging to Google Sheets**, making it suitable for scalable home or industrial automation solutions.

---

## Key Features

- Multi-modal control: **Gesture**, **Touch**, **Voice (Google Assistant)**, and **Mobile App**
- **Google Sheets integration** for real-time event logging and monitoring
- Dual load control: **AC bulb** and **LED** via relay interface
- Designed with **modular and scalable architecture** using ESP32

---

## Hardware Components

 ESP32 Microcontroller                   
 APDS9960 Gesture Sensor   
 Custom Touch Sensor       
 2-Channel Relay Module    
 AC Bulb 
 LED             
 Breadboard 
 Jumper Wires 
 Electrical insulation cables

---

## Software Setup

### Required Libraries

Install the following via Arduino Library Manager:
- `WiFi.h`
- `Wire.h`
- `Adafruit_APDS9960` or `SparkFun_APDS9960`
- `SinricPro.h`
- `ESP_Google_Sheet_Client.h`

### Configuration Steps

1. Set up your Wi-Fi SSID and password in code.
2. Configure Sinric Pro device credentials for voice/app control.
3. Generate Google Sheet API credentials and paste them in your code.
4. Upload the code to ESP32 using Arduino IDE.

---

## System Operation

- **Gesture**: Swipe to toggle devices.
- **Touch**: Tap DIY sensor to switch loads.
- **Voice**: Use commands via Google Assistant.
- **App**: Control devices remotely with Sinric Pro app.
- **Logging**: All events are recorded with timestamp in a Google Sheet.

---


## Contributors

- **Tanushree Waratkar**  
  [GitHub](https://github.com/Tanushree-Waratkar) | [LinkedIn](https://www.linkedin.com/in/tanushree-waratkar-872a63270/)

- **Shivam Rao**  
  [GitHub](https://github.com/Sv9r) | [LinkedIn](https://www.linkedin.com/in/shivam-rao-s029788/)

---

This project demonstrates practical skills in:
- Embedded C/C++ and Arduino framework
- IoT system integration (hardware + cloud)
- API-based communication and real-time logging
- End-user interface development (voice and app-based)
- Technical documentation and modular design practices
