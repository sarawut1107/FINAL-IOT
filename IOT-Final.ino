#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"
#include "DHT.h"
DHT dht;

//สำหรับคลื่นUltrasonic
const int trig = 2;
const int echo = 0;
long duration;
int distance;

//สำหรับวัดค่าน้ำ
int water = A0;
int vaWater = 0;


/* 1. Define the WiFi credentials */
//#define WIFI_SSID "Samon1"
//#define WIFI_PASSWORD "0880811520"
//#define WIFI_SSID "Samon1_plus"
//#define WIFI_PASSWORD "0880811520"
#define WIFI_SSID "Worapron4_1_2.4G"
#define WIFI_PASSWORD "pp394394"

/* 2. Define the API Key */
#define API_KEY "AIzaSyBhGLtgVbvM13-g6-081DvmY9jtZoB9QOQ"

/* 3. Define the RTDB URL <databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app*/
#define DATABASE_URL "final-sarawut-default-rtdb.firebaseio.com"

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "sarawut@gmail.com"
#define USER_PASSWORD "123456"

// 5. Board key (รหัสบอร์ด)
String BOARD_KEY = "boxs/001";

// 6. Path for update
String PAHT1 = "connection";
String PAHT2 = "food";
String PAHT3 = "moisture";
String PAHT4 = "temperature";
String PAHT5 = "water";

//7. Update time (5 วิ)
int UPDATE_TIME = 3000;


//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

//int count = 0;


void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  dht.setup(2); // data pin 2
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

}

void loop()
{

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  delay(2000);

    vaWater = analogRead(water);  //อ่านค่าสัญญาณ analog ขา5 ที่ต่อกับ Soil Moisture Sensor Module v1
    Serial.print("val = "); // พิมพ์ข้อมความส่งเข้าคอมพิวเตอร์ "val = "
    Serial.println(vaWater); // พิมพ์ค่าของตัวแปร val

  if (Firebase.ready() && (millis() - sendDataPrevMillis > UPDATE_TIME || sendDataPrevMillis == 0))
  {


    sendDataPrevMillis = millis();


    delay(dht.getMinimumSamplingPeriod());
    float humidity = dht.getHumidity(); // ดึงค่าความชื้น
    float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ


    FirebaseJson json;



    Serial.print("\t");
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.print(temperature, 1);
    if (!isnan(humidity) || !isnan(temperature)) {
      //    Value 1
      //    json.set(PAHT1, count + 1);
      //
      //    Value 2
//                json.set(PAHT2, duration);

      //    Value 3
//      json.set(PAHT3, humidity );
//
//      //    Value 4
//      json.set(PAHT4, temperature);
//      //    Value 5
//     json.set(PAHT5, vaWater);
//      Serial.printf("Update json... %s\n\n", Firebase.updateNode(fbdo, String("/" + BOARD_KEY + "/" + fbdo.pushName()), json) ? "ok" : fbdo.errorReason().c_str());
//
//    } else { //    Value 3
//      json.set(PAHT3, 0.0 );
//
//      //    Value 4
//      json.set(PAHT4, 0.0);
//      Serial.printf("Update json... %s\n\n", Firebase.updateNode(fbdo, String("/" + BOARD_KEY + "/" + fbdo.pushName()), json) ? "ok" : fbdo.errorReason().c_str());
    }

  }

}
