# 🔥 IoT-Based Autonomous Fire Fighting Robot

An autonomous IoT-based fire-fighting robot developed using **Arduino Uno** and **ESP8266**. The robot detects fire using multiple flame sensors, navigates toward the fire source, maintains a safe distance using an ultrasonic sensor, and extinguishes the fire with a servo-controlled water pump. It also supports Bluetooth manual control and real-time GPS tracking through Firebase.

---

## 📌 Features

* 🔥 Automatic fire detection using 3 flame sensors
* 🤖 Autonomous navigation toward the fire source
* 📏 Safe distance maintenance using an ultrasonic sensor
* 💧 Automatic water pump activation through relay
* 🎯 Servo-controlled water spray for wider coverage
* 📱 Bluetooth manual control using HC-05
* 🌍 Live GPS location tracking with Neo-6M GPS
* ☁️ Real-time Firebase integration via ESP8266
* 🔄 Manual and Auto operation modes

---

## 🛠 Hardware Components

| Component                 | Quantity |
| ------------------------- | -------: |
| Arduino Uno               |        1 |
| ESP8266 NodeMCU           |        1 |
| Flame Sensors             |        3 |
| HC-SR04 Ultrasonic Sensor |        1 |
| L298N Motor Driver        |        1 |
| DC Gear Motors            |        4 |
| Servo Motor               |        1 |
| 12V Water Pump            |        1 |
| Relay Module              |        1 |
| HC-05 Bluetooth Module    |        1 |
| Neo-6M GPS Module         |        1 |
| Water Tank                |        1 |
| Chassis & Wheels          |    1 Set |
| Battery Pack              |        1 |

---

## ⚙️ Software & Libraries

* Arduino IDE
* ESP8266WiFi
* FirebaseESP8266
* TinyGPS++
* SoftwareSerial
* Servo Library

---

## 🚀 How It Works

1. The flame sensors continuously monitor for fire.
2. The robot identifies the direction of the flame.
3. It moves toward the fire using the motor driver.
4. The ultrasonic sensor keeps the robot at a safe distance.
5. The relay activates the 12V water pump.
6. The servo sweeps the water nozzle left and right to extinguish the fire.
7. The ESP8266 uploads live GPS coordinates to Firebase.
8. The robot can also be controlled manually through Bluetooth.

---

## 📱 Bluetooth Commands

| Command | Function         |
| ------- | ---------------- |
| F       | Move Forward     |
| B       | Move Backward    |
| L       | Turn Left        |
| R       | Turn Right       |
| M       | Move Servo       |
| m       | Reset Servo      |
| N       | Pump ON          |
| n       | Pump OFF         |
| Y       | Stop Robot       |
| A       | Enable Auto Mode |

---

## 📂 Project Structure

```text
iot-fire-fighting-robot/
│
├── Arduino_Uno/
│   └── Final_Code_Arduino_Uno.ino
│
├── ESP8266_GPS/
│   └── Firebase_Connectivity_Code_ESP8266-32.ino
│
├── Circuit_Diagram/
│
├── Images/
│
└── README.md
```

---

## 📸 Project Images

> Add your project photos here.

* Robot Front View
* Robot Side View
* Internal Wiring
* Circuit Diagram
* Firebase Screenshot

---

## 🎥 Demonstration

A short demonstration video showing:

* Fire detection
* Autonomous navigation
* Water spraying
* Bluetooth control
* GPS tracking

---

## 🔮 Future Improvements

* Smoke sensor integration
* Gas leakage detection
* Mobile application
* Live camera streaming
* AI-based fire recognition
* Obstacle avoidance
* Path planning

---

## 👨‍💻 Author

**Muhammad Hasnain**
Embedded Systems • IoT • Robotics

If you found this project useful, consider giving it a ⭐ on GitHub.
