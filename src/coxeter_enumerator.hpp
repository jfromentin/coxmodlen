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

#include "element.hpp"

template <char T, Int N> class CoxeterEnumerator{
private:
  Element<T, N> current;
  size_t nb_fixed;
  Int fixed[3];
public:
  CoxeterEnumerator();
  CoxeterEnumerator(Int a);
  CoxeterEnumerator(Int a, Int b);
  CoxeterEnumerator(Int a, Int b, Int c);
  void display();
  void init();
  bool next();
  const Element<T, N>& get() const;
};

template <char T, Int N> inline
void CoxeterEnumerator<T, N>::display() {
  cout << "Enumerator for element of Coxeter group of type " << T << '_' << N << " with ";
  if (nb_fixed ==0) cout << "no fixed pattern." << endl;
  else{
    cout << "pattern ... " << fixed[0];
    for (size_t i = 1; i < nb_fixed; ++ i) cout << ' ' << fixed[i];
    cout << endl;
  }
}

template <char T, Int N> inline
CoxeterEnumerator<T,N>::CoxeterEnumerator () {
  nb_fixed = 0;
}

template <char T, Int N> inline
CoxeterEnumerator<T,N>::CoxeterEnumerator (Int a) {
  nb_fixed = 1;
  fixed[0] = a;
}

template <char T, Int N> inline
void CoxeterEnumerator<T, N>::init() {
  current.init(nb_fixed, fixed);
}

template <char T, Int N> inline
bool CoxeterEnumerator<T, N>::next() {
  return current.next(nb_fixed);
}

template <char T, Int N> inline
const Element<T, N>& CoxeterEnumerator<T,N>::get() const {
  return current;
}
