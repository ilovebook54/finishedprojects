#include <Servo.h> 
#include <IRremote.h>
#include "pins_arduino.h"
int sensorPin = A5; // select the input pin for the potentiometer
int ledPin = 13; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor
int RECV_PIN = 11;//Pin should be PWM
const int trigPin = 1;
const int echoPin = 2;


Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 

int pos = 0;    // variable to store the servo position 

// defines variables
long duration;
int distance;

/*
//Wherever you see 0x and number, those are codes ONLY for my remote. You need to find the codes for the remote you have.
//Here is a link to the place where I got the code: https://importgeek.wordpress.com/2013/02/19/send-tv-remote-signal-using-arduino/
//But, you need to add 0x in front of whatver code you get from the website
//You will need an IR remote, an old toy car, and a motor controller, ad Arduino Uno, and an infrared reciver
//You will need to unassemble the toy car and get the wires for the motors out. Then connect the wires to the motor controller.

 /*Arduino code for ir remote control car using the TSOP1738 ir sensor.
* Decode the button code, match and move robot according to button hex value.  
* For deocoding the hex values we use IRremote: IRrecvDemo.ino sketch from  
* https://www.pjrc.com/teensy/td_libs_IRremote.html. 
* By www.maxphi.com 
*/

IRrecv irrecv(RECV_PIN);

decode_results results;
void function_ultrasonic();

void setup()
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);  
}
void loop() {
  Serial.println(sensorValue, DEC);
  if (sensorValue > 500)
  {
    digitalWrite(ledPin,HIGH) ;   
  }
  else if (sensorValue < 499)
  {
    digitalWrite(ledPin, LOW);
  }
  sensorValue = analogRead(sensorPin);
  function_ultrasonic();
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(8,HIGH);
    myservo.write(90); 
    function_ultrasonic();                         
    //delay(1000);
    //function_ultrasonic(); 
    myservo.write(45);
    /*digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
     digitalWrite(8,LOW);*/
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
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= 17)
  {
    Serial.println("Ultrasonic");
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
     myservo.write(135);
  }


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

 
}

