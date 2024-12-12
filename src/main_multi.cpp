#include <fstream>
#include "permutation.hpp"

int main(int argc, char** argv) {
  if (argc != 4) {
    cerr << "You must specify three diffrent integers a, b and c in [0, Prank - 1]" << endl;
    exit(-1);
  }
  size_t a = atoi(argv[1]);
  size_t b = atoi(argv[2]);
  size_t c = atoi(argv[3]);
  if (a == b or a == c or b == c) {
    cerr << "a, b and c must be different" << endl;
    exit(-1);
  }
  if (a >= Prank or b >= Prank or c >= Prank) {
    cerr << "a, b and c must be in [0, Prank - 1]" << endl;
    exit(-1);
  }
  size_t total = 0;
  size_t res[ResSize];
  for (int i = 0; i < ResSize; ++ i) res[i] = 0;
  Permutation sigma;
  cout << " a = " << a << endl;
  cout << " b = " << b << endl;
  cout << " c = " << c << endl;
  sigma.init3(a, b, c);
  do{
    int l = sigma.k_length();
    res[l] += 1;
    total += 1;
  } while(sigma.next3());
  string filename = "/nfs/home/lmpa/jfromentin/git/brenti_length/output/res_" + to_string(Arank) + "_" + argv[1] + "_" + argv[2] + "_" + argv[3];
  ofstream file(filename.c_str(), ios::trunc);
  file << Arank << ' ' << a << ' ' << b << ' ' << c << endl;
  file << total << endl;
  for (int i = 0; i < ResSize; ++ i) file << res[i] << endl;
  file.close();
  exit(0);
 
}
