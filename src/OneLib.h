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
      // static inline void setLast(bool) {}
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

    //pin state record
    // template<class O>
    class LastState/*:public O*/ {
      // public:
      //   inline LastState():lastState(O::in()) {}
      //   inline bool in() {return O::in();}
      protected:
        inline bool getLast() {return lastState;}
        inline bool setLast(bool v) {return lastState=v;}
        bool lastState;
    };

    //pin state record
    template<class O>
    class RecState:public O,protected virtual LastState {
      public:
        inline bool in() {return setLast(O::in());}
    };

    //debounce the `on` state of a pin
    template<class O,unsigned long delta>
    class DebounceOn:public O,protected virtual LastState {
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
    class Debounce:public O,protected virtual LastState {
      public:
        inline bool in() {
          if (millis()-lastSet<delta) return getLast();
          lastSet=millis();
          return O::in();
        }
        inline operator bool() {return in();}
      protected:
        unsigned long lastSet=-delta;
    };

    template<class O,unsigned long delta>
    using Debouncer=Debounce<O,delta>;

    //attach an action to pin change (input)
    //when pin changes
    template<class O,void(*f)()>
    class OnChange:public O,protected virtual LastState {
      public:
        OnChange() {}
        inline operator bool() {return in();}
        inline bool in() {
          bool n=O::in();
          if (n!=O::getLast()) f();
          return n;
        }
    };
    //when pin rises
    template<class O,void(*f)()>
    class OnRise:public O,protected virtual LastState {
      public:
        inline operator bool() {return in();}
        inline bool in() {
          bool n=O::in();
          if (n&&n!=O::getLast()) f();
          return n;
        }
    };
    //when pin falls
    template<class O,void(*f)()>
    class OnFall:public O,protected virtual LastState {
      public:
        inline operator bool() {return in();}
        inline bool in() {
          bool n=O::in();
          if (!(n||n==O::getLast())) f();
          return n;
        }
    };

    class VPinBase {
      public:
        inline operator bool() {return in();}
        template<uint8_t M> void mode();
        inline void mode(const uint8_t m) {
          switch(m) {
            case OUTPUT: modeOut();break;
            case INPUT: modeIn();break;
            case INPUT_PULLUP: modeInUp();break;
          }
        }
        virtual void modeOut()=0;
        virtual void modeIn()=0;
        virtual void modeInUp()=0;
        virtual void on()=0;
        virtual void off()=0;
        virtual bool in()=0;
        template<bool T>
        inline void set() {T?on():off();}//compiletime
        inline void set(bool v) {v?on():off();}//runtime
    };
    template<>void VPinBase::mode<OUTPUT>() {modeOut();}
    template<>void VPinBase::mode<INPUT>() {modeIn();}
    template<>void VPinBase::mode<INPUT_PULLUP>() {modeInUp();}

    template<class O>
    class VPin:public VPinBase  {
      public:
        // VPin():pin(O()) {}
        VPin(O& o):pin(o) {}
        virtual void modeOut() {pin.modeOut();}
        virtual void modeIn() {pin.modeIn();}
        virtual void modeInUp() {pin.modeInUp();}
        virtual void on() {pin.on();}
        virtual void off() {pin.off();}
        virtual bool in() {return pin.in();}
      protected:
        O& pin;
    };

  };
#endif
