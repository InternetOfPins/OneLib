#include <OneArduino.h>
#include <OneLib/Button.h>

using namespace OneLib;
using namespace OneLib::Arduino;
#include <OneLib/LCD.h>

template<int pin>
using APin=
  OneLib::Hook<
    OneLib::Arduino::PinCap<
      OneLib::Arduino::OutputPin<pin>
    >
  >;

LCD<OneLib::Arduino::API> lcd(
  APin<8>::pin(),
  APin<9>::pin(),
  APin<10>::pin(),
  APin<0>::pin(),
  APin<1>::pin(),
  APin<2>::pin(),
  APin<3>::pin(),
  APin<4>::pin(),
  APin<5>::pin(),
  APin<6>::pin(),
  APin<7>::pin()
);

void setup() {}

void loop() {}
