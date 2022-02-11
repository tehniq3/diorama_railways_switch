/* Sweep by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.
 modified 8 Nov 2013 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep

adapted by Nicu FLORICA (niq_ro)

ver.1.0 - use barrier sketch https://github.com/tehniq3/diorama_barriers
*/

#define deplasare1 3
#define revenire1 2
#define servo1 4

#define led1 5
#define led2 6
 
#include <Servo.h>
Servo myservo1;  // create servo object to control a servo

int pos1 = 0;    // variable to store the servo position
int posmin = 9; // minimum position of the servo
int posmax = 81; // maximum position of the servo

unsigned long  minipauza = 25;  // pentru reducere viteza, implicit e 15.. viteza scade daca numarul creste
int pauzamica = 250; // pauza mica pentru apasare buton
byte directie1 = 0;  // 0 - stop, 1 - deplasare, 2 - revenire
byte directie10 = 3;

unsigned long tpcomanda1;

void setup() {
  Serial.begin(9600);
  Serial.println(" ");
  Serial.println("Macaz simplu...");
  Serial.println("program scris de Nicu FLORICA (niq_ro)");
  myservo1.attach(servo1);  // attaches the servo 

  pinMode(deplasare1, INPUT);
  pinMode(revenire1, INPUT);
  digitalWrite(deplasare1, HIGH);  // rezistenta pull-up interna
  digitalWrite(revenire1, HIGH);  // rezistenta pull-up interna

  pinMode(led1, OUTPUT); // 
  pinMode(led2, OUTPUT); //   
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  delay(pauzamica);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  delay(pauzamica);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH); 

  myservo1.write(posmin);              // tell servo to go to position in variable 'pos'
  delay(1000);
}

void loop() {
  digitalWrite(deplasare1, HIGH);  // rezistenta pull-up interna
  digitalWrite(revenire1, HIGH);  // rezistenta pull-up interna
  
  if ((digitalRead(deplasare1) == LOW) and (pos1 < posmax))
  {
  Serial.println("Deplasare !");
  directie1 = 1;
  pos1 = posmin;
  delay(pauzamica);
  tpcomanda1 = millis();
  }
  
  if ((digitalRead(revenire1) == LOW) and (pos1 > posmin))
  {
  Serial.println("Revenire!");
  directie1 = 2;
  pos1 = posmax;
  delay(pauzamica);
  tpcomanda1 = millis();
  }

  if ((directie1 == 1) and (millis() - tpcomanda1 > minipauza))
  { 
    myservo1.write(pos1);              // tell servo to go to position in variable 'pos'
    delay(minipauza);  
    pos1+=1;
  if (pos1 >= posmax)
  {
    directie1 = 0;
  }
 // tpcomanda1 = millis();
  }

  if ((directie1 == 2) and (millis() - tpcomanda1 > minipauza))
  {
    myservo1.write(pos1);              // tell servo to go to position in variable 'pos'
    delay(minipauza);  
    pos1-=1;
    if (pos1 <= posmin) 
    {
      directie1 = 0;
    }
  //az  tpcomanda1 = millis();
  }

if (directie10 == 1)
{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);    
}
if (directie10 == 2)
{
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);    
}
 directie10 = directie1; 
delay(1);  
}  // end main loop
