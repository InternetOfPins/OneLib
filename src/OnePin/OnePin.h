/* -*- C++ -*- */
#ifndef RSITE_ONEPIN_DEF
  #define RSITE_ONEPIN_DEF

  //r-Site pins API
  //Rui Azevedo - Oct.2017
  //ruihfazevedo@gmail.com

  ///////////////////////////////////////////////////////////////
  // base pin functions adapter
  template<bool (*_get)(PinNr)> struct InputPin {
  public:
    inline bool get(PinNr p) {return (*_get)(p);}
  };

  template<
    void (*_set)(PinNr,bool),
    void (*_on)(PinNr p),
    void (*_off)(PinNr p)
  > class OutputPin {
  public:
    inline void set(PinNr p,bool o) {(*_set)(p,o);}
    inline void on(PinNr p) {(*_on)(p);}
    inline void off(PinNr p) {(*_off)(p);}
  };

  template<
    void (*_modeOff)(PinNr),
    void (*_modeOut)(PinNr),
    void (*_modeIn)(PinNr),
    void (*_modeInUp)(PinNr)
  > class IOPinNoDown {
  public:
    inline void modeOff(PinNr p) {(*_modeOff)(p);}
    inline void modeOut(PinNr p) {(*_modeOut)(p);}
    inline void modeIn(PinNr p) {(*_modeIn)(p);}
    inline void modeInUp(PinNr p) {(*_modeInUp)(p);}
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
      inline void modeInDown(PinNr p) {(*_modeInDown)(p);}
  };

  ///////////////////////////////////////////////////////////////////////
  // Pin overlays

  //debouncer pin overlay
  //prevents pin state change for delta ms
  template<class O,int delta>
  class Debouncer:public O {
    public:
      using O::O;
      inline bool get(PinNr pin) {
        return millis()-lastRead<delta?lastState:(lastRead=millis(),lastState=O::get(pin));
      }
    protected:
      unsigned long lastRead;
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

  ////////////////////////////////////////////////////////////////////
  // Pin API with specific pin number

  template<class O,PinNr nr>
  using Base=LogicPinBase< O, nr<0 >;

  template<class O,PinNr nr,const PinNr pin>
  class PinBase:protected Base<O,nr> {
  public:
    inline bool get() {return Base<O,nr>::get(pin);}
    inline void set(bool o) {Base<O,nr>::set(pin,o);}
    inline void on() {Base<O,nr>::on(pin);}
    inline void off() {Base<O,nr>::off(pin);}
    inline void mode(uint8_t m) {Base<O,nr>::mode(pin,m);}
    inline void modeOff() {Base<O,nr>::modeOff(pin);}
    inline void modeOut() {Base<O,nr>::modeOut(pin);}
    inline void modeIn() {Base<O,nr>::modeIn(pin);}
    inline void modeInUp() {Base<O,nr>::modeInUp(pin);}
  };

  template<class O,PinNr nr>
  using OnePin=PinBase<O,nr,nr<0?-nr:nr>;

#endif
