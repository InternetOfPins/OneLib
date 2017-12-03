/* -*- C++ -*- */
// #ifndef ONELIB_ACCEL_ENCODER_DEF
//   #define ONELIB_ACCEL_ENCODER_DEF

  // #include "Encoder.h"
  #include "OneLib.h"

  // namespace OneLib {
    template<int16_t accelUp>
    class Encoder:public Encoder<0> {
      public:
        Encoder(OnePin& a,OnePin& b):Encoder<0>(a,b),lastUpdate(getMillis()) {}
        static inline uint8_t accelRate() {return accelUp;}
        static const int16_t accelTop=512;
        // static const uint16_t accelUp=8;
        static const uint16_t accelDown=2;
        void updateA() {
          unsigned int m=getMillis();
          accel-=(m-lastUpdate)*accelDown;
          lastUpdate=m;
          if (accel<1) accel=1;
          else if (accel>accelTop) accel=1;
          if (a.logicIn()^b.logicIn()) pos-=accel;
          else pos+=accel;
          if (accel<accelTop) accel+=accelUp;
        }
        void updateB() {
          unsigned int m=getMillis();
          accel-=m-lastUpdate;
          lastUpdate=m;
          if (accel<1) accel=1;
          else if (accel>accelTop) accel=1;
          if (a.logicIn()^b.logicIn()) pos+=accel;
          else pos-=accel;
          if (accel<accelTop) accel+=accelUp;
        }

        template<Encoder<accelUp> *enc>
        using UpdateA = typename MFunc<Encoder<accelUp>>::template With<enc,&Encoder<accelUp>::updateA>;

        template<Encoder<accelUp> *enc>
        using UpdateB = typename MFunc<Encoder<accelUp>>::template With<enc,&Encoder<accelUp>::updateB>;

        template<Encoder<accelUp> *enc,class O,uint8_t deb=1>
        using PinA=RecState<OnChange<O,UpdateA<enc>::caller>>;

        template<Encoder<accelUp> *enc,class O,uint8_t deb=1>
        using PinB=RecState<OnChange<O,UpdateB<enc>::caller>>;

        inline int16_t getAccel() const {return accel;}
      protected:
        int16_t accel=0;
        unsigned long lastUpdate;
    };
  // };//namespace OneLib

// #endif
