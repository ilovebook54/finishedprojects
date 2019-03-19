#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>



/*
   PIR sensor tester
*/
#include "IRremote.h"


int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected`
int times = 0;
int RECV_PIN = 11;
int val = 0;
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);
  pinMode(RECV_PIN, INPUT);

  // declare sensor as input
  // pinMode (//buttonPin, INPUT);
  // pinMode (//ledPin,OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

}


void loop()
{
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH and times == 0)
  {
    // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON

  } 

  else if (val == HIGH and times == 1)
  {
  
  digitalWrite(ledPin,LOW);
  
  }

  else if (pirState == LOW or HIGH and times == 1)
  {

  digitalWrite(ledPin,LOW);
  
  }
  
    if (pirState == LOW and times == 0)
    {
      // we have just turned on
      ////////Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
    
    if (irrecv.decode(&results))
    {
      Serial.println(results.value, HEX);
      Serial.print(results.value);

      if (results.value == 0xFD00F)
      {

        digitalWrite(ledPin, LOW);
        Serial.println("Inside if");
        times == 1;

      }

      else if (results.value == 0xFD08F7)
      {

        digitalWrite(ledPin, HIGH);
        Serial.println("elif");

      }

      irrecv.resume(); // Receive the next value

    }


  }








