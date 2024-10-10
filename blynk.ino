#include "LiquidCrystal_I2C.h"
#define BLYNK_TEMPLATE_ID "TMPLYUot94ay"
#define BLYNK_DEVICE_NAME "GAS"
#define BLYNK_AUTH_TOKEN "Ij-BwVEMGHmUxc9hkdntf_Oc1eqa3ulN"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows); 
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "LAN";  // type your wifi name
char pass[] = "phongkhongcho";  // type your wifi password
int smokeA0 = A0;
int data = 0;
int sensorThres = 100;


BlynkTimer timer;


void setup(){
  pinMode(D5, OUTPUT);
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Khi gas:");
  pinMode(smokeA0, INPUT);
   Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  //dht.begin();
  timer.setInterval(2500L, sendSensor);
}

void sendSensor(){
  int data = analogRead(smokeA0);
  lcd.setCursor(8, 0);
  lcd.print(data);
  if (data >= 500){
    lcd.setCursor(0, 1);
    lcd.print("Canh bao");
    Serial.println ("warnning");
    digitalWrite(D5, HIGH);
  }
  else {
    digitalWrite(D5, LOW);
  }

  Blynk.virtualWrite(V0, data);
  Serial.print("Pin A0: ");
  Serial.println(data);
  if(data > 20){
    Blynk.email("test@gmail.com", "Alert", "Gas Leakage Detected!");
    Blynk.logEvent("gas_alert","Gas Leakage Detected");
  }
}


void loop(){
  Blynk.run();
  timer.run();
}
