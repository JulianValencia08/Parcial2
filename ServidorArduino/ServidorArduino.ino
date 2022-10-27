#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


const char* ssid = "experienciaeafit3";          // nombre de la red
const char* password = "experiencia";

const char* html_page PROGMEM = "<!DOCTYPE html><html lang=\"en\"><head> <meta charset=\"UTF-8\"> <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <title>Parcial 2</title> <style type=\"text/css\"> body {background-color: rgba(214, 211, 211, 0.904);} .wrapper{display:flex;height: 600px;flex-direction: column; align-items: center;justify-content: center;} form{background-color: #999;padding: 50px; background-color:rgb(255, 255, 255); border:3px; border-radius:22px } h1 {color: rgb(7, 7, 7); text-align: center;font-family: tahoma; } h2 { text-align: center;} h3 { text-align: center; } .hola:hover { background-color: red; } </style></head><body> <div class=\"wrapper\"> <form action=\"\"> <h1>Ingrese el texto a mostrar</h1> <h2> <input type=\"text\" name=\"input\" style= \"background-color:rgb(255, 255, 255); border-color:rgba(3, 3, 3, 0.76); color:rgb(0, 0, 0); box-shadow: 0 4px #999; font-family: tahoma;\"></h2> <h3> <button class=\"hola\";value=\"Enviar\" style=\"background-color:rgb(154, 160, 219); border-color:rgba(255, 255, 255, 0); color:white; box-shadow: 0 6px #999; font-family: tahoma;\">Enviar</button></h3> </form> </div></body></html>";

char LedState[20];
ESP8266WebServer server(80); // (se pone el puerto)
String ledstate1;

// ip?LED=0/1
void handleRoot(){

  ledstate1 = server.arg("input");
  ledstate1.toCharArray(LedState,20);

  Serial.println(LedState);

/*
  if (LedState == "1"){
      digitalWrite(2,0);
    }
  if (LedState == "0"){
      digitalWrite(2,1);
    }
*/

  server.send(200, "text/html" ,html_page);
  
}

void setup(){

  pinMode(2, OUTPUT);
  
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);  //Wifi estacion
  WiFi.begin(ssid, password);

  server.on("/", handleRoot);
  server.begin();
  Serial1.begin(9600);
}


void loop() {
  server.handleClient();
  Serial1.write(LedState);

  
  
  /*
   int power = WiFi.RSSI();
  Serial.printf("Signal de dB %d\n", power);
  delay(5000);
 */
}
