#include "MQ135.h"
#include "LiquidCrystal_I2C.h"

int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows); 

void setup (){
Serial.begin (9600);
pinMode(D5, OUTPUT);
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Khi gas:");
}
void loop() {
  MQ135 gasSensor = MQ135(A0); // Attach sensor to pin A0
  lcd.setCursor(8, 0);
  float rzero = gasSensor.getRZero();
  lcd.print(rzero);
  if (rzero <= 50){
    lcd.setCursor(0, 1);
    lcd.print("Canh bao");
    Serial.println ("warnning");
    digitalWrite(D5, HIGH);
  }
  else {
    digitalWrite(D5, LOW);
  }
  delay(1000);
}
