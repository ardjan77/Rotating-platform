#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
SoftwareSerial Blue(9, 8); // RX, TX

int odczyt;
const int stepPin = 2; 
const int dirPin = 3; 
int relay =6;
int liczba_zdjec= 0;
int przerwa = 0;
int kroki = 860/liczba_zdjec;
int automat=0;

void setup() {
Serial.begin(9600);
lcd.begin(16,2);
lcd.print("Gotowy do pracy");;
Blue.begin(9600);
pinMode(stepPin,OUTPUT); 
pinMode(dirPin,OUTPUT);
pinMode(relay,OUTPUT);
digitalWrite(relay, HIGH);
}

void loop() { 
if (Blue.available()){
odczyt=Blue.read();

if(odczyt==101){   
  digitalWrite(dirPin,LOW);
  lcd.clear();
  lcd.print("Ustawiono");
  lcd.setCursor(0,1);
  lcd.print("kierunek obrotow");} 
      
if (odczyt==102){
  digitalWrite(dirPin,HIGH);
  lcd.clear();
  lcd.print("Ustawiono");
  lcd.setCursor(0,1);
  lcd.print("kierunek obrotow");}
  
if(odczyt==103){
if(automat==1)
{
  delay(3000);
  foto();
}    
else
{
  ruch();
}      
}
     

if(odczyt>5 & odczyt <50)
{
  liczba_zdjec=odczyt;
  kroki=860/liczba_zdjec; 
  lcd.clear();
  lcd.print("Liczba");
  lcd.setCursor(0,1);
  lcd.print("zdjec: "); 
  lcd.setCursor(6,1);
  lcd.print(liczba_zdjec);
}

if(odczyt>0 & odczyt <6)
{
  switch (odczyt) {
    
  case 1:
  przerwa = 2000;
  lcd.clear();
  lcd.print("Przerwa  ");
  lcd.setCursor(0,1);
  lcd.print("wynosi 2s"); 
  automat =0;
  break;
  
  case 2:
  przerwa = 5000;
  lcd.clear();
  lcd.print("Przerwa  ");
  lcd.setCursor(0,1);
  lcd.print("wynosi 5s"); 
  automat =0;
  break;
  
  case 3:
  przerwa = 10000;
  lcd.clear();
  lcd.print("Przerwa  ");
  lcd.setCursor(0,1);
  lcd.print("wynosi 10s"); 
  automat =0;
  break;
  
  case 4:
  przerwa = 30000;
  lcd.clear();
  lcd.print("Przerwa  ");
  lcd.setCursor(0,1);
  lcd.print("wynosi 30s"); 
  automat =0;
  break;
  
  case 5:
  przerwa = 0;
  automat =1;
  break;  
}
}
delay(100); 
}
}

void obrot()
  {
  for(int x = 0; x < kroki; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(1000);  
   }}

void ruch()
{
  int b=1;
for(int a =0; a<liczba_zdjec; a++)
{
  lcd.clear();
  lcd.print("Obrot ");
  lcd.setCursor(6,0);
  lcd.print(b);
  lcd.setCursor(8,0);
  lcd.print("/");
  lcd.setCursor(9,0);
  lcd.print(liczba_zdjec);
  b++;
  delay(1500);
  obrot();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Zrob zdjecie");
  delay(przerwa);
}
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GOTOWE");
}

void foto()
{
  delay(4000);
  int b=1;
for(int a =0; a<liczba_zdjec; a++)
{
  obrot();    
  lcd.clear();
  lcd.print("Zdjecie ");
  lcd.setCursor(9,0);
  lcd.print(b);
  lcd.setCursor(11,0);
  lcd.print("/");
  lcd.setCursor(12,0);
  lcd.print(liczba_zdjec);
  b++;
  delay(3500);
  digitalWrite(relay, LOW);
  delay(200);
  digitalWrite(relay, HIGH);
  delay(3500);
  digitalWrite(relay, LOW);
  delay(200);
  digitalWrite(relay, HIGH);
  delay(1500);
}    
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GOTOWE");
}

