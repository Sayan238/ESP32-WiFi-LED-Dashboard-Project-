# 🚀 ESP32 WiFi LED Dashboard Project

A Smart WiFi LED Control Dashboard using ESP32 and a Web Browser 🌐

Using this project, you can control multiple LEDs wirelessly from your phone or PC through a modern responsive web dashboard 📱💻



---

# ✨ Features

* 🌐 WiFi LED Control
* 📱 Mobile Responsive Dashboard
* 💡 Smooth LED Brightness Control
* ⚡ Real-Time Web Control
* 🎨 Modern UI Design
* 🔥 ESP32 Hotspot Mode
* 🎛 Multiple LED Controls
* 🌈 Smooth LED Effects

---

# 🛠 Components Used

* ESP32
* Breadboard
* LEDs
* Jumper Wires
* USB Cable

---

# 🔌 Circuit Connections

<img width="1536" height="1024" alt="ChatGPT Image May 16, 2026, 03_07_21 PM" src="https://github.com/user-attachments/assets/3f12c963-12d5-4a03-a6b4-7f7e72cf9547" />

| LED Color | ESP32 GPIO Pin |
|------------|----------------|
| 🔴 Red LED | GPIO 25 |
| 🟢 Green LED | GPIO 26 |
| 🔵 Blue LED | GPIO 27 |
| 🟡 Yellow LED | GPIO 14 |

### Connections:
- LED Positive (+) → ESP32 GPIO Pin
- LED Negative (-) → GND

⚠️ Recommended:
Use a 220Ω resistor with each LED for safety.

---

# 📷 Project Preview

<img width="1169" height="643" alt="Project Preview" src="https://github.com/user-attachments/assets/12b572d3-ccfe-4747-94f7-7a8a2f6ecaf4" />

---

# ⚙️ How It Works

1. Connect LEDs to ESP32 GPIO pins
2. Upload the code using Arduino IDE
3. Open Serial Monitor
4. Copy the IP Address
5. Open it in any web browser
6. Control LEDs wirelessly 🚀

---

# 💻 Arduino IDE Setup

### Board Setup
- Board: `ESP32 Dev Module`
- Select the correct COM Port
- Upload the code

### Required Libraries
```cpp
#include <WiFi.h>
#include <WebServer.h>
```

---

# 🌐 WiFi Setup

Update your WiFi credentials inside the code:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

---

# 📱 Dashboard Features

✅ LED ON/OFF Control  
✅ Brightness Slider  
✅ Smooth Glow Effects  
✅ Mobile Friendly UI  
✅ Real-Time Response  

---

# 📌 GitHub Repository

If you like this project, give it a ⭐ on GitHub.

---

# 🔥 Created By

## Sayan Barman

💻 ESP32 | IoT | Robotics | Web Projects
