/*
 * This is a basic example on how to use Espalexa and its device declaration methods.
 */ 
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);

// Change this!!
const char* ssid = "TP-LINK_B3F5";
const char* password = "nihao843#";

boolean wifiConnected = false;

Espalexa espalexa;

// EspalexaDevice* device3; //this is optional
const int CONTROL_PIN = D0;

void setup()
{
  pinMode(CONTROL_PIN, OUTPUT);
  digitalWrite(CONTROL_PIN, LOW);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(115200);
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    
    // Define your devices here. 
    espalexa.addDevice("Desktop PC SW", firstLightChanged); //simplest definition, default state off
    // espalexa.addDevice("Light 2", secondLightChanged, 255); //third parameter is beginning state (here fully on)
    
    // device3 = new EspalexaDevice("Light 3", thirdLightChanged); //you can also create the Device objects yourself like here
    // espalexa.addDevice(device3); //and then add them
    // device3->setValue(128); //this allows you to e.g. update their state value at any time!

    espalexa.begin();
    
  } else
  {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}
 
void loop()
{
   espalexa.loop();
   delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness) {
    Serial.println("Power Switch");
    
    //do what you need to do here
    digitalWrite(CONTROL_PIN, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
    digitalWrite(CONTROL_PIN, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    // delay(1000);
    // digitalWrite(D0, HIGH);

    Serial.println("Power Switch down");

}

void secondLightChanged(uint8_t brightness) {
  //do what you need to do here
}

void thirdLightChanged(uint8_t brightness) {
  //do what you need to do here
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
