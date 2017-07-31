// Problem 3.11.4  Iterator of a Vector
//
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

#include <stdexcept>
#include <memory>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "gtest/gtest.h"

template <typename T>
class vector{
private:
  int size_;
  std::unique_ptr<T[]> data_;

public:
  vector(): size_(0), data_(nullptr) {};
  explicit vector(int size): size_(size), data_(new T[size_]) {};
  
  vector(const vector& v): size_(v.size_), data_(new T[size_]) {
    std::copy(&v.data_[0], &v.data_[v.size_], &data_[0]);
  };
  
  vector& operator=(const vector& v){ 
      //if (size_ != v.size_){throw "incompatible size";}; 
      size_ = v.size_;
      std::unique_ptr<T[]> temp(new T[size_]);
      data_ = move(temp);
      std::copy(&v.data_[0], &v.data_[v.size_], &data_[0]);
  }; 
  
  vector(vector&& v): size_(v.size_), data_(nullptr) {std::swap(data_, v.data_);};
  vector& operator=(vector&&v ){std::swap(size_, v.size_); std::swap(data_, v.data_);};
  
  vector(const std::initializer_list<T> values): size_(values.size()), data_(new T[size_]){
    std::copy(values.begin(), values.end(), &data_[0]);
  };
  
  int size() const { return size_; };
  
  void check_index(int i) const{
    if (i<0) {throw "Out of range";}
    if (i>size_) {throw "Out of range";}
  };
  
  T& operator[](int i) { 
      check_index(i); 
      return data_[i];
  };
  
  const T& operator[](int i) const { 
      check_index(i); 
      return data_[i];
  };
    
  struct iterator: public std::iterator<std::random_access_iterator_tag, T>{
    public:
        using value_type = T;
        using difference_type = int;
        
        /*
        constructor
        operator*()
        operator+(int rhs)
        operator-(const iterator& rhs)
        operator++()
        operator--()
        operator==()
        operator!=() 
         */
        
        iterator(): v_(nullptr), pos_(0){};
        iterator(vector& v, int pos):v_(v), pos_(pos){};
        iterator(const iterator& it) = default;
        iterator& operator=(const iterator& it) = default; 
        iterator(iterator&& it): pos_(it.pos_), v_(it.v_) {it.pos_=0; it.v_=vector<T>();};
        iterator& operator=(iterator&&it ){std::swap(pos_, it.pos_); std::swap(v_, it.v_);};
        
        //inline iterator& operator+=(difference_type rhs) {std::cout << "operator+=(diff rhs)" << std::endl; pos_ += rhs; return *this;}
        //inline iterator& operator-=(difference_type rhs) {std::cout << "operator-=(diff rhs)" << std::endl; pos_ -= rhs; return *this;}
        
        value_type& operator*(){ return v_[pos_]; };
        //const value_type& operator*() const {std::cout << "operator*() const" << std::endl;  return *v_[pos_]; };
        //inline value_type* operator->() const {std::cout << "operator->() const" << std::endl;  return *v_[pos_];}
        //inline value_type& operator[](int rhs) const {std::cout << "operator[](int rhs)" << std::endl; return *v_[rhs];}
        
        iterator& operator++() {pos_++; return *this;};
        inline iterator& operator--() {pos_--; return *this;}
        inline difference_type operator-(const iterator& rhs) const {return pos_-rhs.pos_;}
        inline iterator operator+(const difference_type rhs) {pos_ = pos_+rhs; return *this;}
        inline iterator operator-(const difference_type rhs) {pos_ = pos_-rhs; return *this;}
        //inline iterator operator+(difference_type rhs) const {std::cout << "operator+(int rhs) const" << std::endl; iterator tmp(*this); tmp.pos_ = pos_+rhs; return tmp;}
        //inline iterator operator-(difference_type rhs) const {std::cout << "operator-(int rhs) const" << std::endl; iterator tmp(*this); tmp.pos_ = pos_-rhs; return tmp;}
        //friend inline iterator operator+(difference_type lhs, const iterator& rhs) {std::cout << "operator+(int lhs, const iterator& rhs)" << std::endl; return rhs + lhs;}
        //friend inline iterator operator-(difference_type lhs, const iterator& rhs) {std::cout << "operator-(int lhs, const iterator& rhs)" << std::endl; return rhs - lhs;}
        
        // compare position? jep, otherwise for loop does not work
        bool operator == (const iterator& rhs) const {return (pos_ == rhs.pos_); };
        bool operator != (const iterator& rhs) const {return (pos_ != rhs.pos_); };
        inline bool operator>(const iterator& rhs) const {return pos_ > rhs.pos_;}
        inline bool operator<(const iterator& rhs) const {return pos_ < rhs.pos_;}
        //inline bool operator>=(const iterator& rhs) const {std::cout << "operator>=()" << std::endl; return v_[pos_] >= rhs.v_[rhs.pos_];}
        //inline bool operator<=(const iterator& rhs) const {std::cout << "operator<=()" << std::endl; return v_[pos_] <= rhs.v_[rhs.pos_];}

    private:
        int pos_;
        vector v_;
  };

  iterator begin(){ return iterator(*this, 0); };
  
  iterator end(){ return iterator(*this, size_); };

};

int main (int argc, char **argv) 
{
    vector<int> v = {0,10,2,30, 4, 50, 6, 70,10,2,30, 4, 50, 6, 70};
    vector<int> v1 = {0,10,2,30, 4, 50, 6, 70};
    
    v = v1; //std::move(v1);
    
    for (auto a : v) { std::cout << a << " "; } 
    std::cout << '\n';
    for (auto a : v1) { std::cout << a << " "; }   
    std::cout << '\n';
    std::cout << v.end() - v.begin() << std::endl;
    std::sort(v.begin(), v.end());
    std::cout << *(v.begin()) << std::endl;
    std::cout << *(v.begin()+1) << std::endl;
    std::cout << *(v.begin()+2) << std::endl;
    std::cout << *(v.begin()+3) << std::endl;
    vector<int>::iterator temp1 = v.begin();
    vector<int>::iterator temp2 = v.begin()+2;
    std::swap(temp1, temp2);
    // std::iter_swap((v.begin()), (v.begin()+2));
    // std::iter_swap(&(v[1]), &(v[1+2]));
    // std::swap((v[1]), (v[1+2]));
    std::cout << *(v.end()-1) << std::endl;
    std::cout << *temp1 << std::endl;
    std::cout << *temp2 << std::endl;
    // // OK: iter_swap requires ValueSwappable
    for (auto a : v) { std::cout << a << " "; }   
    std::cout << '\n';
    
    
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
};

