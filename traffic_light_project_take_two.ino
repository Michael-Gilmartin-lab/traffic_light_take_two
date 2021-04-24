int motionSensor = 8;
int PIR_STATE = LOW;
int VALUE = 0;

int red = 4; 
int green = 2;
int yellow = 3;
int buzzer = 7;
int counter = 0;
int personCounter = 0;


  char devid[] = "v9DBBAB61CC940D2";
  

char serverName[] = "api.pushingbox.com";
boolean DEBUG = true;
#include <Bridge.h>
#include <HttpClient.h>

void setup()  { 
  
  pinMode(motionSensor, INPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzzer, OUTPUT);


  Bridge.begin();
  Serial.begin(9600);

  
} 

void loop(){
   digitalWrite(red, HIGH); // Turns red LED on. This will stay on until motion is detected 
   
  VALUE = digitalRead(motionSensor); // Waits for motion to be detected
  
  if (VALUE == HIGH)
    {
      personCounter++;

      digitalWrite(buzzer, HIGH); // Makes sound to let someone know motion has been detected 
      delay(70);
      digitalWrite(buzzer, LOW);
      delay(200);
      digitalWrite(buzzer, HIGH); 
      delay(70);
      digitalWrite(buzzer, LOW);
  
      delay(3000); // Small delay once motion detected
      digitalWrite(red, LOW); //  Turns red LED off
      delay(0);

      // Light in process of changing to allow people to cross

      digitalWrite(yellow, HIGH); // Turns yellow LED on
      delay(3000); // small delay for yellow LED
      digitalWrite(yellow, LOW); //  Turns yellow  LED off
      delay(0);


      digitalWrite(green, HIGH); // Turns green LED on

        while(counter <= 40)
        {
          digitalWrite(buzzer, HIGH); // Rapid buzzer so people have an audible cue along with a visual one  
          delay(50);
          digitalWrite(buzzer, LOW);
          delay(200);
          counter++;
        }
    
      counter = 0;

    digitalWrite(green, LOW); //  Turns green LED off
    delay(200);

    if(personCounter >= 0) // change this value to change the frequency the reports are sent to the spreadsheet 
    {
      // Initialize the client library
  HttpClient client;
 
  String APIRequest;
  APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid)+ "&IDtag=100&TimeStamp=50&TempC="+personCounter;
  client.get (APIRequest);
  

  while (client.available()) {
    char c = client.read();

  }
  Serial.flush();
  String UploadMessage;
  Serial.print("\n Uploaded traffic light values: ");
  Serial.print(personCounter);
  
      
      }
  }
  

}
