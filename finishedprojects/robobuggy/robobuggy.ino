#include <IRremote.h>
#include "pins_arduino.h"
int RECV_PIN = 11;//Pin should be PWM
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

void setup()
{ 
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);  
}
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
      switch(results.value)
      {        
        case 0x16736925 or 0x:16736925  //Serial.println("Forward"); // Button 2  
                         
                         digitalWrite(5,LOW);
                         digitalWrite(6,HIGH);
                         digitalWrite(7,LOW);
                         digitalWrite(8,HIGH);
                         break;       
        case 0xFD10EF:  //Serial.println("Backwards"); // Button 4
                         digitalWrite(5,HIGH);
                         digitalWrite(6,LOW);
                         digitalWrite(7,HIGH);
                         digitalWrite(8,LOW);
                         break; 
        case 0xFD00FF:  //Serial.println("Stop"); // Button 5
                         digitalWrite(5,LOW);
                         digitalWrite(6,LOW);
                         digitalWrite(7,LOW);
                         digitalWrite(8,LOW);
                         break; 
        case 0xFD08F7:  //Serial.println("Left"); // Button 6
                         digitalWrite(5,HIGH);
                         digitalWrite(6,HIGH);
                         digitalWrite(7,LOW);
                         digitalWrite(8,HIGH);
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
