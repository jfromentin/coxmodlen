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

#ifndef RESULTS_HPP
#define RESULTS_HPP

class Results{
private:
  size_t size;
  size_t data[1024];
public:
  Results();
  void add(size_t i);
  size_t read(size_t i) const;
  size_t get_size() const;
  void display() const;
};

inline Results::Results() {
  size = 0;
  for (size_t i = 0; i < 1024; ++ i) data[i] = 0;
}

inline void Results::add(size_t i) {
  if (i >= size) {
    data[i] = 1;
    size = i + 1;
  }
  else{
    ++ data[i];
  }
}

inline size_t Results::read(size_t i) const {
  return data[i];
}

inline size_t Results::get_size() const {
  return size;
}

inline void Results::display() const {
  cout << '[' << data[0];
  for (size_t i = 1; i < size; ++ i) {
    cout << ',' << data[i];
  }
  cout << ']' <<  endl;
}
#endif
