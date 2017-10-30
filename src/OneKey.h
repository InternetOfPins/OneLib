/* -*- C++ -*- */
#ifndef RSITE_ONEKEY_DEF
  #define RSITE_ONEKEY_DEF


  #include "OnePin/Arduino.h"

  template<class O,int longPress>
  class OneKeyBase {
    public:
      // int t() {return params<500>.lp();}
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
        O::modeIn();
        Serial.print("");Serial.println();
      }
      State get() {
        if (O::get()) {
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

  template<class O,int longPress=300>
  using OneKey=OneKeyBase<O,longPress>;

#endif
