#include <IRremote.h>
#include "pins_arduino.h"
int RECV_PIN = 11;//Pin should be PWM
int sensorPin = A5; // select the input pin for the potentiometer
int ledPin = 13; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{ 
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);  
  pinMode(ledPin, OUTPUT);
}
void loop() {

  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue, DEC);


  if (sensorValue >= 699)
  {
    digitalWrite(ledPin,HIGH) ;   
    Serial.println("led on");
  }

  else if (sensorValue <= 499)
  {
    digitalWrite(ledPin, LOW);
    Serial.println("led off");
  }





  if (irrecv.decode(&results)) {
      switch(results.value)
      //Serial.println(results.value);
      {        
        case 0xFF629D:  Serial.println("Forward"); // Button 2  
                         digitalWrite(5,LOW);
                         digitalWrite(6,HIGH);
                         digitalWrite(7,LOW);
                         digitalWrite(8,HIGH);
                         break;       
        case 0xFFA857 :  Serial.println("Backward"); // Button 4
                         digitalWrite(5,HIGH);
                         digitalWrite(6,LOW);
                         digitalWrite(7,HIGH);
                         digitalWrite(8,LOW);
                         break; 
        case 0xFF02FD:  Serial.println("Stop"); // Button 5
                         digitalWrite(5,HIGH);
                         digitalWrite(6,HIGH);
                         digitalWrite(7,HIGH);
                         digitalWrite(8,HIGH);
                         break; 
        case 0xFF22DD:  Serial.println("anti-clockwise"); // Button 6
                         digitalWrite(5,LOW);
                         digitalWrite(6,LOW);
                         digitalWrite(7,HIGH);
                         digitalWrite(8,LOW);
                         break;        
                        
                         
        case 0xFFC23D:  Serial.println("clockwise"); // Button 8  
                         digitalWrite(5,HIGH);
                         digitalWrite(6,LOW);
                         digitalWrite(7,HIGH);
                         digitalWrite(8,HIGH);
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

