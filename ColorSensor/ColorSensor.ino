/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 10
#define COMMON_ANODE
// Stores frequency read by the photodiodes
int redPin = 11;
int greenPin = 8;
int bluePin = 9;
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;



void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,HIGH);
  
   // Begins serial communication 
  Serial.begin(9600);
}
void loop() {
 /* // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  
   // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(redFrequency);
  //delay(1000);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(greenFrequency);
  //delay(1000);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.println(blueFrequency);
  delay(2000);


  setColor(redFrequency, greenFrequency, blueFrequency);
*/
  color();
  Serial.print("R Intensity:");  
  Serial.print(redFrequency, DEC);  
  Serial.print(" G Intensity: ");  
  Serial.print(greenFrequency, DEC);  
  Serial.print(" B Intensity : ");  
  Serial.print(blueFrequency, DEC);  
  Serial.println();
  delay(1000);
  if (redFrequency < blueFrequency && redFrequency < greenFrequency && redFrequency < 20)
  {  
   Serial.println(" - (Red Color)");  
   setColor(255,0,0);
   delay(1000);
  }  

  else if (blueFrequency < redFrequency && blueFrequency < greenFrequency)   
  {  
   Serial.println(" - (Blue Color)");  
   setColor(0,0,255);
  delay(1000);
  }  

  else if (greenFrequency < redFrequency && greenFrequency < blueFrequency)  
  {  
   Serial.println(" - (Green Color)");  
   setColor(0,255,0);
 delay(1000);
  }  
  else{
  Serial.println();
  setColor(0,0,0);  
  }

}





void color()  
{    
  digitalWrite(S2, LOW);  
  digitalWrite(S3, LOW);  
  //count OUT, pRed, RED  
  redFrequency = pulseIn(sensorOut, digitalRead(sensorOut) == HIGH ? LOW : HIGH);  
  digitalWrite(S3, HIGH);  
  //count OUT, pBLUE, BLUE  
  blueFrequency = pulseIn(sensorOut, digitalRead(sensorOut) == HIGH ? LOW : HIGH);  
  digitalWrite(S2, HIGH);  
  //count OUT, pGreen, GREEN  
  greenFrequency = pulseIn(sensorOut, digitalRead(sensorOut) == HIGH ? LOW : HIGH);  
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}


