#include <OneKey.h>
#include <Arduino.h>

// using namespace RU;

#define ENCBTN_PIN -4

OneKey<ENCBTN_PIN> btn;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.print("OneKey test Sz:");
  Serial.println(sizeof btn);
  btn.begin();
}
void loop() {
  // Serial.println(btn.get());
  // Serial.println(btn.t());
  delay(200);
}
