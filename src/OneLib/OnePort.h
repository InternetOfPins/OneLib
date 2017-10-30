/* -*- C++ -*- */
#ifndef RSITE_ONEPORT_DEF
  #define RSITE_ONEPORT_DEF

  //r-Site pins API
  //Rui Azevedo - Oct.2017
  //ruihfazevedo@gmail.com
  //CC-BY-NC-SA

  template<
    PortData (*_get)(PortReg)
  > struct InputPort {
    public:
      static inline get(PortReg reg) {return (*_get)(reg);}
  };

  template<
    void (*_set)(PortReg,PortData)
  > class OutputPort {
    public:
      static inline void set(PortReg p,PortData o) {(*_set)(p,o);}
  };

  template<
    PortData (*_get)(PortReg),
    void (*_set)(PortReg,PortData),
    void (*_mode)(PortReg,PortData)
  > class IOPort:
    public InputPort<_get>,
    public OutputPort<_set>
  {
    public:
      static inline void mode(PortReg p,PortData o) {(*_mode)(p,o);}
  };

#endif
