//****************************************************************************//
//    Copyright (C) 2024 Jean Fromentin <jean.fromentin@univ-littoral.fr>     //
//                                                                            //
//  This file is part of CoxModLen  <https://github.com/jfromentin/coxmodlen> //
//                                                                            //
//  HP-Combi is free software: you can redistribute it and/or modify it       //
//  under the terms of the GNU General Public License as published by the     //
//  Free Software Foundation, either version 3 of the License, or             //
//  (at your option) any later version.                                       //
//                                                                            //
//  CoxModLen is distributed in the hope that it will be useful, but WITHOUT  //
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or     //
//  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License      //
//  for  more details.                                                        //
//                                                                            //
//  You should have received a copy of the GNU General Public License along   //
//  with CoxModLen. If not, see <https://www.gnu.org/licenses/>.              //
//****************************************************************************//

#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

#include "common.hpp"

template<Int N> class Permutation{
private:
  Int tab[N];
public:
  Permutation();
  void set_identity();
  Int operator[](Int i) const;
  Int& operator[](Int i);
  bool next();
};

template<Int N> ostream& operator<<(ostream& os, const Permutation<N>& P);

inline void swap(Int& x, Int& y) {
  Int t = x;
  x = y;
  y = t;
}

template<Int N> inline void
Permutation<N>::set_identity() {
  for (size_t i = 0; i < N; ++ i) {
    tab[i] = i;
  }
}

template<Int N> inline
Permutation<N>::Permutation() {
}

template<Int N> inline
Int Permutation<N>::operator[](Int i) const {
  assert((0 <= i) and (i < N));
  return tab[i];
}

template<Int N> inline
Int& Permutation<N>::operator[](Int i){
  assert((0 <= i) and (i < N));
  return tab[i];
}

template<Int N>
bool Permutation<N>::next() {
  for(size_t first = 1; first < N; ++first) {
    if(tab[first - 1] < tab[first]) {
      size_t j = 0;
      while(tab[first] < tab[j]) ++ j;
      swap(tab[j], tab[first]);
      size_t i = first - 1;
      j = 0;
      while(j < i) swap(tab[i --], tab[j ++]);
      return true;
    }
  }
  return false;
}

template<Int N> ostream&
operator<<(ostream& os, const Permutation<N>& P) {
  os << '(' << P[0];
  for (int i = 1; i < N; ++ i) {
    os << ',' << P[i];
  }
  return os << ')';
}

#endif