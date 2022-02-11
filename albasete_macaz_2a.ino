/* Sweep by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.
 modified 8 Nov 2013 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep

adapted by Nicu FLORICA (niq_ro)

ver.1.0 - used barrier sketch https://github.com/tehniq3/diorama_barriers
ver.1.0.b - used one pin for control 2 leds + flashing internal led (D13) 
ver.2.0 - 4 servos with individual controls
*/

#define led0 13 // internal led on board 

#define sw11 3
#define sw12 2
#define servo1 4
#define led1 5

#define sw21 6
#define sw22 7
#define servo2 8
#define led2 9

#define sw31 10
#define sw32 11
#define servo3 12
#define led3 14  // A0

#define sw41 15  // A1
#define sw42 16  // A2
#define servo4 17 // A3
#define led4 18  // A4


#include <Servo.h>
Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
Servo myservo4;  // create servo object to control a servo

int pos1 = 0;    // variable to store the servo position
int pos2 = 0;    // variable to store the servo position
int pos3 = 0;    // variable to store the servo position
int pos4 = 0;    // variable to store the servo position

int posmin = 9; // minimum position of the servo
int posmax = 81; // maximum position of the servo
int delta = 5;  // error position

unsigned long  minipauza = 25;  // pentru reducere viteza, implicit e 15.. viteza scade daca numarul creste
int pauzamica = 250; // pauza mica pentru apasare buton
byte directie1 = 0;  // 0 - stop, 1 - left, 2 - right
byte directie10 = 3;
byte directie2 = 0;  // 0 - stop, 1 - left, 2 - right
byte directie20 = 3;
byte directie3 = 0;  // 0 - stop, 1 - left, 2 - right
byte directie30 = 3;
byte directie4 = 0;  // 0 - stop, 1 - left, 2 - right
byte directie40 = 3;

unsigned long tpcomanda1, tpcomanda2, tpcomanda3, tpcomanda4;

void setup() {
  Serial.begin(9600);
  Serial.println(" ");
  Serial.println("4 switches for railways on diorama");
  Serial.println("software wrote by Nicu FLORICA (niq_ro)");
  myservo1.attach(servo1);  // attaches the servo 
  myservo2.attach(servo2);  // attaches the servo 
  myservo3.attach(servo3);  // attaches the servo 
  myservo4.attach(servo4);  // attaches the servo 
  
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


pos1 = posmin;
pos2 = posmin;
pos3 = posmin;
pos4 = posmin;

  myservo1.write(pos1);              // tell servo to go to position in variable 'posmin'
  delay(pauzamica);
  myservo2.write(pos2);              // tell servo to go to position in variable 'posmin'
  delay(pauzamica);
  myservo3.write(pos3);              // tell servo to go to position in variable 'posmin'
  delay(pauzamica); 
  myservo4.write(pos4);              // tell servo to go to position in variable 'posmin'
  delay(pauzamica);
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
  pos1 = posmin;
  delay(pauzamica);
  tpcomanda1 = millis();
  }
  
  if ((digitalRead(sw12) == LOW) and (pos1 > posmax-delta))
  {
  Serial.println("Servo1 to Right!");
  directie1 = 2;
  pos1 = posmax;
  delay(pauzamica);
  tpcomanda1 = millis();
  }

  if ((digitalRead(sw21) == LOW) and (pos2 < posmin+delta))
  {
  Serial.println("Servo2 to Left !");
  directie2 = 1;
  pos2 = posmin;
  delay(pauzamica);
  tpcomanda2 = millis();
  }
  
  if ((digitalRead(sw22) == LOW) and (pos2 > posmax-delta))
  {
  Serial.println("Servo2 to Right!");
  directie2 = 2;
  pos2 = posmax;
  delay(pauzamica);
  tpcomanda2 = millis();
  }

  if ((digitalRead(sw31) == LOW) and (pos3 < posmin+delta))
  {
  Serial.println("Servo3 to Left !");
  directie3 = 1;
  pos3 = posmin;
  delay(pauzamica);
  tpcomanda3 = millis();
  }
  
  if ((digitalRead(sw32) == LOW) and (pos3 > posmax-delta))
  {
  Serial.println("Servo3 to Right!");
  directie3 = 2;
  pos3 = posmax;
  delay(pauzamica);
  tpcomanda3 = millis();
  }

  if ((digitalRead(sw41) == LOW) and (pos4 < posmin+delta))
  {
  Serial.println("Servo4 to Left !");
  directie4 = 1;
  pos4 = posmin;
  delay(pauzamica);
  tpcomanda4 = millis();
  }
  
  if ((digitalRead(sw42) == LOW) and (pos4 > posmax-delta))
  {
  Serial.println("Servo4 to Right!");
  directie4 = 2;
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
  }
  }

  if ((directie1 == 2) and (millis() - tpcomanda1 > minipauza))
  {
    myservo1.write(pos1);              // tell servo to go to position in variable 'pos'  
    pos1-=1;
    if (pos1 <= posmin) 
    {
      directie1 = 0;
    }
  }

 if ((directie2 == 1) and (millis() - tpcomanda2 > minipauza))
  { 
    myservo2.write(pos2);              // tell servo to go to position in variable 'pos'
    pos2+=1;
  if (pos2 >= posmax)
  {
    directie2 = 0;
  }
  }

  if ((directie2 == 2) and (millis() - tpcomanda2 > minipauza))
  {
    myservo2.write(pos2);              // tell servo to go to position in variable 'pos'  
    pos2-=1;
    if (pos2 <= posmin) 
    {
      directie2 = 0;
    }
  }

 if ((directie3 == 1) and (millis() - tpcomanda3 > minipauza))
  { 
    myservo3.write(pos3);              // tell servo to go to position in variable 'pos'
    pos3+=1;
  if (pos3 >= posmax)
  {
    directie3 = 0;
  }
  }

  if ((directie3 == 2) and (millis() - tpcomanda3 > minipauza))
  {
    myservo3.write(pos3);              // tell servo to go to position in variable 'pos'  
    pos3-=1;
    if (pos3 <= posmin) 
    {
      directie3 = 0;
    }
  }

 if ((directie4 == 1) and (millis() - tpcomanda4 > minipauza))
  { 
    myservo4.write(pos4);              // tell servo to go to position in variable 'pos'
    pos4+=1;
  if (pos4 >= posmax)
  {
    directie4 = 0;
  }
  }

  if ((directie4 == 2) and (millis() - tpcomanda4 > minipauza))
  {
    myservo4.write(pos4);              // tell servo to go to position in variable 'pos'  
    pos4-=1;
    if (pos4 <= posmin) 
    {
      directie4 = 0;
    }
  }


if (directie10 == 1)
{
  digitalWrite(led1, HIGH);  
}
if (directie10 == 2)
{
  digitalWrite(led1, LOW);    
}
if (directie20 == 1)
{
  digitalWrite(led2, HIGH);  
}
if (directie20 == 2)
{
  digitalWrite(led2, LOW);    
}
if (directie30 == 1)
{
  digitalWrite(led3, HIGH);  
}
if (directie30 == 2)
{
  digitalWrite(led3, LOW);    
}
if (directie40 == 1)
{
  digitalWrite(led4, HIGH);  
}
if (directie40 == 2)
{
  digitalWrite(led4, LOW);    
}


 directie10 = directie1;  
 directie20 = directie2;
 directie30 = directie3;
 directie40 = directie4;
 
delay(minipauza);
}  // end main loop
