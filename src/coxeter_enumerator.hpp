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
public:
  void display();
  void init();
  bool next();
  const Element<T, N>& get() const;
};

template <char T, Int N> inline
void CoxeterEnumerator<T, N>::display() {
  cout << "Enumerator for element of Coxeter group of type " << T << '_' << N << endl;
}

template <char T, Int N> inline
void CoxeterEnumerator<T, N>::init() {
  current.set_identity();
}

template <char T, Int N> inline
bool CoxeterEnumerator<T, N>::next() {
  return current.next();
}

template <char T, Int N> inline
const Element<T, N>& CoxeterEnumerator<T,N>::get() const {
  return current;
}
