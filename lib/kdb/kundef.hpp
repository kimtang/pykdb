

# ifdef KX

# undef kx_kG
# undef kx_kC
# undef kx_kH
# undef kx_kI
# undef kx_kJ
# undef kx_kE
# undef kx_kF
# undef kx_kS
# undef kx_kK

//      type bytes qtype     ctype  accessor
# undef kx_KB // 1 boolean   char   kG
# undef kx_UU // 16 guid     U      kU
# undef kx_KG // 1 byte      char   kG
# undef kx_KH // 2 short     short  kH
# undef kx_KI // 4 int       int    kI
# undef kx_KJ // 8 long      long   kJ
# undef kx_KE // 4 real      float  kE
# undef kx_KF // 8 float     double kF
# undef kx_KC // 1 char      char   kC
# undef kx_KS // * symbol    char*  kS

# undef kx_KP // 8 timestamp long   kJ (nanoseconds from 2000.01.01)
# undef kx_KM // 4 month     int    kI (months from 2000.01.01)
# undef kx_KD // 4 date      int    kI (days from 2000.01.01)

# undef kx_KN // 8 timespan  long   kJ (nanoseconds)
# undef kx_KU // 4 minute    int    kI
# undef kx_KV // 4 second    int    kI
# undef kx_KT // 4 time      int    kI (millisecond)

# undef kx_KZ // 8 datetime  double kF (DO NOT USE)

// table,dict
#undef kx_XT //   x->k is XD
#undef kx_XD //   kK(x)[0] is keys. kK(x)[1] is values.


// nulls(n?) and infinities(w?)
# undef kx_nh
# undef kx_wh
# undef kx_ni
# undef kx_wi
# ifdef WIN32
  # undef kx_nj
  # undef kx_wj
  # undef kx_nf
  # undef kx_wf
  # undef kx_isnan
  # undef kx_finite
# else
  # undef kx_nj
  # undef kx_wj
  # undef kx_nf
  # undef kx_wf
  # undef kx_closesocket
# endif

// remove more clutter
# undef kx_O
# undef kx_R
# undef kx_Z
# undef kx_P
# undef kx_U
# undef kx_SW
# undef kx_CS
# undef kx_CD

# undef kx_ZV
# undef kx_ZK
# undef kx_ZH
# undef kx_ZI
# undef kx_ZJ
# undef kx_ZE
# undef kx_ZF
# undef kx_ZC
# undef kx_ZS

# undef kx_K1
# undef kx_K2
# undef kx_TX
# undef kx_xr
# undef kx_xt
# undef kx_xu
# undef kx_xn
# undef kx_xx
# undef kx_xy
# undef kx_xg
# undef kx_xh
# undef kx_xi
# undef kx_xj
# undef kx_xe
# undef kx_xf
# undef kx_xs
# undef kx_xk
# undef kx_xG
# undef kx_xH
# undef kx_xI
# undef kx_xJ
# undef kx_xE
# undef kx_xF
# undef kx_xS
# undef kx_xK
# undef kx_xC
# undef kx_xB

# endif
