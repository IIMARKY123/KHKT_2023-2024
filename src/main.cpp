#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include<Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <Wire.h>
#include <ESP32Servo.h>
#include <ILI9341_SPI.h>
#include <MiniGrafx.h>
#include <Carousel.h>
#include <ArialRounded.h>
#include <HTTPClient.h>   
AsyncWebServer server(80);
Adafruit_MPU6050 mpu;
Servo myservo;
int pos=0;
int val=10;
String val1,val2,val3,val4,val5;
#define MINI_BLACK 0
#define MINI_WHITE 1
#define MINI_YELLOW 2
#define MINI_BLUE 3
#define TFT_DC 2
#define TFT_CS 15
const char* server1="http://192.168.1.194/1";
const char* server2="http://192.168.1.194/2";
const char* server3="http://192.168.1.194/3";
const char* server4="http://192.168.1.194/4";
const char* server5="http://192.168.1.194/5";

uint16_t palette[] = {ILI9341_BLACK, // 0
                      ILI9341_WHITE, // 1
                      ILI9341_YELLOW, // 2
                      0x7E3C
                     }; //3
int BITS_PER_PIXEL = 2; // 2^2 =  4 colors
ILI9341_SPI tft = ILI9341_SPI(TFT_CS, TFT_DC);
MiniGrafx gfx = MiniGrafx(&tft, BITS_PER_PIXEL, palette);
Carousel carousel(&gfx, 0, 0, 240, 100);


String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

void MPUsetup(int sda,int scl){
  Wire.begin(sda,scl);
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
          delay(10);
        }
    }
    Serial.println("MPU6050 Found!");
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    // set gyro range to +- 500 deg/s
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    // set filter bandwidth to 21 Hz
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    analogReadResolution(10);
    delay(100);
}

void MPUuse(){
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    Serial.print("Rotation X: ");
    Serial.print(g.gyro.x);
    Serial.print(", Y: ");
    Serial.print(g.gyro.y);
    Serial.print(", Z: ");
    Serial.print(g.gyro.z);
    Serial.println(" rad/s");
}

void ServoSetup(int Pin){
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(Pin); 
}

String readval1(){
  return String(analogRead(36));
}
String readval2(){
  return String(analogRead(39));
}
String readval3(){
  return String(analogRead(34));
}
String readval4(){
  return String(analogRead(35));
}
String readval5(){
  return String(analogRead(32));
}

void setup(){
  
  WiFi.mode(WIFI_AP_STA);
  //WiFi.softAP("ESP32","12345678");
  Serial.begin(115200);
  //MPUsetup(33,25);
  WiFi.begin("SCTV_19001878_OpenWrt","19001878");
  while (WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting");
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  analogReadResolution(10);
  gfx.init();
  gfx.fillBuffer(MINI_YELLOW);
  gfx.setFont(ArialRoundedMTBold_36);
  gfx.commit();
  server.on("/1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readval1().c_str());
  });
  server.on("/2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readval2().c_str());
  });
  server.on("/3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readval3().c_str());
  });
  server.on("/4", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readval4().c_str());
  });
  server.on("/5", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readval5().c_str());
  });
  server.begin();
}

void loop(){
   if(WiFi.status()== WL_CONNECTED ){ 
 val1=httpGETRequest(server1);
 val2=httpGETRequest(server2);
 val3=httpGETRequest(server3);
 val4=httpGETRequest(server4);
 val5=httpGETRequest(server5);
   }
   Serial.println(val1);
}