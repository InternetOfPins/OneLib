/* -*- C++ -*- */

#include <OneLib.h>

using namespace OneLib;

// #ifndef ONE_CLICK_BUTTON_DEF_H
//   #define ONE_CLICK_BUTTON_DEF_H

  // namespace OneLib {

    template<unsigned long dblTime=600, unsigned long hldTime=2*dblTime>
    class ClickButton:public OneButton {
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
        long delta=getMillis()-lastCheck;
        BtnState one=OneButton::get();
        if (clicks&&one==Open&&delta>=(dblTime>>1)) {
          btnState=Clicked;
          clicks=0;//new frame
          lastCheck=getMillis();
        } else {
          switch(one) {
            case Pressed:
              if (clicks) {
                btnState=DoubleClicked;
                clicks=0;//new frame
                lastCheck=getMillis();
              } else {
                clicks++;
                lastCheck=getMillis();
                btnState=Pressed;
              }
              break;
            case Held:
              if (clicks&&delta>=hldTime) btnState=Held;
              break;
            case Released:
              if (btnState==Held) {
                clicks=0;//new frame
                lastCheck=getMillis();
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
  // };//namespace OneLib
// #endif
