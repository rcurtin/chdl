#ifndef __DIVIDER_H
#define __DIVIDER_H

#include "bvec.h"
#include "bvec-basic.h"
#include "bvec-basic-op.h"
#include "shifter.h"
#include "adder.h"

#define LOG2(x) ((unsigned)(!!(0xffff0000&(x))<<4) | (!!(0xff00ff00&(x))<<3) \
                         | (!!(0xf0f0f0f0&(x))<<2) | (!!(0xcccccccc&(x))<<1) \
                         |  !!(0xaaaaaaaa&(x)) )

namespace chdl {
  template <unsigned N>
    bvec<N> divider(bvec<N> a, bvec<N> b, bvec<N> mod = Lit<N>(0))
  {
    bvec<N> q;
    vec<N + 1, bvec<N>> rem;
    rem[0] = a;
    for (unsigned i = 0; i < N; ++i) {
      unsigned bpos(N - i - 1);
      bvec<2*N> big_b(Cat(Lit<N>(0), b) << Lit<LOG2(N)+1>(bpos));
      q[bpos] = big_b <= Cat(Lit<N>(0), rem[i]);
      bvec<N> dif = rem[i] - (b << Lit<LOG2(N)>(bpos));
      rem[i+1] = Mux(q[bpos], rem[i], dif);
    }

    mod = rem[N];
    return q;
  }

  template <unsigned N> bvec<N> operator/(bvec<N> a, bvec<N> b) {
    return divider(a, b);
  }

  template <unsigned N> bvec<N> operator%(bvec<N> a, bvec<N> b) {
    bvec<N> r;
    divider(a, b, r);
    return r;
  }
};

#endif
