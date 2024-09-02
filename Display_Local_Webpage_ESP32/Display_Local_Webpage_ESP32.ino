#include <WiFi.h>
#include <WebServer.h>
#include <DS1307.h>
#include "html.h"

WebServer server(80);

const char* ssid = "Prateek";       
const char* password = "justdoelectronics@#12345"; 

uint8_t sec, minute, hour, day, month;
uint16_t year;
DS1307 rtc;

void MainPage() {
  String _html_page = html_page;            
  server.send(200, "text/html", _html_page);  
}

void webRTC() {
  String data = "[\""+String(hour)+"\",\""+String(minute)+"\",\""+String(sec)+"\",\""+String(day)+"\",\""+String(month)+"\",\""+String(year)+"\"]";
  server.send(200, "text/plane", data);
}

void setup(void){
  Serial.begin(115200);      
  WiFi.mode(WIFI_STA);            
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  delay(1000);    
  while(WiFi.waitForConnectResult() != WL_CONNECTED){Serial.print(".");} 
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("Your Local IP address is: ");
  Serial.println(WiFi.localIP());     
 
  Serial.println("Init RTC...");
  rtc.begin();
  rtc.start();
  server.on("/", MainPage);           
  server.on("/readwebRTC", webRTC); 
  server.begin();                   
  delay(1000);                         
}

void loop(void){
  rtc.get(&sec, &minute, &hour, &day, &month, &year);
  Serial.print("\nTime: ");
  Serial.print(hour, DEC);
  Serial.print(":");
  Serial.print(minute, DEC);
  Serial.print(":");
  Serial.print(sec, DEC);

  Serial.print("\nDate: ");
  Serial.print(day, DEC);
  Serial.print(".");
  Serial.print(month, DEC);
  Serial.print(".");
  Serial.print(year, DEC);
  Serial.println("");
  server.handleClient();
  delay(1000);
}