//****************************************************************************//
//    Copyright (C) 2024 Jean Fromentin <jean.fromentin@univ-littoral.fr>     //
//                                                                            //
//  This file is part of CoxModLen <https://github.com/jfromentin/coxmodlen>  //
//                                                                            //
//  CoxModLen is free software: you can redistribute it and/or modify it      //
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

#include "permutation.hpp"

template <char T, Int N> class Element;

template <Int N> class Element<'A', N> {
private:
  Permutation<N + 1> sigma;
public:
  void init(size_t nb_fixed, Int* fixed);
  bool next(size_t nb_fixed);
  size_t length(Int k, Int h);
  void display() const;
};


template <Int N> class Element<'B', N> {
private:
  Permutation<N> sigma;
  Int sign[N];
public:
  void init(size_t nb_fixed, Int* fixed);
  bool next(size_t nb_fixed);
  size_t length(Int k, Int h);
  void display() const;
};

template <Int N> class Element<'D', N> {
private:
  Int nb_minus;
  Permutation<N> sigma;
  Int sign[N];
public:
  void init(size_t nb_fixed, Int* fixed);
  bool next(size_t nb_fixed);
  size_t length(Int k, Int h);
  void display() const;
};

template <Int N> inline
void Element<'A', N>::init(size_t nb_fixed, Int* fixed) {
  sigma.init(nb_fixed, fixed);
}

template <Int N> inline
bool Element<'A', N>::next(size_t nb_fixed) {
  return sigma.next(nb_fixed);
}

template <Int N> inline
size_t Element<'A', N>::length(Int k, Int h) {
  size_t res = 0;
  for (Int i = 0; i <= N; ++ i) {
    Int v = sigma[i];
    for (Int j = i + h; j <= N; j += k) {
      if (v > sigma[j]) ++ res;
    }
  }
  return res;
}

template<Int N> inline
void Element<'A', N>::display() const {
  cout << sigma << endl;
}

template<Int N> inline
void Element<'B', N>::init(size_t nb_fixed, Int* fixed) {
  sigma.init(nb_fixed, fixed);
  for (size_t i = 0; i < N; ++i) sign[i] = 1;
}

template <Int N> inline
bool Element<'B', N>::next(size_t nb_fixed) {
  for (size_t i = 0; i < N; ++i) {
    if (sign[i] == 1) {
      sign[i] = -1;
      for (size_t j = 0; j < i; ++ j) sign[j] = 1;
      return true;
    }
  }
  for (size_t i = 0; i < N; ++i) sign[i] = 1;
  return sigma.next(nb_fixed);
}

template <Int N> inline
size_t Element<'B', N>::length(Int k, Int h) {
  Int tab[2 * N + 1];
  tab[N] = 0;
  for (Int i = 1; i <= N; ++ i) {
    Int v = sign[i - 1] * (sigma[i - 1] + 1);
    tab[N + i] = v;
    tab[N - i] = - v;
  }
  size_t res = 0;
  for (Int i = 0; i <= 2 * N; ++ i) {
    Int vi = tab[i];
    for (Int j = i + h; j <= 2 * N; j += k) {
      if (vi > tab[j]) ++ res;
    }
  }
  return res / 2;
}

template<Int N> inline
void Element<'B', N>::display() const {
  cout << '(' << ((sign[0] == -1) ? '-' : '+') << sigma[0];
  for (int i = 1; i < N; ++ i) {
    cout << ',' << ((sign[i] == -1) ? '-' : '+') <<  sigma[i];
  }
  cout << ')' << endl;
}

template<Int N> inline
void Element<'D', N>::init(size_t nb_fixed, Int* fixed) {
  sigma.init(nb_fixed, fixed);
  nb_minus = 0;
  for (size_t i = 0; i < N; ++i) sign[i] = 1;
}

template <Int N> inline
bool Element<'D', N>::next(size_t nb_fixed) {
  bool sign_is_modified;
  do{
    sign_is_modified = false;
    for (size_t i = 0; i < N and not sign_is_modified; ++i) {
      if (sign[i] == 1) {
	sign_is_modified = true;
	++ nb_minus;
	sign[i] = -1;
	for (size_t j = 0; j < i; ++ j) sign[j] = 1;
	nb_minus -= i;
      }
    }    
  } while(nb_minus % 2 != 0 and sign_is_modified);
  if (sign_is_modified) return true;
  for (size_t i = 0; i < N; ++i) sign[i] = 1;
  nb_minus = 0;
  return sigma.next(nb_fixed);
}

template <Int N> inline
size_t Element<'D', N>::length(Int k, Int h) {
  size_t res = 0;
  Int tab[N + 1];
  tab[0] = 0;
  for (Int i = 1; i <= N; ++ i) {
    Int v = sign[i - 1] * (sigma[i - 1] + 1);
    tab[i] = v;
  }
  for (Int i = 1; i < N; ++ i) {
    Int vi = tab[i];
    for (Int j = i + 1; j <= N; ++ j) {
      if ( ((j - i) % k == h) and tab[i] > tab[j] ) ++ res;
      if ( ((2 * N - (j + i)) % k == h) and -tab[i] > tab[j]) ++ res;
    }
  }
  return res;

}

template<Int N> inline
void Element<'D', N>::display() const {
  cout << '(' << ((sign[0] == -1) ? '-' : '+') << sigma[0];
  for (int i = 1; i < N; ++ i) {
    cout << ',' << ((sign[i] == -1) ? '-' : '+') <<  sigma[i];
  }
  cout << ')' << endl;
}
