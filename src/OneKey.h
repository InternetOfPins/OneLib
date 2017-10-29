/* -*- C++ -*- */
#ifndef RSITE_ONEKEY_DEF
  #define RSITE_ONEKEY_DEF

  #include <Arduino.h>

  enum PinMode {Off,Out,In,InUp,InDown};

  //r-Site pins API
  template<
    bool (*_get)(int)
  > struct InputPin {
    bool get(int p) {return (*_get)(p);}
  };

  // template<
  //   void (*_set)(int,bool),
  //   void (*_on)(int p),
  //   void (*_off)(int p)
  // > class OutputPin {
  //   void set(int p,bool o) {(*_set)(p,o);}
  //   void on(int p) {(*_on)(p);}
  //   void off(int p) {(*_off)(p);}
  // };
  //
  // template<
  //   void (*_modeOff)(int),
  //   void (*_modeOut)(int),
  //   void (*_modeIn)(int),
  //   void (*_modeInUp)(int),
  //   void (*_modeInDown)(int),
  // > class IOPinBase {
  // };
  //
  // template<
  //   bool (*_get)(int)
  //   void (*_set)(int,bool),
  //   void (*_on)(int p),
  //   void (*_off)(int p)
  //   void (*_modeOff)(int),
  //   void (*_modeOut)(int),
  //   void (*_modeIn)(int),
  //   void (*_modeInUp)(int),
  //   void (*_modeInDown)(int),
  // > class IOPin:public
  //   InputPin<_get>,OutputPin<_set,_on,_off>
  // {
  // public:
  //   void modeOff(int p) {(*_modeOff)(p);}
  //   void modeOut(int p) {(*_modeOut)(p);}
  //   void modeIn(int p) {(*_modeIn)(p);}
  //   void modeInUp(int p) {(*_modeInUp)(p);}
  //   void modeInDown(int p) {(*_modeInDown)(p);}
  // };

  class ArduinoPin:public InputPin<
    (bool(*)(int))digitalRead
    // bool get(int p) {return digitalRead(p);},
    // void modeOff(int) {pinMode(p,INPUT);off(p);},
    // void modeOut(int p) {pinMode(p,OUTPUT);},
    // void modeIn(int) {pinMode(p,INPUT);},
    // void modeInUp(int) {pinMode(p,INPUT_PULLUP);},
    // void modeInDown(int) {pinMode(p,INPUT_PULLDOWN);},
    // void set(int p,bool o) {digitalWrite(p,o);},
    // void on(int p) {digitalWrite(p,true);},
    // void off(int p) {digitalWrite(p,false);}
  >{};

  // template<PinBase PIn>
  // class debounce {
  // protected:
  //   bool state;
  //   unsigned long=start;
  // public:
  //
  // };

  template<
      int nr,
      bool isOn,
      int pinNr
    >
  class Pin {
    virtual void pinMode() {}
    virtual bool read() {}
    virtual void write(bool) {}
  };

  // namespace RU {

    //use negative pin number for reverse logic pin and internal pull-up
    template<
      int nr,
      bool isOn,
      int pinNr,
      int longPress
    >
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

    template<int nr,int longPress=500>
    using OneKey=OneKeyBase<nr,nr<0,nr<0?-nr:nr,longPress>;
  // };//namespace RU

#endif
