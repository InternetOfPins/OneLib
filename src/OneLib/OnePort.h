/* -*- C++ -*- */

template<class T>
struct Data {
  T value;
  inline Data(){}
  inline Data(T o):value(o) {}
};

typedef Data<uint8_t> Byte;
typedef Data<uint16_t> Word;

template<class T>
using Ptr=Data<T*>;

///////////////////
template<class O,class T>
struct DataInBase:public O {
  using O::O;
  inline T get() const {return O::value;}
  inline bool operator==(T o) {return O::value==o;}
};
template<class O> using DataIn=DataInBase<O,typeof(O::value)>;

template<class O,class T>
struct DataOutBase:public O {
  using O::O;
  inline void set(T o) {O::value=o;}
  inline T operator=(T o) {return O::value=o;}
};
template<class O> using DataOut=DataOutBase<O,typeof(O::value)>;

//the diamond problem with data
template<class O,class T>
struct DataIOBase:public DataIn<O>,public DataOut<O> {
  using O::O;
  inline T operator=(T o) {return DataOut<O>::operator=(o);}
};
template<class O> using DataIO=DataIOBase<O,typeof(O::value)>;

///////////////////
template<class O,class T>
struct RefInBase:public O {
  using O::O;
  inline T get() const {return *O::value;}
  inline bool operator==(T o) {return get()==o;}
};
template<class O> using RefIn=RefInBase<O,typeof(O::value)>;

template<class O,class T>
struct RefOutBase:public O {
  using O::O;
  inline void set(T o) {*O::value=o;}
  inline T operator=(T o) {return *O::value=o;}
};
template<class O> using RefOut=RefOutBase<O,typeof(O::value)>;

template<class O,class T>
struct RefIOBase:public RefIn<O>,public RefOut<O> {
  using O::O;
  inline T operator=(T o) {return DataOut<O>::operator=(o);}
};
template<class O> using RefIO=RefIOBase<O,typeof(O::value)>;
