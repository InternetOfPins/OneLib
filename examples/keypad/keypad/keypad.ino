#include <OneArduino.h>
#include <OneLib/KeyMatrix.h>
using namespace OneLib::Arduino;


using KeyData=PinCap<
  PinGroup<
    InputPin<-2>,
    InputPin<-3>
  >
>;
using KeyScan=PinCap<PinGroup<OutputPin<-4>,OutputPin<-5>>>;

using Keypad=KeyMatrix<
  OneLib::Arduino::API,
  KeyData,
  KeyScan
>;
// char keymap[2][2]{{'*','/'},{'+','-'}};
Keypad keypad({'*','/'},{'+','-'});

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("OneLib, testing pin groups and pin specs");
  Keypad::begin();
}
void loop() {}
