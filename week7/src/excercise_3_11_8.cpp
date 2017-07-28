// Summer of C++ 
// Quiz Week 7 
// Solution by: Rene Reimann

/*
 * 
 * 3.11.8
 * 
 * Stack with Custom Size
 * 
 * Reise your stack implementation from Exercise 3.11.3 (and optionally that of Excercise 3.11.7) with a user-defined size. 
 * The size is passed as the second template argument. The default should be 4096.
 * 
 */

#include "sstream"
//#include "gtest/gtest.h"
#include <iostream>
#include <memory>

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

int main (int argc, char **argv) 
{
    stack<int, 10> st;
    
    std::cout << st.max() << std::endl;
    std::cout << "" << std::endl;
    std::cout << st.empty() << std::endl;
    std::cout << st.full() << std::endl;
    std::cout << st.size() << std::endl;
    
    st.push(10);
    std::cout << "" << std::endl;
    std::cout << st.top() << std::endl;
    std::cout << st.empty() << std::endl;
    std::cout << st.full() << std::endl;
    std::cout << st.size() << std::endl;
    st.push(33);
    std::cout << "" << std::endl;
    std::cout << st.top() << std::endl;
    std::cout << st.empty() << std::endl;
    std::cout << st.full() << std::endl;
    std::cout << st.size() << std::endl;
    st.push(20);
    std::cout << "" << std::endl;
    std::cout << st.top() << std::endl;
    std::cout << st.empty() << std::endl;
    std::cout << st.full() << std::endl;
    std::cout << st.size() << std::endl;
    st.pop();
    std::cout << "" << std::endl;
    std::cout << st.top() << std::endl;
    std::cout << st.empty() << std::endl;
    std::cout << st.full() << std::endl;
    std::cout << st.size() << std::endl;
    
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
};
