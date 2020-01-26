//uji coba galon 
// 25 desember 2019

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Wire.h>

const int Upin = 8;  //pin sensor 
const int RelayPin = 7; //pin relay
const byte ROWS = 4; 
const byte COLS = 4; 
byte rowPins[ROWS] = {6, 5, 4, 3}; 
byte colPins[COLS] = {9, 12, 11, 10}; 
long duration, inches, cm;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //pin lcd ke pin digital
char keys[ROWS][COLS] = 
{ 
{'1','2','3','a'}, 
{'4','5','6','b'}, 
{'7','8','9','c'}, 
{'#','0','*','d'}  
};
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Keypad keypad=Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS); 

void setup()
{
pinMode(RelayPin,OUTPUT);
Serial.begin(9600);
lcd.begin(16, 2);
lcd.print("Selamat Datang");
delay(100);
}
void loop() 
{
  pinMode(Upin, OUTPUT);
  digitalWrite(Upin, LOW);
  delayMicroseconds(2);
  digitalWrite(Upin, HIGH);
  delayMicroseconds(5);
  digitalWrite(Upin, LOW); 
  pinMode(Upin, INPUT);
  duration = pulseIn(Upin, HIGH);
  
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
  
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);
   if (cm == 10)   
  { 
    digitalWrite(RelayPin, LOW);
    Serial.print("Hidup...");
    delay(10);
  }
    else
    {   
    digitalWrite(RelayPin, HIGH);
    Serial.print("Mati...");
    }
    delay(100);
    
    char tombol = keypad.getKey();
    if (tombol!= NO_KEY){
    Serial.println(tombol);}
    lcd.print(tombol);
    delay(100);
}
long microsecondsToInches(long microseconds)
{  
  return microseconds / 74 / 2;
}
long microsecondsToCentimeters(long microseconds) 
{
  return microseconds / 29 / 2;
}
