/* -*- C++ -*- */
#ifndef ONELIB_AVR_DEF
  #define ONELIB_AVR_DEF

#include "OneLib.h"

  namespace OneLib {
    namespace Avr {

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
        template<bool T>
        static inline void set() {T?on():off();}
        static inline void set(bool v) {v?on():off();}
        static inline bool in() {return Port::template in<pin>();}
        static inline bool rawIn() {return in();}
      };
      template<class Port,int pin>
      using Pin=LogicPinBase<PinBase<Port,pin<0?-pin:pin>,pin<0>;

      namespace AtMega328p {
        typedef Avr::Port<0x23> PortB;
        typedef Avr::Port<0x26> PortC;
        typedef Avr::Port<0x29> PortD;
        namespace ArduinoPins {
          constexpr uint8_t pinToPort[]={
            0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,
            0x23,0x23,0x23,0x23,0x23,0x23,
            0x26,0x26,0x26,0x26,0x26,0x26
          };
          constexpr uint8_t pinToBit[]={
            0,1,2,3,4,5,6,7,
            0,1,2,3,4,5,
            0,1,2,3,4,5
          };
          template<int8_t pin>
          using Pin = Avr::Pin<Avr::Port<pinToPort[pin<0?-pin:pin]>,pin<0?-pinToBit[pin<0?-pin:pin]:pinToBit[pin<0?-pin:pin]>;
        }
      };

    };

  }//namespace OneLib
#endif
