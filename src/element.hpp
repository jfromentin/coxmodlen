//****************************************************************************//
//    Copyright (C) 2024 Jean Fromentin <jean.fromentin@univ-littoral.fr>     //
//                                                                            //
//  This file is part of CoxModLen  <https://github.com/jfromentin/coxmodlen> //
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
  void set_identity();
  bool next();
  void display() const;
};


template <Int N> class Element<'B', N> {
private:
  Permutation<N> sigma;
  Int sign[N];
public:
  void set_identity();
  bool next();
  void display() const;
};


template <Int N> inline
void Element<'A', N>::set_identity() {
  sigma.set_identity();
}

template <Int N> inline
bool Element<'A', N>::next() {
  return sigma.next();
}

template<Int N> inline
void Element<'A', N>::display() const {
  return cout << sigma << endl;
}

template <Int N> inline
void Element<'B', N>::set_identity() {
  sigma.set_identity();
  for (size_t i = 0; i < N; ++i) sign[i] = 1;
}

template <Int N> inline
bool Element<'B', N>::next() {
  for (size_t i = 0; i < N; ++i) {
    if (sign[i] == 1) {
      sign[i] = -1;
      for (size_t j = 0; j < i; ++ j) sign[j] = 1;
      return true;
    }
  }
  for (size_t i = 0; i < N; ++i) sign[i] = 1;
  return sigma.next();
}


template<Int N> inline
void Element<'B', N>::display() const {
  cout << '(' << ((sign[0] == -1) ? '-' : '+') << sigma[0];
  for (int i = 1; i < N; ++ i) {
    cout << ',' << ((sign[i] == -1) ? '-' : '+') <<  sigma[i];
  }
  cout << ')' << endl;
}
