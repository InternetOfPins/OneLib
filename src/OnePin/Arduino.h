/* -*- C++ -*- */
#ifndef RSITE_ARDUINOPINS_DEF
  #define RSITE_ARDUINOPINS_DEF

  #include <Arduino.h>
  #include "OnePin.h"

  inline bool arduino_get(int p) {return digitalRead(p);}
  inline void arduino_modeOff(int p) {pinMode(p,INPUT);digitalWrite(p,LOW);}
  inline void arduino_modeOut(int p) {pinMode(p,OUTPUT);}
  inline void arduino_modeIn(int p) {pinMode(p,INPUT);}
  inline void arduino_modeInUp(int p) {pinMode(p,INPUT_PULLUP);}
  inline void arduino_modeInDown(int p) {pinMode(p,INPUT);}//
  inline void arduino_mode(int p, int o) {pinMode(p,o);}
  inline void arduino_set(int p,bool o) {digitalWrite(p,o);}
  inline void arduino_on(int p) {digitalWrite(p,HIGH);}
  inline void arduino_off(int p) {digitalWrite(p,LOW);}

  class ArduinoPin:
    public InputPin<&arduino_get>,
    public OutputPin<&arduino_set,&arduino_on,&arduino_off>,
    public IOPinNoDown<&arduino_modeOff,&arduino_modeOut,&arduino_modeIn,&arduino_modeInUp>
  {};

#endif
