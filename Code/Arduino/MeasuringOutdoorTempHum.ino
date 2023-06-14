#include "DHT.h"
#include "WiFi.h"
#include "ThingSpeak.h"
#include<stdlib.h>


#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


const char *ssid =  "ssid name";     
const char *pass =  "password";


WiFiClient  client;

unsigned long myChannelNumber = 8888888;
const char * myWriteAPIKey = "****************";

unsigned long lastTime = 0;
unsigned long timerDelay = 600000; // interval 10 minutes


String myStatus = "";


void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, pass);
  Serial.println("Connecting..");
  // Connect to WiFi
    while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  lastTime = millis();
  float t = dht.readTemperature(); // Reads the temperature in degrees Celsius
  float h = dht.readHumidity();  // Reads the humidity in %
  if (isnan(h) || isnan(t)) {
  Serial.println("Failed to read from DHT sensor!");
  return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C, ");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);
   
  // set the status
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else
  {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
}



void loop() {

delay(2000);

if ((millis() - lastTime) > timerDelay) {
    
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect");
    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");  
    } 
    Serial.println("");
    Serial.println("WiFi connected");
  }
    
float t = dht.readTemperature(); // Reads the temperature in degrees Celsius
    
float h = dht.readHumidity();  // Reads the humidity in %

if (isnan(h) || isnan(t)) {
  Serial.println("Failed to read from DHT sensor!");
  return;
}

Serial.print("Temperature: ");
Serial.print(t);
Serial.println("°C, ");
Serial.print("Humidity: ");
Serial.print(h);
Serial.println(" %");

ThingSpeak.setField(1, t);
ThingSpeak.setField(2, h);
   
// set the status
ThingSpeak.setStatus(myStatus);
  
// write to the ThingSpeak channel
int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
if(x == 200){
  Serial.println("Channel update successful.");
}
else
{
  Serial.println("Problem updating channel. HTTP error code " + String(x));
}

lastTime = millis();
}
}


