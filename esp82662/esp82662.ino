#include <SoftwareSerial.h>       //Software Serial library
SoftwareSerial espSerial(2, 3);   //Pin 2 and 3 act as RX and TX. Connect them to TX and RX of ESP8266      
#define DEBUG true
String mySSID = "WiFi SSID";       // WiFi SSID
String myPWD = "WiFi Password"; // WiFi Password
String myAPI = "API Key";   // API Key
String myHOST = "api.thingspeak.com";
String myPORT = "80";
String myFIELD = "field1"; 
int sendVal;


void setup()
{
  Serial.begin(9600);
  espSerial.begin(115200);
  
  espData("AT+RST\r\n", 1000, DEBUG);                      //Reset the ESP8266 module
  delay(5000);
  espData("AT+CWMODE=1\r\n", 1000, DEBUG);                 //Set the ESP mode as station mode
  delay(5000);
  espData("AT+CWJAP=\""+ mySSID +"\",\""+ myPWD +"\"\r\n", 1000, DEBUG);   //Connect to WiFi network
 delay(5000);
  /*while(!esp.find("OK")) 
  {          
      //Wait for connection
  }*/
  delay(5000);
  
}

  void loop()
  {
    /* Here, I'm using the function random(range) to send a random value to the 
     ThingSpeak API. You can change this value to any sensor data
     so that the API will show the sensor data  
    */
    
    sendVal = random(1000); // Send a random number between 1 and 1000
    String sendData = "GET /update?api_key="+ myAPI +"&"+ myFIELD +"="+String(sendVal);
    espData("AT+CIPMUX=1\r\n", 1000, DEBUG);       //Allow multiple connections
    delay(5000);
    espData("AT+CIPSTART=0,\"TCP\",\""+ myHOST +"\","+ myPORT+"\r\n", 1000, DEBUG);
   delay(5000);
    espData("AT+CIPSEND=0," +String(sendData.length()+4)+"\r\n",1000,DEBUG);  
   delay(1000);
    espSerial.find(">"); 
    espSerial.println(sendData);
    Serial.print("Value to be sent: ");
    Serial.println(sendVal);
     
    espData("AT+CIPCLOSE=0\r\n",1000,DEBUG);
    delay(10000);
  }

  String espData(String command, const int timeout, boolean debug)
{
  Serial.print("AT Command ==> ");
  Serial.print(command);
  Serial.println("     ");
  
  String response = "";
  espSerial.println(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (espSerial.available())
    {
      char c = espSerial.read();
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
  
