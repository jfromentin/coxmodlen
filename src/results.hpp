#ifndef RESULTS_HPP
#define RESULTS_HPP

#include <vector>

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
