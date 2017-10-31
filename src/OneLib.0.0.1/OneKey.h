/* -*- C++ -*- */
#ifndef RSITE_ONEKEY_DEF
  #define RSITE_ONEKEY_DEF

  //key driver providing messages
  template<class O,int dblClk,int longPress>
  class OneKeyBase:public O {
    public:
      // int t() {return params<500>.lp();}
      enum State : unsigned char {
        Open = 0,
        Closed,
        Pressed,
        Held,
        Released,
        Clicked,
        DoubleClicked
      };
      inline void begin() {O::begin();}
      State read() {
        if (O::in()) {
          switch(state) {
            case DoubleClicked:
            case Pressed: return Held;
            case Open:
              state=millis()-lastChk<dblClk?DoubleClicked:Pressed;
          }
        } else state=Open;
        return state;
      }
    protected:
      unsigned long lastChk;
      State state=Open;
  };

  template<class O,int dblClick=100,int longPress=300>
  using OneKey=OneKeyBase<O,dblClick,longPress>;

#endif
