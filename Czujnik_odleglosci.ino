//podlaczenie LCD GND,VPP, SCL- A5,sda- A4 
//czujnik odleglosci vcc-pin 10, trig 12, echo 11

#include <Wire.h>   
#include <LiquidCrystal_I2C.h> 
#define trigPin 12
#define echoPin 11

#define czerwona 3
#define zielona 4
#define zolta 2

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {

pinMode(czerwona, OUTPUT); 
  pinMode(zielona, OUTPUT);
  pinMode(zolta, OUTPUT);
  digitalWrite(zielona, LOW);
  
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);

  lcd.begin(16,2);   
  lcd.backlight(); 
 
}
int a=0;
void loop() 
{
   lcd.clear();
a=zmierzOdleglosc();
Serial.print(a);
Serial.print("\n");
lcd.setCursor(0,0); 
lcd.print("czesc");
lcd.setCursor(0,1); 
lcd.print("Distance: ");
lcd.print(a);
lcd.print(" cm");

if (a<100 && a>50){
  digitalWrite(zielona, LOW);
  digitalWrite(czerwona, LOW);
  digitalWrite(zolta, HIGH);
  } ;
  if(a<50){
  digitalWrite(zielona, LOW);
  digitalWrite(czerwona, HIGH);
  digitalWrite(zolta, LOW);
  };
if(a>100) {
  digitalWrite(zielona, HIGH);
  digitalWrite(czerwona, LOW);
  digitalWrite(zolta, LOW);
};

delay(1000);
}


 int zmierzOdleglosc() {
  long czas=0, dystans=0;
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  czas = pulseIn(echoPin, HIGH);
  dystans = czas / 58;
 
  return dystans;
}
