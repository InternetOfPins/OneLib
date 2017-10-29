/* -*- C++ -*- */
#ifndef RSITE_ONEKEY_DEF
  #define RSITE_ONEKEY_DEF

  // namespace RU {

    #include "OnePin/Arduino.h"

    //   use negative pin number for reverse logic pin and internal pull-up
    // template<
    //   int nr,
    //   bool isOn,
    //   PinNr pinNr,
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
    // template<int nr>
    // using OneKey=OneKeyBase<nr,nr<0,nr<0?-nr:nr>;
  // };//namespace RU

#endif
