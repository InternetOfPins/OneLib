/* -*- C++ -*- */
#ifndef KEYMATRIX_DEF_H
#define KEYMATRIX_DEF_H

#include <OneLib.h>

using namespace OneLib;

template<typename API,typename DataPins,typename ScanPins>
class KeyMatrixBase {
protected:
  const char keys[ScanPins::Field::size][DataPins::Field::size];
  // const char keys[][DataPins::Field::size];
public:
  template<typename ... T>
  KeyMatrixBase(const T ... o):keys{o...} {}
  // KeyMatrixBase(const char keys[ScanPins::Field::size][DataPins::Field::size])
  //   :keys(keys) {}
};

template<typename API,typename DataPins,typename ScanPins>
class KeyMatrix:public KeyMatrixBase<API,DataPins,ScanPins> {
public:
  static_assert(DataPins::Field::size>0,"Must have some data pins");
  using KeyMatrixBase<API,DataPins,ScanPins>::KeyMatrixBase;
  static inline void begin() {
    ScanPins::begin();
    DataPins::begin();
  }
};

template<typename API,typename DataPins>
class KeyMatrix<API,DataPins,VoidPin<typename API::Value>>:public KeyMatrixBase<API,DataPins,VoidPin<typename API::Value>>{
public:
  static_assert(DataPins::Field::size>0,"Must have some data pins");
  using KeyMatrixBase<API,DataPins,VoidPin<typename API::Value>>::KeyMatrixBase;
  static inline void begin() {
    DataPins::begin();
  }
};

#endif
