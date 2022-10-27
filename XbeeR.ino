#include <LiquidCrystal.h> 
 
LiquidCrystal lcd(48,49,45,44,43,42);

void setup(){
  pinMode(47, OUTPUT);
  digitalWrite(47, 0);
  Serial3.begin(9600);
  Serial.begin(9600);
    lcd.begin(16, 2);

}

void loop(){
  if(Serial3.available()){
      lcd.clear();
      delay(100);
      String caracter = Serial3.readString();
      String sub = caracter.substring(15,caracter.length() - 1);
      Serial.print(sub);
      lcd.print(sub);
      lcd.setCursor(0, 1); 
  }
}
