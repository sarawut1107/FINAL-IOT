#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>

#define WIFI_SSID "Worapron4_1_2.4G"
#define WIFI_PASSWORD "pp394394"
#define FIREBASE_HOST "final-sarawut-default-rtdb.firebaseio.com"
#define FIREBASE_KEY "AIzaSyBhGLtgVbvM13-g6-081DvmY9jtZoB9QOQ"


void setup()
{
  Serial.begin(115200);
  
 Serial.println(WiFi.localIP());
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      Serial.print(WiFi.status());
    }

    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.status());
    Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
}

void loop()
{

  if (Firebase.failed())
  {
    Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
    Serial.println(Firebase.error());
    Serial.println("Connection to firebase failed...");
  }
  else
  {
   
  }
}
