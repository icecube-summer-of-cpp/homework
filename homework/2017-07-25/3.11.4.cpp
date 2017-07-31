//not working :(

#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iterator>



// Problem 3.11.4  Iterator of a Vector
// Add the methods begin() and end() for returning begin and end iterator to
// class vector.  Add the types iterator and const_iterator to the class as well.
// Note that pointers are models of the concept of random-access iterators.
//
// http://en.cppreference.com/w/cpp/concept/RandomAccessIterator
//
// Use the STL functions sort for ordering vector entries to demonstrate that
// your iterators work as they should.
//
// http://en.cppreference.com/w/cpp/algorithm/sort
//



template <typename T>
class vector{
private:
    unsigned int size_;
    std::unique_ptr<T[]> data_;

public:
    explicit vector(unsigned int size) : data_(new T[size]), size_(size){
    }
    vector(const vector& v)  : data_(new T[v.size()]), size_(v.size()) {
      for(int i=0; i< v.size(); ++i){
        this->data_[i] = v[i];
      }
    }
    vector(const std::initializer_list<T> values)  : data_(new T[values.size()]), size_(values.size()){
      int i = 0;
      for(auto tmp: values){
        this->data_[i++] = tmp;
      }
    }
    
    int size() const {
      return this->size_;
    }
    const T& operator[](unsigned int i) const {
      return this->data_[i];
    }
    
    class iterator{
        vector<T>  &obj;
        unsigned long pos;
    public:
        iterator(vector<T> &obj, unsigned long pos=0): pos(pos), obj(obj){};
        iterator operator++(int){++pos;};
        T operator* (){return this->obj[pos];};
        bool operator==(iterator rhs){
          return this->pos == rhs.pos;
        };
        
        bool operator!=(iterator rhs){
          return this->pos != rhs.pos;
        };
    };
    
    iterator begin(){
      return iterator(*this, 0);
    }
    iterator end(){
      return iterator(*this, this->size_);
    }
  
};



int main()
{
  vector<float> v({1.0, 10.0, 2.0, -3.0});
  std::sort(v.begin(), v.end());
  auto test = v.begin();
  std::cout << *test << std::endl;
  return 0;
}
