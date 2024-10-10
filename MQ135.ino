#include "MQ135.h"
#include <LiquidCrystal_I2C.h>

int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows); 

void setup (){    //Mỗi khi sketch bắt đầu, lệnh setup sẽ giúp bạn khởi tạo các biến và bắt đầu sử dụng các thư viện
Serial.begin (9600);//thiết lập giao tiếp nối tiếp giữa bo Arduino và một thiết bị khác.giữa Arduino và máy tính của bạn thông qua cáp USB 
pinMode(D5, OUTPUT);// đặt pin kỹ thuật số làm output: pinMode(ledPin, OUTPUT);
  // initialize LCD
  lcd.init();//khởi động màn hình 
  // turn on LCD backlight                      
  lcd.backlight();//bật đèn nền
  // set cursor to first column, first row
  lcd.setCursor(0, 0);////Đưa con trỏ tới hàng 0, cột 0 cột-hàng
  // print message
  lcd.print("Khi gas:");
}
void loop() {
  MQ135 gasSensor = MQ135(A0); // Attach sensor to pin A0//khai báo chân đọc cảm biến A0
  lcd.setCursor(8, 0);//khai báo cột hàng
  float rzero = gasSensor.getRZero();
  lcd.print(rzero);
  if (rzero <= 0){
    lcd.setCursor(0, 1);//Đưa con trỏ tới hàng 1, cột 0
    lcd.print("Canh bao");
    Serial.println ("warnning");//xuất gtri dạng chuỗi 
    digitalWrite(D5, HIGH);//xuất tín hiệu
  }
  else {
    digitalWrite(D5, LOW);
  }
  delay(1000);
}
