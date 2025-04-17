#include <Arduino.h>
#include <SimpleDHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>

// Wi-Fi credentials
const char* ssid = "wifi_name";                 
const char* password = "wifi_password";

// Firebase credentials
const char* FIREBASE_API_KEY = "FIREBASE_API_KEY";
const char* FIREBASE_PROJECT_ID = "FIREBASE_PROJECT_ID";
const char* DOCUMENTO_FIRESTORE = "FIREBASE_COLLECTION";

// RGB LED pins
#define PIN_LED_Red 16
#define PIN_LED_Green 17
#define PIN_LED_Blue 18

// Function declarations
int inviaDatiFirestore(String,String);
void set_led_rosso();
void set_led_verde();
void set_let_blue();

// Initialize DHT11 sensor on pin 22
SimpleDHT11 dht11(22);

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_Red, OUTPUT);
  pinMode(PIN_LED_Green, OUTPUT);
  pinMode(PIN_LED_Blue, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  // Retry Wi-Fi connection up to 20 times
  int maxProve = 20;
  int prova = 0;

  // Wi-Fi connection loop
  while (WiFi.status() != WL_CONNECTED && prova < maxProve ){
    delay(1000);
    set_led_rosso(); // Red LED = no connection
    prova += 1;
  }

  if(WiFi.status() == WL_CONNECTED){
    set_led_verde(); // Green LED = connected

    // Set NTP time sync (CET time zone)
    configTime(7200, 3600, "pool.ntp.org");
  }
}

void loop() {
  int int_temp,int_umid,media_umidita=0,media_temperatura=0;
  
  // Check if Wi-Fi is still connected
  if (WiFi.status() == WL_CONNECTED){
    // Average 10 readings
    for ( int i = 0; i < 10; i++){
      byte temp = 0; 
      byte umid = 0;

      // Read sensor data
      int err = dht11.read(&temp, &umid, NULL);

      if(err != SimpleDHTErrSuccess){
        i--; // Retry current reading
      } else {
        int_temp = int(temp);
        int_umid = int(umid);
        media_umidita += int_umid;
        media_temperatura += int_temp;
        delay(4000);
      }
    }

    // Calculate average values
    int_temp = media_temperatura / 10;
    int_umid = media_umidita / 10;

    // set as string for "inviaDatiFirestore()" function
    String umidita = String(int_umid);
    String temperatura = String(int_temp);

    // Send data to Firebase
    if(inviaDatiFirestore(umidita,temperatura)){
      set_led_verde(); // Data send to Database
      delay(3600000);  // Wait 1 hour before next transmission
    } else {
      set_let_blue();  // Error sending to Firebase
    }

  } else {
    // Wi-Fi disconnected, attempt to reconnect
    set_led_rosso();
    
    WiFi.begin(ssid, password);  
    while (WiFi.status() != WL_CONNECTED){
      delay(1000);
    }

    if(WiFi.status() == WL_CONNECTED){
      set_led_verde();
    }
  }
}

// Function to send temperature and humidity data to Firestore
int inviaDatiFirestore(String umidita, String temperatura){
  HTTPClient http;

  time_t ora;
  time(&ora);

  struct tm struct_tm;
  localtime_r(&ora, &struct_tm); // Get local time

  // Format timestamp for Firebase
  char stringa_ora[20];
  strftime(stringa_ora, sizeof(stringa_ora), "%Y-%m-%d %H:%M", &struct_tm);

  // Build Firestore request URL
  String url = "https://firestore.googleapis.com/v1/projects/"+ String(FIREBASE_PROJECT_ID)+ "/databases/(default)/documents/"+ String(DOCUMENTO_FIRESTORE)+ "?key=" + FIREBASE_API_KEY;

  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  // Construct JSON payload for Firestore
  String payload = 
  "{"
    "\"fields\": {"
      "\"Temperatura\": { \"integerValue\": "+temperatura+" },"
      "\"Umidita\": { \"integerValue\": "+umidita +" },"
      "\"Data_lettura\": { \"stringValue\": \""+ String(stringa_ora)+"\" }"
    "}"
  "}";

  int httpResponseCode = http.POST(payload);

  // Check HTTP response
  if(httpResponseCode == 200){
    http.end();
    return 1;
  } else {
    http.end();
    return 0;
  }
}

// RED: Wi-Fi disconnected
void set_led_rosso(){
  analogWrite(PIN_LED_Green,0); 
  analogWrite(PIN_LED_Red,255);
  analogWrite(PIN_LED_Blue,0);
}

// GREEN: All systems working
void set_led_verde(){
  analogWrite(PIN_LED_Green,255); 
  analogWrite(PIN_LED_Red,0);
  analogWrite(PIN_LED_Blue,0);
}

// BLUE: Error sending data to Firestore
void set_let_blue(){
  analogWrite(PIN_LED_Green,0); 
  analogWrite(PIN_LED_Red,0);
  analogWrite(PIN_LED_Blue,255);
}
