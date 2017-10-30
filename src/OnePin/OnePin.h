/* -*- C++ -*- */
#ifndef RSITE_ONEPIN_DEF
  #define RSITE_ONEPIN_DEF

  //r-Site pins API
  //Rui Azevedo - Oct.2017
  //ruihfazevedo@gmail.com
  //CC-BY-NC-SA

  #ifdef DEBUG
  #include <streamFlow.h>
  #endif

  ///////////////////////////////////////////////////////////////
  // base pin functions adapter
  template<bool (*_get)(PinNr)> struct InputPin {
  public:
    static inline bool get(PinNr p) {return (*_get)(p);}
  };

  template<
    void (*_set)(PinNr,bool),
    void (*_on)(PinNr p),
    void (*_off)(PinNr p)
  > class OutputPin {
  public:
    static inline void set(PinNr p,bool o) {(*_set)(p,o);}
    static inline void on(PinNr p) {(*_on)(p);}
    static inline void off(PinNr p) {(*_off)(p);}
  };

  template<
    void (*_modeOff)(PinNr),
    void (*_modeOut)(PinNr),
    void (*_modeIn)(PinNr),
    void (*_modeInUp)(PinNr)
  > class IOPinNoDown {
  public:
    static inline void modeOff(PinNr p) {(*_modeOff)(p);}
    static inline void modeOut(PinNr p) {(*_modeOut)(p);}
    static inline void modeIn(PinNr p) {(*_modeIn)(p);}
    static inline void modeInUp(PinNr p) {(*_modeInUp)(p);}
  };

  template<
    bool (*_get)(PinNr),
    void (*_set)(PinNr,bool),
    void (*_on)(PinNr p),
    void (*_off)(PinNr p),
    void (*_modeOff)(PinNr),
    void (*_modeOut)(PinNr),
    void (*_modeIn)(PinNr),
    void (*_modeInUp)(PinNr),
    void (*_modeInDown)(PinNr)
  > class IOPin:
    public InputPin<_get>,
    public OutputPin<_set,_on,_off>,
    public IOPinNoDown<_modeOff,_modeOut,_modeIn,_modeInUp>
  {
    public:
      static inline void modeInDown(PinNr p) {(*_modeInDown)(p);}
  };

  ///////////////////////////////////////////////////////////////////////
  // Pin overlays

  //debouncer pin overlay
  //prevents pin state change for delta ms
  template<class O,int delta>
  class Debouncer:public O {
    public:
      // using O::O;
      inline bool get(PinNr pin) {
        if (millis()-lastChange<delta) return lastState;
        bool s=O::get(pin);
        return s==lastState?lastState:(lastChange=millis(),lastState=s);
      }
    protected:
      unsigned long lastChange=-delta;
      bool lastState;
  };

  //logic pin overlay
  //pin with reversible logic
  template<class O,bool isOn>
  class LogicPinBase:public O {
    public:
      inline bool get(PinNr pin) {return O::get(pin)^isOn;}
      inline void set(PinNr pin,bool o) {O::set(pin,o^isOn);}
      inline void on(PinNr pin) {O::set(pin,true);}
      inline void off(PinNr pin) {O::set(pin,false);}
  };

  template<class O,PinNr nr>
  using LogicPin=LogicPinBase< O, nr<0 >;

  ////////////////////////////////////////////////////////////////////
  // Pin API with specific pin number

  template<class O,PinNr pin>
  class PinIO:protected O {
    private: OnePinIO(){}
    public:
      // inline void TaskPin() {}//restriction
      inline bool in() {return O::get(pin);}
  };
  template<class O,PinNr pin>
  class PinOutput:public PinIO<O,pin> {
    public:
      inline void begin() {O::modeOut(pin);}
      inline void begin(bool o) {O::modeOut(pin);O::set(pin,o);}
      inline void set(bool o) {O::set(pin,o);}
      inline void on() {O::on(pin);}
      inline void off() {O::off(pin);}
  };
  template<class O,PinNr pin>
  class PinInput:public PinIO<O,pin> {
    public:
      inline void begin() {O::modeIn(pin);}
  };
  template<class O,PinNr pin>
  class PinInputUp:public PinIO<LogicPin<O,-pin>,pin> {
    public:
      inline void begin() {O::modeInUp(pin);}
  };

  template<template<class,PinNr> class IO,class O,PinNr nr>
  using OnePinBase=IO<O,nr<0?-nr:nr>;

  template<template<class,PinNr> class IO,class O,PinNr nr>
  class OnePin:public OnePinBase<IO,O,nr> {
    // inline OnePin() {IO::TaskPin();}
  public:
  };

#endif
