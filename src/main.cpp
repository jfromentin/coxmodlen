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


#include "coxeter_enumerator.hpp"
#include "results.hpp"

int main(){
  Int k = 2;
  Int h = 1;
  Results res;
  CoxeterEnumerator<'D', 10> enumerator;
  enumerator.display();
  enumerator.init();
  do{
    auto x = enumerator.get();
    size_t l = x.length(k, h);
    res.add(l);
  }while(enumerator.next());
  res.display();
}
