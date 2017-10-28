/* -*- C++ -*- */
#ifndef RSITE_ONEKEY_DEF
  #define RSITE_ONEKEY_DEF

  #include <Arduino.h>

  // namespace RU {

    template<int longPress=500>
    struct OneKeyParams {};

    //use negative pin number for reverse logic pin and interbal pull-up
    template<
      int nr,
      // template<int longPress> class OneKeyParams,
      bool isOn,
      int pinNr
    >
    class OneKeyBase {
      public:
        enum State : unsigned char {
          Open = 0,
          Closed,
          Pressed,
          Held,
          Released,
          Clicked,
          DoubleClicked
        };
        inline void begin() {
          pinMode(pinNr,isOn?INPUT_PULLUP:INPUT);
          Serial.print("");Serial.println();
        }
        inline bool pin() {return digitalRead(pinNr);}
        State get() {
          if (pin()^isOn) {
            switch(state) {
              case Pressed: return Held;
              case Open: state=Pressed;
            }
          } else state=Open;
          return state;
        }
      protected:
        unsigned long lastChk;
        State state=Open;
    };

    template<int nr>
    class OneKey:public OneKeyBase<nr,nr<0,nr<0?-nr:nr> {};
  // };//namespace RU

#endif
