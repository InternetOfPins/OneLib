/* -*- C++ -*- */
#ifndef RSITE_AVRPINS_DEF
  #define RSITE_AVRPINS_DEF

  template<int port,uint8_t pinMask>
  class PinId {
    inline int addr() {return port;}
    inline uint8_t mask() {return pinMask;}
  };

  typedef uint8_t PortData;
  typedef PortData* PortReg;
  #include "OnePin.h"
  #include "OnePort.h"

  inline PortData avrPort_get(PortReg reg) {return *(reg);}
  inline void avrPort_set(PortReg reg,PortData o) {*(reg)=o;}
  inline void avrPort_mode(PortReg reg,PortData o) {*(reg)=o;}

  class AvrPort:public IOPort<&avrPort_get,&avrPort_set,&avrPort_mode> {};

  inline bool avr_get(PinNr p) {return digitalRead(p);}
  inline void avr_modeOff(PinNr p) {pinMode(p,INPUT);digitalWrite(p,LOW);}
  inline void avr_modeOut(PinNr p) {pinMode(p,OUTPUT);}
  inline void avr_modeIn(PinNr p) {pinMode(p,INPUT);}
  inline void avr_modeInUp(PinNr p) {pinMode(p,INPUT_PULLUP);}
  inline void avr_modeInDown(PinNr p) {pinMode(p,INPUT);}//
  inline void avr_mode(PinNr p, PinNr o) {pinMode(p,o);}
  inline void avr_set(PinNr p,bool o) {digitalWrite(p,o);}
  inline void avr_on(PinNr p) {digitalWrite(p,HIGH);}
  inline void avr_off(PinNr p) {digitalWrite(p,LOW);}

  class AvrPin:
    public InputPin<PinId,&avr_get>,
    public OutputPin<PinId,&avr_set,&avr_on,&avr_off>,
    public IOPinNoDown<PinId,&avr_modeOff,&avr_modeOut,&avr_modeIn,&avr_modeInUp>
  {};

#endif
