//  UV light on off option added on 21-04-20 . tested ok

// Servo motorcode added 




#define UVLight  4           //Uv light            GPIO0(D2)
 

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>





String command="";             //String to store app command state.


const char* ssid = "NodeMCU Car";
ESP8266WebServer server(80);

void setup() {
 

 pinMode(LED_BUILTIN, OUTPUT);  



  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}





void UVLightOn(){ 

      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("UVLightOn()");
      
  }

void UVLightOff(){ 

      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("UVLightOff()");
      
  }


void loop() {
    server.handleClient();
    
      command = server.arg("State");
     
   
  if (command == "E") UVLightOn();
else if (command == "R") UVLightOff();








}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
