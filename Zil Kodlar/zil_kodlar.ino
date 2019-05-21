#include <ESP8266WiFi.h>  //ESP8266 Wifi Modülünü programlamak için Kütüphane

int zil = 0;

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  WiFi.begin("Modemadi", "Modemsifresi");  //Bağalanılacak ağ adı ve şifresi
  server.begin();
  pinMode(zil, INPUT);
  delay(5000);  //Bağlanması için bir süre beklenir.
 
  Serial.print("Connecting");
  for (int i = 0; i<10; i++)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");  //IP adresi öğrenme
  Serial.println(WiFi.localIP());

}

void loop(){
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  //html kodları
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("");
  if( digitalRead(zil) == HIGH ){  //zile basıldığında adresin yanına /zil yazılır
    client.println("<a href=\"/zil\"\"></a>");
  }
  client.println("</html>");
}
