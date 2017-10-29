/* -*- C++ -*- */
#ifndef RSITE_ONEKEY_DEF
  #define RSITE_ONEKEY_DEF

  #include "Pins/Arduino.h"

  //debouncer : pin overlay
  template<class O,int delta>
  class Debouncer:public O {
    public:
      using O::O;
      inline bool get(int pin) {
        return millis()-lastRead<delta?lastState:(lastRead=millis(),lastState=O::get(pin));
      }
    protected:
      unsigned long lastRead;
      bool lastState;
  };

  // template<
  //     int nr,
  //     bool isOn,
  //     int pinNr
  //   >
  // class Pin {
  //   virtual void pinMode() {}
  //   virtual bool read() {}
  //   virtual void write(bool) {}
  // };
  //
  // namespace RU {

    //use negative pin number for reverse logic pin and internal pull-up
    // template<
    //   int nr,
    //   bool isOn,
    //   int pinNr,
    //   int longPress
    // >
    // class OneKeyBase {
    //   public:
    //     // int t() {return params<500>.lp();}
    //     enum State : unsigned char {
    //       Open = 0,
    //       Closed,
    //       Pressed,
    //       Held,
    //       Released,
    //       Clicked,
    //       DoubleClicked
    //     };
    //     inline void begin() {
    //       pinMode(pinNr,isOn?INPUT_PULLUP:INPUT);
    //       Serial.print("");Serial.println();
    //     }
    //     inline bool pin() {return digitalRead(pinNr);}
    //     State get() {
    //       if (pin()^isOn) {
    //         switch(state) {
    //           case Pressed: return Held;
    //           case Open: state=Pressed;
    //         }
    //       } else state=Open;
    //       return state;
    //     }
    //   protected:
    //     unsigned long lastChk;
    //     State state=Open;
    // };
    //
    // template<int nr,int longPress=500>
    // using OneKey=OneKeyBase<nr,nr<0,nr<0?-nr:nr,longPress>;
  // };//namespace RU

#endif
