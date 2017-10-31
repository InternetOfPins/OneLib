#include <OneLib/OnePort.h>

void setup() {
  DataIO<RefIO<Byte>> x;
  x=12;
  // RefIO<DataIO<Byte>> r(&x);
}
void loop() {}
