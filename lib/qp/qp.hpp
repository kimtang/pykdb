


# ifndef QP_HPP_KKT_09_03_2016
# define QP_HPP_KKT_09_03_2016

# include <kdb/k.h>
# include <utility>
# include <string>
# include <boost/python.hpp>


namespace python = boost::python;
// using namespace boost::python;

namespace qp{

  template<class T>
  void assign(kx::k0& k,python::object o) {
      // Turn a Python sequence into an STL input range
      python::stl_input_iterator<T> begin(o), end;
      T* l = (T*)(k.G0);
      for(;begin!=end;++begin,++l)(*l)=*begin;
  }

  template<class Value>
  struct list
  {
      list(kx::K k) : k_(k){}
      kx::K k_;
      Value* begin() {return (Value*)(k_->G0); }
      Value* end() {return (Value*)(k_->G0) + k_->n; }
  };


  typedef list<kx::G> lG;
  typedef list<kx::C> lC;
  typedef list<kx::H> lH;
  typedef list<kx::I> lI;
  typedef list<kx::J> lJ;
  typedef list<kx::E> lE;
  typedef list<kx::F> lF;
  typedef list<kx::S> lS;
  typedef list<kx::K> lK;

  // serve as a vehicel for python
  kx::J n(kx::K k){return k->n;}
  // kx::C G0(kx::K k){return k->G0;}
  kx::K k0(kx::K k){return k->k;}
  kx::K k2(kx::I i,kx::SS s){return kx::k(i,s,(kx::K)0);}
  kx::K k3(kx::I i,kx::SS s,kx::K k0){return kx::k(i,s,k0,(kx::K)0);}
  kx::K k4(kx::I i,kx::SS s,kx::K k0,kx::K k1){return kx::k(i,s,k0,k1,(kx::K)0);}
  kx::V r0(kx::K k0){return kx::r0(k0);}
  // kx::J G0(kx::k0& k){return k.G0[0];}

  kx::K knk1(kx::I i,kx::K k0){return kx::knk(i,k0);}
  kx::K knk2(kx::I i,kx::K k0,kx::K k1){return kx::knk(i,k0,k1);}
  kx::K knk3(kx::I i,kx::K k0,kx::K k1,kx::K k2){return kx::knk(i,k0,k1,k2);}
  kx::K knk4(kx::I i,kx::K k0,kx::K k1,kx::K k2,kx::K k3){return kx::knk(i,k0,k1,k2,k3);}

  std::string sn(kx::SS s,kx::I i){return std::string(kx::sn(s,i));}
  std::string ss(kx::SS s){return std::string(kx::ss(s)); }

//       sd1(I,K(*)(I)),
//       dl(V*f,I),
//       ja(K*,V*),
//       js(K*,SS),
//       jk(K*,K),
//       dot(K,K),

}


# endif
