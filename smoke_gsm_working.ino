#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2
int sensorThres = 400;
int smokeA0 = A5;
int red = 9;

void setup()

{
  pinMode(red, OUTPUT);
  pinMode(smokeA0, INPUT);
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
  updateSerial();
  
 mySerial.println("ATD+ +#;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  updateSerial();
  delay(1); // wait for 20 seconds...
  mySerial.println("ATH"); //hang up
  updateSerial();
}

void loop()
{
  while(mySerial.available()){
  Serial.println(mySerial.readString());
  int analogSensor = analogRead(smokeA0);
}
//////////////////////////////////////////////////
while(Serial.available())  {
  mySerial.println(Serial.readString());
  int analogSensor = analogRead(smokeA0);
}
//////////////////////////////////////////////////
  int analogSensor = analogRead(smokeA0);
  Serial.print("Pin A0: ");
  Serial.println(analogSensor);


  if (analogSensor > sensorThres) {
    mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
    updateSerial();

    Serial.println("Fire detected!");
    Serial.println("calling....");
    mySerial.println("ATD+ +254710562451;");
    updateSerial();
    delay(20000); //20 sec delay
    mySerial.println("ATH"); //hang up
    updateSerial();
    
    
  }

  delay(500);
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
