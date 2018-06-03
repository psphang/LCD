//Arduino Clock
//Requirements:
/*
 * 1-Arduino Mega or Uno
 * 2-Potentiometer (eg 5K)
 * 3-LCD 16x2
 * 4-Two Push button
 */
//Description:
/*
 * With this code you can make a 12-hours clock by using 16x2 LCD display.
 * Also we can set the time with the help of two push buttons, which controls Hours and Minutes.
 */
//Pin-outs:
 /*
  * Pin outs of Arduino board, 16x2 LCD screen and Ultrasonic sensor is given following:
  * Arduino       ||        LCD
  * ====================================
  * +5V                    VDD or VCC
  * GND                     VSS
  * 8                       RS
  * GND                     RW
  * 9                       E
  * 4                       D4
  * 5                       D5
  * 6                       D6
  * 7                       D7
  * +3.3V                   A
  * GND                     K
  * ====================================
  * Arduino       ||     Potentiometer
  * ====================================
  * +5V                     1st pin
  * GND                     3rd pin
  * ====================================
  * Potentiometer ||        LCD
  * ====================================
  * 2nd pin                 Vo
  * => You can set contrast using Potentiometer
  * ====================================
  * Arduino       ||  Push Button 1
  * ====================================
  * +5V                     1st Pin
  * 10                      2nd Pin
  * ====================================
  * Arduino       ||  Push Button 2
  * ====================================
  * +5V                     1st Pin
  * 11                      2nd Pin
  * ====================================
  */
#include <LiquidCrystal.h>

//mcunode pio to real esp pio
#define D0 16
#define D1 5 // I2C Bus SCL (clock)
#define D2 4 // I2C Bus SDA (data)
#define D3 0
#define D4 2 // Same as "LED_BUILTIN", but inverted logic
#define D5 14 // SPI Bus SCK (clock)
#define D6 12 // SPI Bus MISO 
#define D7 13 // SPI Bus MOSI
#define D8 15 // SPI Bus SS (CS)
#define D9 3 // RX0 (Serial console)
#define D10 1 // TX0 (Serial console)
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//const int rs = 16,rw = 5, en = 4, d4 = 0, d5 = 2, d6 = 14, d7 = 12;
const int rs = 16, en = 5, d4 = 4, d5 = 0, d6 = 2, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int button, mode1, mode2, t=2, f, second=0, minutes=0, hours=0;
void setup()
{
  lcd.begin(16,2);
  lcd.clear();
  pinMode(D7,INPUT);
  pinMode(D8,INPUT);
}
void loop()
{
  f=t%2;
  mode1=digitalRead(D7);
  mode2=digitalRead(D8);
  lcd.clear();
  lcd.print("Time : ");
  if(f==0)
  {
    lcd.print("       AM");
  }
  else
  {
    lcd.print("       PM");
  }
  second++;
  if(second>=60)
  {
    second=0;
    minutes++;
  }
  if(minutes>=60)
  {
    second=0;
    minutes=0;
    hours++;
  }
  if(hours>=13)
  {
    second=0;
    minutes=0;
    hours=1;
    t++;
  }
  lcd.setCursor(6,0);
  lcd.print(hours);
  lcd.print(":");
  lcd.print(minutes);
  lcd.print(":");
  lcd.print(second);
  if(mode1==1)
  {
    delay(100);
    minutes++;
  }
  if(mode2==1)
  {
    delay(1000);
    hours++;
  }
  else
  {
    delay(1000);
  }
}
