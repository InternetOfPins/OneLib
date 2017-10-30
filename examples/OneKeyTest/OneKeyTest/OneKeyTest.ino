#include <OnePin/Arduino.h>
#include <OneKey.h>

//negative pin, OnePin will wire reverse logic
#define ENCBTN_PIN -4

class On {
  public:
    inline bool in() {return true;}
};

class Off {
  public:
    inline bool in() {return false;}
};

template<class O,int timeout=100,bool state=true>
class Until {
  public:
    inline bool in() {return millis()<timeout?state:!state;}
};

template<class O,int timeout=100,bool state=true>
class Next:protected O {
  protected:
    unsigned long start;
  public:
    Next():start(-1) {}
    inline bool in() {
      if (O::in()) start=millis();
      return millis()-start<timeout?state:!state;
    }
};

template<typename T>
class BinSource {
  // static T result;
  protected: BinSource() {}
  public: inline T read() {}
};

class Millis:public BinSource<unsigned long> {
  public: inline unsigned long read() {return millis();}
};

//toggle every a power of 2 in source count
template<class O,int P2>
class EveryBin:protected O {
  public:
    inline bool in() {return O::read()&(1<<P2);}
};

Debouncer<ArduinoPin,1000> debPin;//huge debounced pin 1s
OnePin<
  PinOutput,
  ArduinoPin,
  LED_BUILTIN
> led;//output led board

OnePin<
  PinInputUp,
  Debouncer<ArduinoPin,30>,
  ENCBTN_PIN
> btn;//pulled-up input with software debounce

OneKey<
  OnePin<
    PinInputUp,
    Debouncer<ArduinoPin,30>,
    ENCBTN_PIN
  >
> key;//key track from pulled-up input with software debounce, event emission Open|Pressed|Held|DoubleClicked|Timedout

Next<
  OnePin<
    PinInputUp,
    Debouncer<ArduinoPin,30>,
    ENCBTN_PIN
  >
  ,5000
> next;//whatch a debouced pulled-up input and hold `on` state for given time

EveryBin<Millis,8> ms;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  led.begin();
  btn.begin();
  key.begin();
}

void loop() {
  Serial<<"debPin:"<<debPin.get(4)<<" ";
  Serial<<"btn:"<<btn.in()<<" ";
  Serial<<"key:"<<key.read()<<" ";
  Serial<<"next:"<<next.in()<<" ";
  Serial<<"EveryBin:"<<ms.in()<<" ";
  Serial<<endl;
  //delay(300);
}
