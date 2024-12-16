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


#include <fstream>
#include "coxeter_enumerator.hpp"
#include "results.hpp"
#include "config.hpp"

int main(int argc, char** argv) {
  if (argc != 4) {
    cerr << "You must specify three diffrent integers a, b and c" << endl;
    exit(-1);
  }
  Int a = atoi(argv[1]);
  Int b = atoi(argv[2]);
  Int c = atoi(argv[3]);
  if (a == b or a == c or b == c) {
    cerr << "a, b and c must be different" << endl;
    exit(-1);
  }
  CoxeterEnumerator<T, N> enumerator(a, b, c);
  Int Prank = enumerator.permutation_rank();
  if (a >= Prank or b >= Prank or c >= Prank) {
    cerr << "a, b and c must be in [0, Prank - 1]" << endl;
    exit(-1);
  }
  enumerator.init();
  Results results;

  // Main loop
  do{
    auto x = enumerator.get();
    size_t l = x.length(k, h);
    results.add(l);
  } while(enumerator.next());

  // Save results
  string filename = output_dir + "/" + T + to_string(N) + "_for_" + to_string(k) + "_" + to_string(h) + "_with_" + argv[1] + "_" + argv[2] + "_" + argv[3];
  ofstream file(filename.c_str(), ios::trunc);
  file << T << N << endl;
  file << k << " " << h << endl;
  file << a << " " << b << " " << c << endl;
  file << results.get_size() << endl;
  file << "-----------" << endl;
  for (size_t i = 0; i < results.get_size(); ++ i) file << results.read(i) << endl;
  file.close();
  exit(0);
}
