/* -*- C++ -*- */
#ifndef ONELIB_ENCODER_DEF
  #define ONELIB_ENCODER_DEF

  #include "OneLib.h"

  namespace OneLib {
    template<int16_t accelUp=6> class Encoder;

    template<>class Encoder<0> {
      public:
        Encoder(OnePin& a,OnePin& b):a(a),b(b) {}
        void begin() {
          a.begin();
          b.begin();
        }
        static inline uint8_t accelRate() {return 0;}
        inline int getPosition() {return pos;}
        void updateA() {
          if (a.logicIn()^b.logicIn()) pos--;
          else pos++;
        }
        void updateB() {
          if (a.logicIn()^b.logicIn()) pos++;
          else pos--;
        }

        template<Encoder *enc>
        using UpdateA = MFunc<Encoder>::With<enc,&Encoder::updateA>;
        template<Encoder *enc,class O,uint8_t deb=1>
        using PinA=RecState<OnChange<O,UpdateA<enc>::caller>>;

        template<Encoder *enc>
        using UpdateB = MFunc<Encoder>::With<enc,&Encoder::updateB>;
        template<Encoder *enc,class O,uint8_t deb=1>
        using PinB=RecState<OnChange<O,UpdateB<enc>::caller>>;

      protected:
        OnePin& a;
        OnePin& b;
        volatile int pos=0;
    };

    template<int16_t accelUp>class Encoder:public Encoder<0> {
      public:
        Encoder(OnePin& a,OnePin& b):Encoder<0>(a,b),lastUpdate(millis()) {}
        static inline uint8_t accelRate() {return accelUp;}
        static const int16_t accelTop=512;
        // static const uint16_t accelUp=8;
        static const uint16_t accelDown=2;
        void updateA() {
          unsigned int m=millis();
          accel-=(m-lastUpdate)*accelDown;
          lastUpdate=m;
          if (accel<1) accel=1;
          else if (accel>accelTop) accel=1;
          if (a.logicIn()^b.logicIn()) pos-=accel;
          else pos+=accel;
          if (accel<accelTop) accel+=accelUp;
        }
        void updateB() {
          unsigned int m=millis();
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

    #define mkEncoder(EncoderType,enc,pina,pinb)\
      extern EncoderType enc;\
      typedef EncoderType::PinA<&enc,Debouncer<InputPin<pina>,1>> enc##_EncA;\
      typedef EncoderType::PinB<&enc,Debouncer<InputPin<pinb>,1>> enc##_EncB;\
      enc##_EncA enc##_a_;\
      enc##_EncB enc##_b_;\
      OnePin<enc##_EncA> enc##_a(enc##_a_);\
      OnePin<enc##_EncB> enc##_b(enc##_b_);\
      EncoderType enc(enc##_a,enc##_b);
  };//namespace OneLib
#endif
