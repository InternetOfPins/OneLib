/* -*- C++ -*- */
/*
Pin manipulation meta-framework
OnePin meta-framework can overlay existing frameworks with zero cost

Along with the pin manipulation functions there are also a couple of composable
utilities like debouncing or action coupling

A top layer with virtual functions is provided for library abstration over Pins

A couple of small examples of libraries included

This is the base for IOP - The Internet Of Pins
on the sequence of VirtualPins proposals done to Arduino framework
*/
#ifndef ONELIB_DEF
  #define ONELIB_DEF

  #include <avr/io.h>
  #ifdef DEBUG
    #include <streamFlow.h>
  #endif

  #include "OneLib/Mem.h"
  #include "OneLib/Func.h"
  #include "OneLib/Pin.h"

  namespace OneLib {

  };
#endif
