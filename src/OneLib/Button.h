/* -*- C++ -*- */
// #ifndef ONE_BUTTON_DEF_H
//   #define ONE_BUTTON_DEF_H

  #include <OneLib.h>

  using namespace OneLib;

  // namespace OneLib {

    enum BtnState:unsigned char {Open = 0,Pressed,Held,Released,Clicked,DoubleClicked/*,Escape*/};

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
  // };//namespace OneLib
// #endif
