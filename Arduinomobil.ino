#include <Servo.h>

Servo MojServo;
#define trigPin 2
#define echoPin 3

// Define variables:
long duration;
int distance;
int stanje = HIGH;
int brzina = 180;
int kut=105;

const int senzor1Pin = 5;
const int senzor2Pin = 6;

void setup() {
  // Define inputs and outputs:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(senzor1Pin, INPUT);
  pinMode(senzor2Pin, INPUT);

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(10, stanje);
  analogWrite(11, brzina);

  MojServo.attach(9);
  //Begin Serial communication at a baudrate of 9600:
  Serial.begin(9600);
}

void loop() {

  int ocitanje1 = digitalRead(senzor1Pin);
 /* Serial.print("Vrijednost na senzoru1: ");
  Serial.print(ocitanje1);*/

  int ocitanje2 = digitalRead(senzor2Pin);
 /* Serial.print("Vrijednost na senzoru2: ");
  Serial.print(ocitanje2);*/

  if(ocitanje1==HIGH && ocitanje2==LOW){
    kut=kut-8;
  }

  if(ocitanje2==HIGH && ocitanje1==LOW){
    kut=kut+8;
  }

  if(ocitanje1==HIGH && ocitanje2==HIGH) {

    kut=105;
    MojServo.write(kut);
    
    // Clear the trigPin by setting it LOW:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);

    // Trigger the sensor by setting the trigPin high for 10 microseconds:
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
    duration = pulseIn(echoPin, HIGH);
    // Calculate the distance:
    distance= duration*0.034/2;

    // Print the distance on the Serial Monitor (Ctrl+Shift+M):
   /* Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");*/ 

    if(distance<=20) {
      if(stanje==HIGH){
        stanje=LOW;
        brzina=150;
        kut=kut-20;

        digitalWrite(10, stanje);
        analogWrite(11, brzina);
        MojServo.write(kut);
  
        delay(1000);
    
        stanje=HIGH;
        brzina=180;
        kut=kut+20;

        delay(20);
      }
    }
  }
  MojServo.write(kut);
  digitalWrite(10, stanje);
  analogWrite(11, brzina);
  delay(45);
}
