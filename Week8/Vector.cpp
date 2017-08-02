#include <cassert>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <iterator>
#include <iostream>

template <typename T>
class vector{
//private:

public:
  int size_;
  std::unique_ptr<T[]> data_;
  //constructor
  explicit vector(int size): size_(size),data_(new T[size]) {}
  //default constructor
  vector(): size_(0), data_(0) {}
  
  //copy constructor
  vector(const vector& v) : size_(v.size_), data_(new T[size_]) 
  {
    std::copy(&v.data_[0],&v.data_[v.size_], &data_[0]);
  }
  //move constructor
  vector(vector&& v): size_(v.size_), data_(std::move(v.data_)) {v.size_ = 0;}
  //copy assignment
  vector& operator=(const vector& v)
  {
    if (this == &v) return *this;
    check_size(v.size_);
    std::copy(&v.data_[0],&v.data_[v.size_], &data_[0]);
  }
  //move assignment
  vector& operator=(vector&& v)
  {
    assert(size_ == 0 || size_ == v.size_);
    std::swap(data_,v.data_);
    return *this;
  }
  //initializer list
  //vector(const std::initializer_list<T> values){/* implement me */}
  //destructor
  ~vector(){}


  int size() const { return size_;}
  void check_size(int that_size) const { assert(size_ == that_size); }
  void check_index(int that_index) const {assert(size_ > that_index && that_index >= 0); }

  //need this to access value that is defined
  const T& operator[](int i) const
  {
    check_index(i);
    return data_[i];
  }
  //need this to place new value
  T& operator[](int i) 
  {
    check_index(i);
    return data_[i];
  }

  struct iterator
  {
    iterator(T* x) : value(x) {}
    T& operator*() { return *value;}
    iterator operator++(){iterator i= *this;value++;return i;}
    iterator operator--(){iterator i= *this;value--;return i;}
    iterator operator-(iterator that){that= *this;value--;return that;}
    bool operator!=(const iterator that) const { return value != that.value;}

    T* value;
  };

  iterator begin(){ return iterator(&(this->data_[0])) ;}
  iterator end(){ return iterator(&(this->data_[1])) ;}
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v)
{
  os << '[';
  for (int i= 0; i < v.size(); ++i) os << v[i] << ',';
  os << ']';
  return os;
}

int main()
{
  vector<double> v(4) ;
  v[0]= 1.0; v[2]= 2.0; v[3] = -3.0;
  std::cout << v << std::endl;
  float j = v[0];
  std::cout << j << std::endl;
  std::sort(v.begin(), v.end());
  return 0;
}
