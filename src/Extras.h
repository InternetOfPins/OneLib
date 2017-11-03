/* -*- C++ -*- */

template<class T>
class Maybe {
  enum {Just<T>,Nothing<T>};
};

template<typename T> bool isJust(Just<T>){return true;}
template<typename T> bool isJust(Nothing<T>){return false;}
template<typename T> T fromJust(Just<T> jt) {return jt.fromJust();}

template<class T,class ...Args>
struct Lazyness {
  template<T (*f)(Args...),Args ... values>
  struct Lazy {
    inline T operator()() {return isJust(result)?fromJust(result):fromJust(result=Just<T>((*f)(values...)));}
    protected:
      Maybe<T> result=Nothing<T>();
  };
};

template<class O>
struct Flux {
  static inline void read(void (*cb)(O)) {}
};

template<class O>
class List {
  public:
    List(O* addr,unsigned long len):addr(addr),len(len) {}
    inline void next() {++addr;--len;}
    inline operator O() {return *addr;}
    inline unsigned long sz() {return len;}
    template<class S,class T>
    inline List<T> map(auto f,List<S> list) {}
  protected:
    O* addr;
    unsigned long len;
};
