#include <stdexcept>
#include <memory>
#include <algorithm>
#include <iterator>
#include <iostream>

template <typename T>
class vector{
private:
  int size_;
  std::unique_ptr<T[]> data_;

public:
  explicit vector(int size) {/* implement me */}
  vector(const vector& v) {/* implement me */}
  vector(const std::initializer_list<T> values){/* implement me */}
  int size() const { /* implement me */}
  const T& operator[](int i) const {/* implement me */}
    
  struct iterator{/* implement me */};

  iterator begin(){ /* implement me */}
  iterator end(){ /* implement me */}

};
