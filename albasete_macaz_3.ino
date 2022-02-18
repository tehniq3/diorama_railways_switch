/* Sweep by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.
 modified 8 Nov 2013 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep

adapted by Nicu FLORICA (niq_ro)

ver.1.0 - used barrier sketch https://github.com/tehniq3/diorama_barriers
ver.1.0.b - used one pin for control 2 leds + flashing internal led (D13) 
ver.2.0 - 4 servos with individual controls: https://github.com/tehniq3/diorama_railways_switch
ver.2.b - move outputs of the servos at PWM outputs
ver.3.0 - use EEPROM to store position for each servos
ver.3.c - repair value after restart
*/

#define led0 13 // internal led on board 

#define sw11 2
#define sw12 3
#define servo1 6  // pwm
#define led1 15   // A1

#define sw21 4
#define sw22 5
#define servo2 9  // pwm
#define led2 16   // A2

#define sw31 7
#define sw32 8
#define servo3 10 // pwm
#define led3 17   // A3

#define sw41 12  
#define sw42 14   // A0  
#define servo4 11 // pwm
#define led4 18   // A4

#include <EEPROM.h>
#include <Servo.h>
Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
Servo myservo4;  // create servo object to control a servo

int pos1 = 0;    // variable to store the servo position
int pos2 = 0;    // variable to store the servo position
int pos3 = 0;    // variable to store the servo position
int pos4 = 0;    // variable to store the servo position

int posmin = 30; // minimum position of the servo
int posmax = 60; // maximum position of the servo
int delta = 5;  // error position

unsigned long  minipauza = 25;  // pentru reducere viteza, implicit e 15.. viteza scade daca numarul creste
int pauzamica = 250; // pauza mica pentru apasare buton
byte directie1 = 0;  // 0 - stop, 1 - left, 2 - right
byte lumina1 = 3;
byte directie2 = 0;  // 0 - stop, 1 - left, 2 - right
byte lumina2 = 3;
byte directie3 = 0;  // 0 - stop, 1 - left, 2 - right
byte lumina3 = 3;
byte directie4 = 0;  // 0 - stop, 1 - left, 2 - right
byte lumina4 = 3;

unsigned long tpcomanda1, tpcomanda2, tpcomanda3, tpcomanda4;

byte pos10, pos20, pos30, pos40;  // values for sore last position of servos
byte checkok = 5;  // value for check the eeprom state
byte adresa = 200; // adresa initiala de memorare

unsigned long tpjoaca;
unsigned long tpmemorare = 5000;
byte scris = 1;

void setup() {
  Serial.begin(9600);
  Serial.println(" ");
  Serial.println("4 switches for railways on diorama");
  Serial.println("software wrote by Nicu FLORICA (niq_ro)");

pinMode(sw11, INPUT);
  pinMode(sw12, INPUT);
  pinMode(sw21, INPUT);
  pinMode(sw22, INPUT);
  pinMode(sw31, INPUT);
  pinMode(sw32, INPUT);
  pinMode(sw41, INPUT);
  pinMode(sw42, INPUT);
  digitalWrite(sw11, HIGH);  // enable internal pullup resistor
  digitalWrite(sw12, HIGH);  // enable internal pullup resistor
  digitalWrite(sw21, HIGH);  // enable internal pullup resistor
  digitalWrite(sw22, HIGH);  // enable internal pullup resistor
  digitalWrite(sw31, HIGH);  // enable internal pullup resistor
  digitalWrite(sw32, HIGH);  // enable internal pullup resistor
  digitalWrite(sw41, HIGH);  // enable internal pullup resistor
  digitalWrite(sw42, HIGH);  // enable internal pullup resistor

pinMode(led0, OUTPUT); // output
pinMode(led1, OUTPUT); // output
pinMode(led2, OUTPUT); // output
pinMode(led3, OUTPUT); // output
pinMode(led4, OUTPUT); // output
  digitalWrite(led0, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

if (EEPROM.read(adresa) == checkok) 
{
  Serial.println("read values for servos...");
  pos1 = EEPROM.read(adresa+1);
  pos2 = EEPROM.read(adresa+2);
  pos3 = EEPROM.read(adresa+3);
  pos4 = EEPROM.read(adresa+4);
}
else
{
  Serial.println("write the values for servos...");
  pos1 = posmin;
  pos2 = posmin;
  pos3 = posmin;
  pos4 = posmin;
  EEPROM.update(adresa, checkok);
  EEPROM.update(adresa+1, posmin);
  EEPROM.update(adresa+2, posmin);
  EEPROM.update(adresa+3, posmin);
  EEPROM.update(adresa+4, posmin);
  digitalWrite(led0, HIGH);
  delay(1000);
  digitalWrite(led0, LOW);
}
  
  myservo1.attach(servo1);  // attaches the servo
  myservo1.write(pos1);              // tell servo to go to position in variable 'pos1'
  delay(pauzamica);  
  myservo2.attach(servo2);  // attaches the servo 
  myservo2.write(pos2);              // tell servo to go to position in variable 'pos2'
  delay(pauzamica);
  myservo3.attach(servo3);  // attaches the servo 
  myservo3.write(pos3);              // tell servo to go to position in variable 'pos3'
  delay(pauzamica); 
  myservo4.attach(servo4);  // attaches the servo 
  myservo4.write(pos4);              // tell servo to go to position in variable 'pos4'
  delay(pauzamica);

  if (pos1 > posmax-delta) lumina1 = 1;
  else lumina1 = 2;
  if (pos2 > posmax-delta) lumina2 = 1;
  else lumina2 = 2;  
  if (pos3 > posmax-delta) lumina3 = 1;
  else lumina3 = 2;
  if (pos4 > posmax-delta) lumina4 = 1;
  else lumina4 = 2;

delay(2000);
}

void loop() {
  digitalWrite(sw11, HIGH);  // enable internal pullup resistor
  digitalWrite(sw12, HIGH);  // enable internal pullup resistor
  digitalWrite(sw21, HIGH);
  digitalWrite(sw22, HIGH);
  digitalWrite(sw31, HIGH);
  digitalWrite(sw32, HIGH);
  digitalWrite(sw41, HIGH);
  digitalWrite(sw42, HIGH);
   
  digitalWrite(led0, millis()/200%2);  // flash
 
  if ((digitalRead(sw11) == LOW) and (pos1 < posmin+delta))
  {
  Serial.println("Servo1 to Left !");
  directie1 = 1;
  lumina1 = 1;
  pos1 = posmin;
  delay(pauzamica);
  tpcomanda1 = millis();
  }
  
  if ((digitalRead(sw12) == LOW) and (pos1 > posmax-delta))
  {
  Serial.println("Servo1 to Right!");
  directie1 = 2;
  lumina1 = 2;
  pos1 = posmax;
  delay(pauzamica);
  tpcomanda1 = millis();
  }

  if ((digitalRead(sw21) == LOW) and (pos2 < posmin+delta))
  {
  Serial.println("Servo2 to Left !");
  directie2 = 1;
  lumina2 = 1;
  pos2 = posmin;
  delay(pauzamica);
  tpcomanda2 = millis();
  }
  
  if ((digitalRead(sw22) == LOW) and (pos2 > posmax-delta))
  {
  Serial.println("Servo2 to Right!");
  directie2 = 2;
  lumina2 = 2;
  pos2 = posmax;
  delay(pauzamica);
  tpcomanda2 = millis();
  }

  if ((digitalRead(sw31) == LOW) and (pos3 < posmin+delta))
  {
  Serial.println("Servo3 to Left !");
  directie3 = 1;
  lumina3 = 1;
  pos3 = posmin;
  delay(pauzamica);
  tpcomanda3 = millis();
  }
  
  if ((digitalRead(sw32) == LOW) and (pos3 > posmax-delta))
  {
  Serial.println("Servo3 to Right!");
  directie3 = 2;
  lumina3 = 2;
  pos3 = posmax;
  delay(pauzamica);
  tpcomanda3 = millis();
  }

  if ((digitalRead(sw41) == LOW) and (pos4 < posmin+delta))
  {
  Serial.println("Servo4 to Left !");
  directie4 = 1;
  lumina4 = 1;
  pos4 = posmin;
  delay(pauzamica);
  tpcomanda4 = millis();
  }
  
  if ((digitalRead(sw42) == LOW) and (pos4 > posmax-delta))
  {
  Serial.println("Servo4 to Right!");
  directie4 = 2;
  lumina4 = 2;
  pos4 = posmax;
  delay(pauzamica);
  tpcomanda4 = millis();
  }

  if ((directie1 == 1) and (millis() - tpcomanda1 > minipauza))
  { 
    myservo1.write(pos1);              // tell servo to go to position in variable 'pos'
    pos1+=1;
  if (pos1 >= posmax)
  {
    directie1 = 0;
    tpjoaca = millis();
    scris = 0;
  }
  }

  if ((directie1 == 2) and (millis() - tpcomanda1 > minipauza))
  {
    myservo1.write(pos1);              // tell servo to go to position in variable 'pos'  
    pos1-=1;
    if (pos1 <= posmin) 
    {
      directie1 = 0;
      tpjoaca = millis();
      scris = 0;
    }
  }

 if ((directie2 == 1) and (millis() - tpcomanda2 > minipauza))
  { 
    myservo2.write(pos2);              // tell servo to go to position in variable 'pos'
    pos2+=1;
  if (pos2 >= posmax)
  {
    directie2 = 0;
    tpjoaca = millis();
    scris = 0;
  }
  }

  if ((directie2 == 2) and (millis() - tpcomanda2 > minipauza))
  {
    myservo2.write(pos2);              // tell servo to go to position in variable 'pos'  
    pos2-=1;
    if (pos2 <= posmin) 
    {
      directie2 = 0;
      tpjoaca = millis();
      scris = 0;
    }
  }

 if ((directie3 == 1) and (millis() - tpcomanda3 > minipauza))
  { 
    myservo3.write(pos3);              // tell servo to go to position in variable 'pos'
    pos3+=1;
  if (pos3 >= posmax)
  {
    directie3 = 0;
    tpjoaca = millis();
    scris = 0;
  }
  }

  if ((directie3 == 2) and (millis() - tpcomanda3 > minipauza))
  {
    myservo3.write(pos3);              // tell servo to go to position in variable 'pos'  
    pos3-=1;
    if (pos3 <= posmin) 
    {
      directie3 = 0;
      tpjoaca = millis();
      scris = 0;
    }
  }

 if ((directie4 == 1) and (millis() - tpcomanda4 > minipauza))
  { 
    myservo4.write(pos4);              // tell servo to go to position in variable 'pos'
    pos4+=1;
  if (pos4 >= posmax)
  {
    directie4 = 0;
    tpjoaca = millis();
    scris = 0;
  }
  }

  if ((directie4 == 2) and (millis() - tpcomanda4 > minipauza))
  {
    myservo4.write(pos4);              // tell servo to go to position in variable 'pos'  
    pos4-=1;
    if (pos4 <= posmin) 
    {
      directie4 = 0;
      tpjoaca = millis();
      scris = 0;
    }
  }


if (lumina1 == 1)
{
  digitalWrite(led1, HIGH);  
}
if (lumina1 == 2)
{
  digitalWrite(led1, LOW);    
}
if (lumina2 == 1)
{
  digitalWrite(led2, HIGH);  
}
if (lumina2 == 2)
{
  digitalWrite(led2, LOW);    
}
if (lumina3 == 1)
{
  digitalWrite(led3, HIGH);  
}
if (lumina3 == 2)
{
  digitalWrite(led3, LOW);    
}
if (lumina4 == 1)
{
  digitalWrite(led4, HIGH);  
}
if (lumina4 == 2)
{
  digitalWrite(led4, LOW);    
}

if ((millis() - tpjoaca > tpmemorare) and (scris == 0))
{
  Serial.println("write the new values for servos...");
  EEPROM.update(adresa, checkok);
  EEPROM.update(adresa+1, pos1);
  EEPROM.update(adresa+2, pos2);
  EEPROM.update(adresa+3, pos3);
  EEPROM.update(adresa+4, pos4);
  scris = 1;
  digitalWrite(led0, HIGH);
  delay(1000);
  digitalWrite(led0, LOW);
}

 
delay(minipauza);
}  // end main loop
