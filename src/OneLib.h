/* -*- C++ -*- */
#ifndef ONELIB_DEF
  #define ONELIB_DEF

  #include <avr/io.h>
  #ifdef DEBUG
    #include <streamFlow.h>
  #endif

  namespace OneLib {

    template<class T>
    struct Mem {
      static inline T get(T* addr) {return *addr;}
      static inline T set(T* addr,T v) {return *addr=v;}
    };

    //void pin, use this if no pin is to be used
    struct VoidPin {
      static inline void modeOut() {}
      static inline void modeIn() {}
      static inline void modeInUp() {}
      static inline void on() {}
      static inline void off() {}
      static inline bool in() {return false;}
      inline operator bool() {return in();}
    } voidPin;//or its objective version

    template<class O,bool isOn>
    class LogicPinBase:public O {
      public:
        inline bool in() {return this->O::in()^isOn;}
        static inline void on() {isOn?O::off():O::on();}
        static inline void off() {isOn?O::on():O::off();}
        inline operator bool() {return this->in();}
    };

    template<class O,unsigned long delta>
    class Debouncer:public O {
      public:
        inline bool in() {
          if (millis()-lastOn<delta) return true;
          else if (this->O::in()) {
            lastOn=millis();
            return true;
          }
          return false;
        }
        inline operator bool() {return in();}
      protected:
        unsigned long lastOn=-delta;
    };
  };
#endif
