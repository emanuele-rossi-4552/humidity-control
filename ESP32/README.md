# ESP32 DHT11 Firebase Logger
This project reads temperature and humidity data from a **DHT11 sensor**, averages the values over 10 readings,
and sends the data every hour to **Google Firebase Firestore** using an **ESP32** microcontroller with Wi-Fi.
RGB LED indicators provide real-time status updates on Wi-Fi connectivity and data transmission.

## Features
- Connects to Wi-Fi with retry mechanism  
- Reads temperature and humidity using DHT11  
- Averages 10 sensor readings for more stable data  
- Sends data to Firebase Firestore via HTTP POST  
- Includes timestamp using NTP (Network Time Protocol)  
- RGB LED status indication  
  - 🔴 Red: No Wi-Fi connection  
  - 🟢 Green: Connected and data sent successfully  
  - 🔵 Blue: Failed to send data to Firebase  

## Hardware Requirements
- ESP32 board  
- DHT11 temperature and humidity sensor (data connected to pin 22)
- Common cathode RGB LED (connected to pins 16 (Red), 17(Green), and 18(Blue))  
- Internet connection  

## Software Requirements
- VSCode with PlatformIO
- Libraries:
  - `SimpleDHT`(included in the project)
  - `WiFi.h` (included with ESP32 core)
  - `HTTPClient.h`(included with ESP32 core)

## Firebase Setup
1. Go to [Firebase Console](https://console.firebase.google.com/) and create a new project.
2. Enable **Firestore Database** in test mode.
3. Note your **project ID** and **Web API Key** from project settings.
4. Set your Firestore collection name (e.g., `dati_sensor`) in the sketch.
5. Ensure your security rules allow data writing (for development only):

Before uploading the sketch, update the following constants:

    const char* ssid = "your_wifi_name";
    const char* password = "your_wifi_password";

    const char* FIREBASE_API_KEY = "your_firebase_api_key";
    const char* FIREBASE_PROJECT_ID = "your_project_id";
    const char* DOCUMENTO_FIRESTORE = "your_firestore_collection";


How It Works
  ESP32 connects to Wi-Fi (with max 20 retries).

  If successful, it sets the time using pool.ntp.org.

  Every hour:
    It reads 10 temperature/humidity values from DHT11.
    Averages them.

  Sends them to Firestore.

  LED color changes based on result.
