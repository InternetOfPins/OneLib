/* -*- C++ -*- */
#ifndef ONELIB_ARDUINO_DEF
  #define ONELIB_ARDUINO_DEF

#include "OneLib.h"

  namespace OneLib {
    namespace Arduino {
      template<int pin>
      struct PinBase {
        static inline void mode(uint8_t m) {pinMode(pin,m);}
        static inline void modeOut() {pinMode(pin,OUTPUT);}
        static inline void modeIn() {pinMode(pin,INPUT);}
        static inline void modeInUp() {pinMode(pin,INPUT_PULLUP);}
        static inline void on() {digitalWrite(pin,HIGH);}
        static inline void off() {digitalWrite(pin,LOW);}
        static inline bool in() {return digitalRead(pin);}
        template<bool T>
        static inline void set() {T?on():off();}
        static inline void set(bool v) {v?on():off();}
      };
      template<int pin>
      using Pin=LogicPinBase<PinBase<pin<0?-pin:pin>,pin<0>;
    };
  }//namespace OneLib

  // right now no advantage comes from this, we have no vpins yet
  // #define pinMode(p,m) Arduino::Pin<p>::mode(m)
  // #define digitalRead(p) Arduino::Pin<p>().in()
#endif
