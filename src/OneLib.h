/* -*- C++ -*- */
#include <avr/io.h>

#ifdef DEBUG
  #include <streamFlow.h>
#endif

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


//-------------------------------------------------------
struct Avr {

  // hardwired code
  template<uint8_t reg>
  struct Reg:protected Mem<uint8_t> {
    static inline uint8_t get() {return Mem::get(reg);}
    static inline uint8_t set(uint8_t v) {return Mem::set(reg,v);}
    template<uint8_t bit> static inline void on() {(*(uint8_t*)reg)|=1<<bit;}
    template<uint8_t bit> static inline void off() {(*(uint8_t*)reg)&=~(1<<bit);}
    template<uint8_t bit> static inline bool in() {return (*(uint8_t*)reg)&(1<<bit);}
  };

  template<uint8_t base> using In = Avr::Reg<base>;
  template<uint8_t base> using Mode = Avr::Reg<base+1>;
  template<uint8_t base> using Out = Avr::Reg<base+2>;

  template<uint8_t base>
  struct Port:
    protected In<base>,
    protected Mode<base>,
    protected Out<base>
  {
    static inline uint8_t mode() {return Mode<base>::get();}
    static inline void mode(uint8_t m) {Mode<base>::set(m);}
    static inline uint8_t in() {return In<base>::get();}
    static inline void out(uint8_t data) {Out<base>::set(data);}

    template<uint8_t bit>
    static inline void modeOut() {Mode<base>::template on<bit>();}
    template<uint8_t bit>
    static inline void modeIn() {
      Mode<base>::template off<bit>();
      Out<base>::template off<bit>();
    }
    template<uint8_t bit>
    static inline void modeInUp() {
      Mode<base>::template off<bit>();
      Out<base>::template on<bit>();
    }
    template<uint8_t bit>
    static inline void modeOff() {
      Mode<base>::template off<bit>();
      Out<base>::template off<bit>();
    }
    template<uint8_t bit>
    static inline void on() {Out<base>::template on<bit>();}
    template<uint8_t bit>
    static inline void off() {Out<base>::template off<bit>();}

    template<uint8_t bit>
    static inline bool in() {return In<base>::template in<bit>();}

  };
  template<class Port,int pin>
  struct PinBase:protected Port {
    static inline void modeOut() {Port::template modeOut<pin>();}
    static inline void modeIn() {Port::template modeIn<pin>();}
    static inline void modeInUp() {Port::template modeInUp<pin>();}
    static inline void on() {Port::template on<pin>();}
    static inline void off() {Port::template off<pin>();}
    static inline bool in() {return Port::template in<pin>();}
  };
  template<class Port,int pin>
  using Pin=LogicPinBase<PinBase<Port,pin<0?-pin:pin>,pin<0>;
};
