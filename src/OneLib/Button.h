/* -*- C++ -*- */
// #ifndef ONE_BUTTON_DEF_H
//   #define ONE_BUTTON_DEF_H

  #include <OneLib.h>

  using namespace OneLib;

  // namespace OneLib {

    enum BtnState:unsigned char {Open = 0,Pressed,Held,Released,Clicked,DoubleClicked/*,Escape*/};

    class OneButton {
    public:
      using Pin=OnePin<uint8_t,1>;
      //library "request" `Value type` and `field size` (defaults to 1?)
      //still library can receive an API or Info object for adequate Value type
      //however the direction of template parameter MUST be this one (from library to metaframework)
      //for the sake of not having to make template libraries (hew)
      OneButton(Pin& pin):pin(pin) {}
      inline void begin() {pin.begin();};
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
    protected:
      Pin& pin;
      BtnState getState() {return pin.in()?Held:Open; }
      BtnState state=Open;
    };
  // };//namespace OneLib
// #endif
