/*Arduino code for ir remote control car using the TSOP1738 ir sensor.
  Decode the button code, match and move robot according to button hex value.
  For deocoding the hex values we use IRremote: IRrecvDemo.ino sketch from
  https://www.pjrc.com/teensy/td_libs_IRremote.html.
  By www.maxphi.com
*/

#include <IRremote.h>
#include "pins_arduino.h"
int RECV_PIN = 11;//Pin should be PWM
int MAX_DISTANCE = 38;
const int trigPin = 1;
const int echoPin = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;



//NewPing sonar(trigPin, echoPin, MAX_DISTANCE); // NewPing setup of pins and maximum distance.



long duration;
int distance;

void function_ultrasonic();


void setup()
{
  irrecv.enableIRIn(); // Start the receiver
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}
void loop()
{

  function_ultrasonic();

  if (irrecv.decode(&results))
  {
    switch (results.value)
    {
      case 0xFF629D:  Serial.println("Forward"); // Button 2
        function_ultrasonic();
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        function_ultrasonic();
        break;
      case 0xFFA857:  Serial.println("Backwards"); // Button 4
        function_ultrasonic();
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        digitalWrite(8, LOW);
        function_ultrasonic();
        break;
      case 0xFF02FD:  Serial.println("Stop"); // Button 5
        function_ultrasonic();
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        function_ultrasonic();
        break;
      case 0xFFC23D:  Serial.println("Turn Right"); // Button 6
        function_ultrasonic();
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        function_ultrasonic();
        break;

       
        /*case 0x1FEF00F:  //Serial.println("Right"); // Button 8
                         digitalWrite(5,LOW);
                         digitalWrite(6,HIGH);
                         digitalWrite(7,HIGH);
                         digitalWrite(8,LOW);
                         break; */


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
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 5 && distance > 0)
  {
    Serial.println("Ultrasonic");
   Serial.print("Distance: ");
    Serial.println(distance);

    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
  }


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
}
