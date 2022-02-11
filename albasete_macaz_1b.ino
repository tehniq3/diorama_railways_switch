/* Sweep by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.
 modified 8 Nov 2013 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep

adapted by Nicu FLORICA (niq_ro)

ver.1.0 - used barrier sketch https://github.com/tehniq3/diorama_barriers
ver.1.0.b - used one pin for control 2 leds + flashing internal led (D13)
*/

#define sw11 3
#define sw12 2
#define servo1 4

#define led1 5
#define led0 13 // internal led on board
 
#include <Servo.h>
Servo myservo1;  // create servo object to control a servo

int pos1 = 0;    // variable to store the servo position
int posmin = 9; // minimum position of the servo
int posmax = 81; // maximum position of the servo
int delta = 5;  // error position

unsigned long  minipauza = 25;  // pentru reducere viteza, implicit e 15.. viteza scade daca numarul creste
int pauzamica = 250; // pauza mica pentru apasare buton
byte directie1 = 0;  // 0 - stop, 1 - left, 2 - right
byte directie10 = 3;

unsigned long tpcomanda1;

void setup() {
  Serial.begin(9600);
  Serial.println(" ");
  Serial.println("diorama switch for railway");
  Serial.println("software wrote by Nicu FLORICA (niq_ro)");
  myservo1.attach(servo1);  // attaches the servo 

  pinMode(sw11, INPUT);
  pinMode(sw12, INPUT);
  digitalWrite(sw11, HIGH);  // rezistenta pull-up interna
  digitalWrite(sw12, HIGH);  // rezistenta pull-up interna

  pinMode(led0, OUTPUT); // 
  digitalWrite(led0, LOW);

  pinMode(led1, OUTPUT); // 
  digitalWrite(led1, LOW);
  delay(pauzamica);
  digitalWrite(led1, HIGH);
  delay(pauzamica);
  digitalWrite(led1, LOW);

  myservo1.write(posmin);              // tell servo to go to position in variable 'posmin'
  delay(1000);
}

void loop() {
  digitalWrite(sw11, HIGH);  // rezistenta pull-up interna
  digitalWrite(sw12, HIGH);  // rezistenta pull-up interna

   digitalWrite(led0, millis()/200%2);  // flash
  
  if ((digitalRead(sw11) == LOW) and (pos1 < posmin+delta))
  {
  Serial.println("Left !");
  directie1 = 1;
  pos1 = posmin;
  delay(pauzamica);
  tpcomanda1 = millis();
  }
  
  if ((digitalRead(sw12) == LOW) and (pos1 > posmax-delta))
  {
  Serial.println("Right!");
  directie1 = 2;
  pos1 = posmax;
  delay(pauzamica);
  tpcomanda1 = millis();
  }

  if ((directie1 == 1) and (millis() - tpcomanda1 > minipauza))
  { 
    myservo1.write(pos1);              // tell servo to go to position in variable 'pos1'
    pos1+=1;
  if (pos1 >= posmax)
  {
    directie1 = 0;
  }
  }

  if ((directie1 == 2) and (millis() - tpcomanda1 > minipauza))
  {
    myservo1.write(pos1);              // tell servo to go to position in variable 'pos1'  
    pos1-=1;
    if (pos1 <= posmin) 
    {
      directie1 = 0;
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
 directie10 = directie1;  
delay(minipauza);
}  // end main loop
