#ifdef DEBUG
  #include <streamFlow.h>
#endif

#include <OneArduino.h>

using namespace OneLib;
using namespace OneLib::Arduino;

#include <OneLib/Button.h>
#include <OneLib/ClickButton.h>

typedef InputPin<-4> Btn;
typedef OutputPin<13> Led;

Btn btn;
OnePinHook<Btn> btnHook(btn);
ClickButton<> oneBtn(btnHook);

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial<<"OneLib dev simple"<<endl;
  Btn::begin();
  Led::begin();
}

void loop() {
  if(oneBtn.get()==BtnState::Clicked) Led::tog();
}
