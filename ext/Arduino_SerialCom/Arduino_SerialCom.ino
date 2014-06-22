/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int counter=0;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(15);               // wait for a some time
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(10);               // wait for a some time
  

    String msg = String("[Sensor1Data,"); //send sensor data in this format "[Sensor1Data,500]"
    String temp = msg + counter + "]" ;
    char* cString = (char*) malloc(sizeof(char)*(temp.length() + 1));
    temp.toCharArray(cString, temp.length() + 1);
    Serial.write(cString);
    delete cString;
    counter ++;
    if (counter == 1024)
        counter = 0; //reset counter
  
  
}

void serialEvent(){

  
}


