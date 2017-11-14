/* -*- C++ -*- */
#ifndef ONEBUTTON_DEF
  #define ONEBUTTON_DEF

  #ifdef DEBUG
    #include <streamFlow.h>
  #endif
  #include "OneLib.h"

  enum BtnState:uint8_t {Open = 0,Pressed,Held,Released,Clicked,DoubleClicked,Escape};

  namespace OneLib {
    //return states: Pressed | Held | Released | Open
    class OneButton {
    public:
      OneButton(OnePin& pin):pin(pin) {}
      BtnState get() {
        BtnState s=getState();
        if(s!=state)
          switch (state) {
            case Open: state=Pressed;break;
            case Held: state=Released;break;
            default: state=s;break;
          }
        return state;
      }
    // protected:
      OnePin& pin;
      BtnState getState() {return pin.in()?Held:Open; }
      BtnState state=Open;
    };

    template<unsigned long dblTime=600, unsigned long hldTime=2*dblTime>
    class ClickButton:public OneButton {//from https://github.com/0xPIT/encoder with some tweaks
    public:
      ClickButton(OnePin& pin):OneButton(pin) {}
      static inline bool mustConsume(BtnState btnState)//list states that MUST be consumed
      {return btnState==DoubleClicked||btnState==Clicked||btnState==Released;}
      BtnState get() {
        update();
        BtnState ret = btnState;
        if (mustConsume(btnState)) btnState = Open;
        return ret;
      }
      void update() {
        if (mustConsume(btnState)) return;//this states must be consumed!
        long delta=millis()-lastCheck;
        BtnState one=OneButton::get();
        if (clicks&&one==Open&&delta>=(dblTime>>1)) {
          btnState=Clicked;
          clicks=0;//new frame
          lastCheck=millis();
        } else {
          switch(one) {
            case Pressed:
              if (clicks) {
                btnState=DoubleClicked;
                clicks=0;//new frame
                lastCheck=millis();
              } else {
                clicks++;
                lastCheck=millis();
                btnState=Pressed;
              }
              break;
            case Held:
              if (clicks&&delta>=hldTime) btnState=Held;
              break;
            case Released:
              if (btnState==Held) {
                clicks=0;//new frame
                lastCheck=millis();
                btnState=Released;
              } else btnState=Open;
              break;
            case Open:
            default:
              btnState=one;
          }
        }
      }
    // protected:
      uint16_t clicks = 0;
      unsigned long lastCheck = 0;
      BtnState btnState=Open;
    };

    // **use case**
    // typedef RecState<Debouncer<InputPin<-4>,50>> Key4Pin;
    // Key4Pin key4Pin;
    // OnePinHook<Key4Pin> key4(key4Pin);
    // ClickButton<600> btn4(key4);
  }
#endif
