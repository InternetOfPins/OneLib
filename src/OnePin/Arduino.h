/* -*- C++ -*- */
#ifndef RSITE_ARDUINOPINS_DEF
  #define RSITE_ARDUINOPINS_DEF

  #include <Arduino.h>
  typedef int8_t PinNr;
  #include "OnePin.h"

  inline bool arduino_get(PinNr p) {return digitalRead(p);}
  inline void arduino_modeOff(PinNr p) {pinMode(p,INPUT);digitalWrite(p,LOW);}
  inline void arduino_modeOut(PinNr p) {pinMode(p,OUTPUT);}
  inline void arduino_modeIn(PinNr p) {pinMode(p,INPUT);}
  inline void arduino_modeInUp(PinNr p) {pinMode(p,INPUT_PULLUP);}
  inline void arduino_modeInDown(PinNr p) {pinMode(p,INPUT);}//
  inline void arduino_mode(PinNr p, PinNr o) {pinMode(p,o);}
  inline void arduino_set(PinNr p,bool o) {digitalWrite(p,o);}
  inline void arduino_on(PinNr p) {digitalWrite(p,HIGH);}
  inline void arduino_off(PinNr p) {digitalWrite(p,LOW);}

  class ArduinoPin:
    public InputPin<&arduino_get>,
    public OutputPin<&arduino_set,&arduino_on,&arduino_off>,
    public IOPinNoDown<&arduino_modeOff,&arduino_modeOut,&arduino_modeIn,&arduino_modeInUp>
  {};

#endif
