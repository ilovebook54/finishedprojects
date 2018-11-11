#include <IRremote.h>
#include "pins_arduino.h"
#include <Servo.h>
Servo myservo; // create servo object to control a servo
int potpin = A0; // analog pin used to connect the potentiometer
int val; // variable to read t
int RECV_PIN = 11;//Pin should be PWM
int sensorPin = A5;
int ledPin = 13; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor
//#include "pins_arduino.h"
//int RECV_PIN = 11;//Pin should be PWM
int MAX_DISTANCE = 38;
const int trigPin = 1;
const int echoPin = 2;


IRrecv irrecv(RECV_PIN);

decode_results results;


long duration;
int distance;

void function_ultrasonic();



void setup()
{ 
  Serial.begin(9600);
  myservo.attach(9); // attaches the servo on pin 9 to the servo object
  irrecv.enableIRIn(); // Start the receiver
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);  
  pinMode(ledPin, OUTPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

}
void loop() {

  
//Serial.println("inside void loop");
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 179);
  myservo.write(val);     // sets the servo position according
  // to the scaled value
  //Serial.println(val);
  delay(15);


  sensorValue = analogRead(sensorPin);
  //Serial.println(sensorValue, DEC);


  if (sensorValue >= 699)
  {
    digitalWrite(ledPin,HIGH) ;   
  //  Serial.println("led on");
  }

  else if (sensorValue <= 499)
  {
    digitalWrite(ledPin, LOW);
    //Serial.println("led off");
  }


  //if (irrecv.decode(&results)) {
    //  function_ultrasonic();

  if (irrecv.decode(&results))
  {
   
    function_ultrasonic();
    
    switch (results.value)
    {
      case 0x511DBB:
      case 0xFF629D:  Serial.println("Forward"); // Button 2
        function_ultrasonic();
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        function_ultrasonic();
        break;
      case 0xA3C8EDDB:
      case 0xFFA857:  Serial.println("Backwards"); // Button 4
        function_ultrasonic();
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        digitalWrite(8, LOW);
        function_ultrasonic();
        break;
      case 0xD7E84B1B:
      case 0xFF02FD:  Serial.println("Stop"); // Button 5
        function_ultrasonic();
        digitalWrite(5, LOW);
        digitalWrite(6, LOW); 
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        function_ultrasonic();
        break;
      case 0xFFC23D:
      case 0x20FE4DBB:  Serial.println("Turn"); // Button 6
        function_ultrasonic();
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        function_ultrasonic();
        break;
/*        case FD807F:  //Serial.println("Right"); // Button 8  
                         int carspeed = ++ ;  



        case FD906F:  //Serial.println("Right"); // Button 8  
                         int carspeed = -1 ;  
*/
                             
      }  

    irrecv.resume(); // Receive the next value
  }
}  


void function_ultrasonic ()
{

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
 // Serial.print("Distance: ");
  //Serial.println(distance);

  if (distance <= 17)
  {
   // Serial.println("Ultrasonic");
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
  }


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
}
