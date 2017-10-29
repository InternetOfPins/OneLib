/* -*- C++ -*- */
#ifndef RSITE_ONEPIN_DEF
  #define RSITE_ONEPIN_DEF

  //r-Site pins API
  //Rui Azevedo - Oct.2017
  //ruihfazevedo@gmail.com
  template<bool (*_get)(int)> struct InputPin {
  public:
    inline bool get(int p) {return (*_get)(p);}
  };

  template<
    void (*_set)(int,bool),
    void (*_on)(int p),
    void (*_off)(int p)
  > class OutputPin {
  public:
    inline void set(int p,bool o) {(*_set)(p,o);}
    inline void on(int p) {(*_on)(p);}
    inline void off(int p) {(*_off)(p);}
  };

  template<
    void (*_modeOff)(int),
    void (*_modeOut)(int),
    void (*_modeIn)(int),
    void (*_modeInUp)(int)
  > class IOPinNoDown {
  public:
    inline void modeOff(int p) {(*_modeOff)(p);}
    inline void modeOut(int p) {(*_modeOut)(p);}
    inline void modeIn(int p) {(*_modeIn)(p);}
    inline void modeInUp(int p) {(*_modeInUp)(p);}
  };

  template<
    bool (*_get)(int),
    void (*_set)(int,bool),
    void (*_on)(int p),
    void (*_off)(int p),
    void (*_modeOff)(int),
    void (*_modeOut)(int),
    void (*_modeIn)(int),
    void (*_modeInUp)(int),
    void (*_modeInDown)(int)
  > class IOPin:
    public InputPin<_get>,
    public OutputPin<_set,_on,_off>,
    public IOPinNoDown<_modeOff,_modeOut,_modeIn,_modeInUp>
  {
    public:
      inline void modeInDown(int p) {(*_modeInDown)(p);}
  };
#endif
