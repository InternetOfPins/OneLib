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
      static inline T get(const T* addr) {return *addr;}
      static inline T set(T* addr,const T v) {return *addr=v;}
    };

    //void pin, use this if no pin is to be used
    struct VoidPin {
      inline operator bool() {return in();}
      static inline void modeOut() {}
      static inline void modeIn() {}
      static inline void modeInUp() {}
      static inline void on() {}
      static inline void off() {}
      static inline bool in() {return false;}
      template<bool T>
      static inline void set() {T?on():off();}//compiletime
      static inline void set(bool v) {v?on():off();}//runtime
    } voidPin;//or its objective version

    //if needed invert pin logic or be absent : constexpr^0
    template<class O,bool isOn>
    class LogicPinBase:public O {
      public:
        inline bool in() {return this->O::in()^isOn;}
        static inline void on() {isOn?O::off():O::on();}
        static inline void off() {isOn?O::on():O::off();}
        inline operator bool() {return this->in();}
    };

    //debounce the `on` state of a pin
    template<class O,unsigned long delta>
    class DebounceOn:public O {
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

    //debounce pin state change
    template<class O,unsigned long delta>
    class Debounce:public O {
      public:
        inline bool in() {
          if (millis()-lastSet<delta) return lastState;
          lastSet=millis();
          return lastState=O::in();
        }
        inline operator bool() {return in();}
      protected:
        unsigned long lastSet=-delta;
        bool lastState;
    };

    template<class O,unsigned long delta>
    using Debouncer=Debounce<O,delta>;
  };
#endif
