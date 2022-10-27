#include <string.h>
byte start = 0x7e; 
byte length1 = 0x00;
String mensaje1;
String mensaje2;
const char* mensaje;
byte length2;
byte typeFrame = 0;
byte frameId = 0;
byte macXbeeR[8] = {0x00, 0x13, 0xa2, 0x00, 0x41, 0x07, 0x89, 0x90};
byte options = 00;
int sumMac;
int sumMessage;
byte checksum;
void setup() {
  // put your setup code here, to run once:
    Serial2.begin(9600);
    Serial3.begin(9600); 
    Serial.begin(9600);   
}
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial2.available()){
    mensaje1 = Serial2.readString();
    Serial.println(mensaje1);
    mensaje2 = mensaje1.substring(0, mensaje1.length() - 2);
    Serial.print(mensaje2);
    mensaje = mensaje2.c_str();
    length2 = 9 + mensaje1.length();
    Serial.print(length2);
    for(int i = 0; i < sizeof(macXbeeR); i++){
      sumMac += macXbeeR[i];
    } 
    for(int i = 0; i <  strlen(mensaje); i++){
      sumMessage += mensaje[i];  
    }
    checksum = 0xff - ((sumMac + sumMessage) & 0xff);
    //Serial.println(checksum, HEX);
    Serial3.write(start); // Se envia 7E
    Serial.println(start, HEX);
    Serial3.write(length1);//
    Serial.println(length1, HEX);
    Serial3.write(length2);
    Serial.println(length2, HEX);
    Serial3.write(typeFrame);
    Serial.println(typeFrame, HEX);
    Serial3.write(frameId);
    Serial.println(frameId, HEX);
    for (int i = 0; i < sizeof(macXbeeR); i++){
      Serial3.write(macXbeeR[i]); 
      Serial.println(macXbeeR[i], HEX);  
    } 
    Serial3.write(options);
    Serial.println(options, HEX);
    Serial3.write(mensaje);
    Serial.println(mensaje);
    Serial3.write(checksum);
    Serial.println(checksum, HEX);
    delay(500);
    checksum = 0;
    mensaje = "";
    sumMac = 0;
    sumMessage = 0;
  }
}
