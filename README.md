
# Weather Dashboard with Firebase and ESP32 
This project combines two parts: a **React app** for visualizing temperature and humidity data and an **ESP32-based device** for collecting sensor data.
The app retrieves the data from a Firebase Firestore database and displays it through interactive charts.

## Project Overview
This project allows users to track temperature and humidity data over time, visualize it in a simple dashboard, and store the data in Firebase for later access.
The ESP32 collects real-time data from temperature and humidity sensors, and the React app provides a web-based interface to view and analyze the data.

### Components
- **React App**: A web interface for viewing temperature and humidity data. It fetches data from Firebase Firestore and visualizes it using interactive charts.
- **ESP32 Device**: A microcontroller that reads temperature and humidity data from sensors (DHT11) and sends it to Firebase for storage.
- **Firebase**: The backend service that stores data from the ESP32 and serves it to the React app.

## Features
- Real-time data collection and visualization
- Interactive line charts for displaying temperature and humidity
- Firebase integration for storing and retrieving data
- Simple and responsive layout for different screen sizes

## Technologies Used
- **Frontend**: React, Recharts, Day.js
- **Backend**: Firebase Firestore
- **Hardware**: ESP32 (with DHT11)

## How It Works
1. **Data Collection (ESP32)**: The ESP32 reads the temperature and humidity from the sensors and sends the data to Firebase using the Firebase SDK for Arduino.
2. **Data Storage (Firebase)**: The collected data is stored in Firebase Firestore under the "letture" collection.
3. **Data Visualization (React App)**: The React app fetches data from Firebase and uses Recharts to display it in interactive line charts.

## For The Setup Instructions:

### Backend (ESP32)
See the README.md file in "/ESP32"

### Frontend (React App)
 See the README.md file in "/App-React"

## Security Considerations
This project does not include Firebase security rules by default.  
If you plan to deploy the app, make sure to:
- Set appropriate Firestore security rules to control read and write access.
- Never expose sensitive credentials in your code or frontend.
