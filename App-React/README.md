
# Firebase Weather Dashboard
This is a simple React app that reads temperature and humidity data from a Firebase Firestore database and displays them using charts (via Recharts).

## Configuration
To connect the app to your own Firebase project, edit the Firebase configuration inside "App.js".  
Look for the following section:

    const firebaseConfig = {
    apiKey: "API_key",
    authDomain: "Domain",
    projectId: "Project_ID",
    storageBucket: "Storage",
    messagingSenderId: "Sende_ID",
    appId: "App_ID"
    };

Replace the placeholder values with your actual Firebase credentials, which you can find in your Firebase Console.

## Features
 - Retrieves data from Firestore (letture collection)
 - Filters and visualizes data by year, month, and day
 - Displays temperature and humidity in interactive line charts
 - Responsive layout for different screen sizes

## Technologies Used
 - React
 - Firebase Firestore
 - Recharts
 - Day.js

## How to Run
- Clone the repository

- Install dependencies
    "npm install"

- Create a new React project and copy the file "App.js" and "index.js" into the "/src" folder. Then, replace the Firebase config in "App.js" with your own Firebase project credentials.

- For only local use:
    1) Start the development server
        "npm start"

- To deploy as a web app:
    1) Install Firbase CLI:
        "npm install -g firebase-tools"
    2) Log in to your Firebase account:
        "firebase login"
    3) Initialize Firebase Hosting:
        "firebase init hosting"
        - select your project
        - set the public directory to "build"
        - choose No for Single Page Application (SPA) rewrite
    4) Build the app:
        "npm run build"
    5) Deploy the app:
        "firebase deploy"


🛡️ Notes on Security
This project does not include any Firebase security rules.
If you plan to deploy this app or make it public, make sure to:

Set appropriate Firestore security rules

Never expose credentials that allow write access (or unauthenticated read access, unless intentional)
