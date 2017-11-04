/* -*- C++ -*- */

template<typename T> struct Maybe {};
template<typename T> class Nothing:public Maybe<T> {};
template<typename T> class Just:public Maybe<T> {
  public:
    inline Just(T o):value(o) {}
    inline T fromJust() const {return value;}
  protected:
    T value;
};

template<typename T> bool isJust(Just<T>) {return true;}
template<typename T> bool isJust(Nothing<T>) {return false;}
template<typename T> T fromJust(Just<T> o) {o.fromJust();}

template<typename res,typename ... types>
class Function {
  public:
    Function(res (*fn)(types...)):fn(fn) {}
    template<types...>
    res operator()(types... args) {return (*fn)(args...);}
  protected:
    res (*fn)(types...);
};

template<class O>
struct Flux {
  static inline void read(void (*cb)(O)) {}
};

template<class O>
class Array {
  public:
    Array(O* addr,unsigned long len):addr(addr),len(len) {}
    inline void next() {++addr;--len;}
    inline operator O() {return *addr;}
    inline unsigned long sz() {return len;}
    template<class S,class T>
    inline Array<T> map(auto f,Array<S> list) {}
  protected:
    O* addr;
    unsigned long len;
};
