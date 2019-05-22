
# ifndef KX_HPP_KKT_24_03_2016
# define KX_HPP_KKT_24_03_2016

# include <kdb/k.h>
# include <utility>

namespace kx{

  F zu(F u){return u/86400000000.0 - 10957.0;}   // kdb+ datetime from unix
  J uz(F f){return 86400000000*(f+10957);}  // unix from kdb+ datetime
  J pu(J u){return u - 946684800000000000;} // kdb+ timestamp from unix, use ktj(Kj,n) to create timestamp from n
  J up(J f){return f + 946684800000000000;}  // unix from kdb+ timestamp
  I um(I u){return u + 360; }
  I mu(I u){return u - 360; }

  I ud(I u){return u + 10957; }
  I du(I u){return u - 10957; }


  typedef std::pair<G*,G*> GP;
  typedef std::pair<C*,C*> CP;
  typedef std::pair<H*,H*> HP;
  typedef std::pair<I*,I*> IP;
  typedef std::pair<J*,J*> JP;
  typedef std::pair<E*,E*> EP;
  typedef std::pair<F*,F*> FP;
  typedef std::pair<S*,S*> SP;
  typedef std::pair<K*,K*> KP;

  struct dx {};
  struct dy {};
  struct tx {};
  struct ty {};
  struct cs {};

  struct conv{
	explicit conv(K x):x_(x){};
	K x_;
    operator G (){return x_->g;}
    operator H (){return x_->h;}
    operator I (){return x_->i;}
    operator J (){return x_->j;}
    operator E (){return x_->e;}
    operator F (){return x_->f;}

	// explicit overload for S
	S operator()(cs){return x_->s;}

    operator G* (){return x_->G0;}
    operator C* (){return (C*)(x_->G0);}
    operator H* (){return (H*)(x_->G0);}
    operator I* (){return (I*)(x_->G0);}
    operator J* (){return (J*)(x_->G0);}
    operator E* (){return (E*)(x_->G0);}
    operator F* (){return (F*)(x_->G0);}
    operator S* (){return (S*)(x_->G0);}
    operator K* (){return (K*)(x_->G0);}

    operator GP (){G* xx = x_->G0;return GP(xx,xx+x_->n); }
    operator CP (){C* xx = (C*)(x_->G0);return CP(xx,xx+x_->n); }
    operator HP (){H* xx = (H*)(x_->G0);return HP(xx,xx+x_->n); }
    operator IP (){I* xx = (I*)(x_->G0);return IP(xx,xx+x_->n); }
    operator JP (){J* xx = (J*)(x_->G0);return JP(xx,xx+x_->n); }
    operator EP (){E* xx = (E*)(x_->G0);return EP(xx,xx+x_->n); }
    operator FP (){F* xx = (F*)(x_->G0);return FP(xx,xx+x_->n); }
    operator SP (){S* xx = (S*)(x_->G0);return SP(xx,xx+x_->n); }
    operator KP (){K* xx = (K*)(x_->G0);return KP(xx,xx+x_->n); }

    K operator ()(dx){return (K)((K*)x_->G0)[0];}
    K operator ()(dy){return (K)((K*)x_->G0)[1];}
    K operator ()(tx){return (K)((K*)x_->k->G0)[0];}
    K operator ()(ty){return (K)((K*)x_->k->G0)[1];}
  };

}


# endif
