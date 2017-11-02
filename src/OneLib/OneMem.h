/* -*- C++ -*- */
template<class T,T o>
struct Static {
  static inline T value() {return o;};
  inline bool operator==(const auto v) {return o==v;}
  inline operator T() {return value();}
};

template<class T,T& o>
struct Ram {
  static inline  T value() {return o;}
  inline T operator=(const auto v) {return o=v;}
  inline bool operator==(const auto v) {return o==v;}
  inline operator T() const {return value();}
};

template<class T,const T* o>
struct Flash {
  static inline const T& value() {return *o;}
  inline bool operator==(const auto v) const {return *o==v;}
  inline operator T&() const {return value();}
};

template<class T,const T* o>
struct FlashString {
  static inline __FlashStringHelper* value() {return (__FlashStringHelper*)o;}
  inline bool operator==(const auto v) const {return *o==v;}
  // inline operator (__FlashStringHelper*)() const {return value();}
};
