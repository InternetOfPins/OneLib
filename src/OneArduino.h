/* -*- C++ -*- */
#ifndef ONELIB_ARDUINO_DEF
  #define ONELIB_ARDUINO_DEF

#include "OneLib.h"

  namespace OneLib {
    namespace Arduino {

      #define CHRONOMETER

      static inline unsigned long getMillis() {return millis();}

      #include "OneLib/HAL/Mem.h"
      #include "OneLib/HAL/Func.h"
      #include "OneLib/HAL/Pin.h"

      #include "OneLib/Soft/Debounce.h"
      #include "OneLib/Soft/Wire.h"

      #include "OneLib/Driver/OnePin.h"
      #include "OneLib/Driver/Encoder.h"
      #include "OneLib/Driver/AccelEncoder.h"
      #include "OneLib/Driver/Button.h"
      #include "OneLib/Driver/ClickButton.h"


      template<const int pin>
      struct PinBase {
        static inline void begin() {}
        static inline void mode(const uint8_t m) {pinMode(pin,m);}
        static inline void modeOut() {pinMode(pin,OUTPUT);}
        static inline void modeIn() {pinMode(pin,INPUT);}
        static inline void modeInUp() {pinMode(pin,INPUT_PULLUP);}
        static inline bool in() {return digitalRead(pin);}
        static inline bool rawIn() {return digitalRead(pin);}
        static inline bool logicIn() {return digitalRead(pin);}
        static inline void on() {digitalWrite(pin,HIGH);}
        static inline void off() {digitalWrite(pin,LOW);}
        template<bool T>
        static inline void set() {T?on():off();}
        static inline void set(bool v) {v?on():off();}
      };
      template<int pin>
      using Pin=LogicPinBase<PinBase<pin<0?-pin:pin>,pin<0>;

      template<const int pin>
      struct InputPin:public Pin<pin> {
        static inline void begin() {if (pin<0) Pin<pin>::modeInUp(); else Pin<pin>::modeIn();}
      };
      template<const int pin>
      struct OutputPin:public Pin<pin> {
        static inline void begin() {Pin<pin>::modeOut();}
      };
    };
  }//namespace OneLib
#endif
