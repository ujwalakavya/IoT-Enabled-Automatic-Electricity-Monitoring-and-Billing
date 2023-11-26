#include <ESP8266WiFi.h>

String apiWritekey = "FFOQ56PRNKWNTF6E"; // THINGSPEAK WRITEAPI key Energy Meter 
const char* ssid = "UK"; // wifi SSID name
const char* password = "kavya123" ;// wifi pasword
const char* server = "api.thingspeak.com";

#define powsen A0
static float power=1;
int count=0,input=0;
//int flag=0;
static int wific=0;
static int upload_count=0,z=0;
static int p_arr[30];


WiFiClient client;

long unsigned int publishInterval = 120000;//120000=2 min,300000=5 min, 9000000=15min, (3600000;1 hour),(60000;2 minutes)
long lastPublishMillis=0;

void setup() {
  Serial.begin(115200);
  pinMode(powsen, INPUT);
  wifiConnect();
}
void loop() {
  /*if(flag==0)
  {
     wifiConnect();
  }*/
 input=analogRead(powsen);
     if(input>450)
     {
      count++;
      power=(float)count/3.2;
      delay(100);
     }
     /*Serial.print("Input:");
     Serial.println(input);
     Serial.print("Count:");
     Serial.println(count);
     Serial.print("Power:");
     Serial.println(power);*/
   if (millis() - lastPublishMillis >= publishInterval) {
   upload();
   lastPublishMillis = millis();
 }
}
void wifiConnect() 
{
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();
  wific++;
  Serial.print("wifi Connect COunt: ");
  Serial.println(wific);
  //flag=1;
}
void upload() 
{ 
  if (client.connect(server,80))
  {  
    String tsData = apiWritekey;
           tsData +="&field1=";
           tsData += String(power);
           tsData += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(tsData.length());
     client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
     client.print(tsData);
 
     Serial.print("Energy (in Watts/day): ");
     Serial.print(power);
     Serial.println("uploaded to Thingspeak server....");
     upload_count++;
     if(upload_count==5)
     {
        if(wific>0) 
        {
          count=0;
          wific=0;
        }
          
        p_arr[z]=power;
        power=0;
        upload_count=0;
        z++;  
     }
     Serial.print(upload_count);
  }
  client.stop();
 
  Serial.println("Waiting to upload next reading...");
  Serial.println();
}
