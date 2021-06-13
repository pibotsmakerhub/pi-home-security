/* DISCLAIMER!!
 * 
 * Anyone Can Use or Edit as per the Following Conditions
 *    >> The User Must Leave this commented part as it is.
 *    >> The User must Mention Pi BOTS MakerHub when publishing.
 * 
 * If you have any Comments or Suggestions, 
 *  Send a message on:
 *    >> instagram.com/pi_bots
 *    >> instagram.com/at_mega_328p
 *    >> instagram.com/tech.xplorer
 *    
 *  >> About Pi BOTS MakerHub: 
 *    ___________________________
 *    Pi BOTS MakerHub is an Opensource Hardware Community and Training Center. 
 *    You can join our Community programs By joining our Community Groups. 
 *    To join, Send "Join" to wa.me/919400701088
 *    
 *  >> Watch the Video Tutorial to make sure you have done everything Correctly.
 *      https://youtu.be/61eE2Bfd7DQ
 *    
 *    --------- THANK YOU ---------
 * 
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiClient.h>

WiFiClient wifiClient;

const char* iftttURL = "http://maker.ifttt.com/trigger/ESP_MOTION/with/key/cngKKJ6py15q3adxlbAvq31ZdN4gFdDH50auMK1THjL";
const char* ssid = "SSID";          // Your WiFi Name.
const char* password = "PASSWORD";  // Your WiFi Password.
char auth[] = "dlCOw9k5nbI5xH4reO0uIfBpdLakRGXZ";      // Your Blynk Authentication token.

int pir = D1;               // PIR Data Pin

int state = 0;              // Turn on and off 
int pirVal = 0;             // Variable to store PiR Value.

WidgetLED led1(V0);         // Virtual LED on Blynk App (Configure with V0)

BLYNK_CONNECTED() {         // Syncing Hardware with Blynk Server when booting up.
  Blynk.syncAll();  
}

BLYNK_WRITE(V1) {           // Retrieve Data from Button to the Hardware Via Virtual pin 1.  
  state = param.asInt();
}

void setup () {

  Serial.begin(9600);                   // Initialize Serial Communication for debugging.
  WiFi.begin(ssid, password);           // Begin WiFi Connection

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }
  Blynk.begin(auth, ssid, password);    // Begin Blynk Server
}

void loop() {
  Blynk.run();                              // Run Blynk Code (It's Very Easy since we use <BlynkSimpleEsp8266> Library).
  pirVal = digitalRead(pir);                // Store status of PIR Sensor to the variable pirVal.
  if (state == 1) {                         // Conditional statement to check wether the user activated the device or not.
    led1.on();                              // if the Device activated, the LED widget on phone will turn on.
    if (pirVal == HIGH) {                   // Conditional statement to check the status of PIR Sensor.  
      if (WiFi.status() == WL_CONNECTED) {  // Check WiFi connection status

        HTTPClient http;                    // Declare an object of class HTTPClient

        http.begin(wifiClient, iftttURL);               // Specify request destination
        int httpCode = http.GET();          // Send the request
        Serial.println("Done");   

        if (httpCode > 0) {
          //Check the returning code

          String payload = http.getString();   // Get the request response payload
          Serial.println(payload);             // Print the response payload

        }

        http.end();                         // Close connection

      }
      delay(5000);                          // Run the code repeatedly, with a delay of 5 Seconds.  
    }

  }
  else {
    led1.off();                             // If Device is not activated, turn off the LED Widget.
  }
}
