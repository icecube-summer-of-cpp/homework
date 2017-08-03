// Summer of C++ 
// Quiz Week 8 
// Solution by: Rene Reimann

/*
 * 
 * 3.11.7
 * 
 * Stack of bool
 * 
 * Specialize your stack implementation from 3.11.3 for bool. Use an unsigned char for 8 bool as in Section 3.6.1.
 * 
 */

//#include "gtest/gtest.h"
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

template <typename T>
struct stack_element{
    T value;
    std::shared_ptr<stack_element<T>> ptr;
    
    explicit stack_element(T value, std::shared_ptr<stack_element<T>> ptr): value(value), ptr(ptr){};
};

template <typename T, int max_size=4096>
class stack{
    public:
        stack(): size_(0), last_elem_(nullptr){};
        
        ~stack()=default;
        
        T top(){
            if (empty()){ throw "Empty"; };
            return (*last_elem_).value;
        };
        
        void pop(){
            if (empty()){ throw "Underflow"; };
            size_ -= 1;
            last_elem_ = (*last_elem_).ptr;
        };
        
        void push(T val){
            if (full()){ throw "Overflow"; };
            size_ += 1;
            last_elem_ = std::make_shared<stack_element<T>>(val, last_elem_);
        };
        
        void clear(){
            size_ = 0;
            last_elem_ = nullptr;
        };
        
        int size(){
            return size_;
        };
        
        int max(){
            return MAX_SIZE_;
        };
        
        bool full(){
            return size_ == MAX_SIZE_;
        };
        
        bool empty(){
            return size_ == 0;
        };
        
    private:
        std::shared_ptr<stack_element<T>> last_elem_;
        int size_;
        static const int MAX_SIZE_ = max_size;
};

class vector_bool_proxy{
    public:
        vector_bool_proxy(unsigned char& byte, int p): byte(byte), mask(1<<p){};
    private:
        unsigned char& byte;
        unsigned char mask;
};

bool get_element(char c, uint pos){
    if (pos >= 8) {throw "Out of Range";}
    // moves the bytes by 'pos' positions to the right, so that we have the 'pos' one and make an and with the mask 00000001
    return (c >> pos & 1);
}

std::string char_2_binary(char c){
    std::stringstream s;
    s << "0b";
    for (int position=7; position >= 0; position--){
        s << get_element(c, position);
    }
    return s.str();
}

void set_element(unsigned char& c, uint pos, bool val){
    if (pos >= 8) {throw "Out of Range";}
    char mask = 1 << pos; // zero with a one at position pos
    if (val == true){
        c |= mask;
    }else{
        c &= ~mask;
    };
};

template <>
class stack<bool, 4096>{
private:
  const size_t max_size{4096};
  std::vector<unsigned char> elements_;
  size_t top_index_{0};
  
public:
  stack() = default;
  ~stack() = default;  
  stack(const stack&) = default;
  stack(stack&&) = default;
  stack& operator=(const stack&) = default;
  stack& operator=(stack&&) = default;  
  
  bool top(){
      if (empty()){ throw "Empty"; }
      int elem_index = (top_index_-1)/8;
      int pos_index = (top_index_-1)%8;
      return get_element(elements_[elem_index], pos_index);
  }
  
  void pop(){
      if (empty()){ throw "Underflow"; }
      top_index_ -= 1;
      if (top_index_%8 == 0){ elements_.pop_back(); };
  }
  
  void print(){
    std::cout << "Size: " << top_index_ << std::endl;
    for (auto it = elements_.begin() ; it != elements_.end(); ++it){
        std::cout << char_2_binary(*it) << std::endl;
    }
  }
  
  void push(bool value){
      if (full()){ throw "Overflow";};
      
      if (top_index_%8 == 0){
        elements_.push_back(0b00000000);
      }
      int elem_index = (top_index_)/8;
      int pos_index = (top_index_)%8;
      
      set_element(elements_[elem_index], pos_index, value);
      
      top_index_ += 1;
  }
  
  void clear(){
    elements_.clear();
    top_index_ = 0;
  }
  
  int max(){return max_size;}
  
  size_t size(){ return top_index_; }
  
  bool full(){ return top_index_ == max_size; }
  
  bool empty(){ return top_index_ == 0;}
};

int main (int argc, char **argv) 
{
    stack<bool> st;
    
    for (int i=0; i< 25; i++){
        st.print();
        st.push(i%2==1);
        std::cout << std::boolalpha << st.top() << std::endl;
    }
    for (int i=0; i< 25; i++){
        st.pop();
        st.print();
        std::cout << std::boolalpha << st.top() << std::endl;
    }
    
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
};
