#include <exception>
#include <assert.h>
#include <vector>


class Full: public std::exception
{
    const char* what() const throw() { return "Stack is full.\n"; }
};
class Empty: public std::exception
{
    const char* what() const throw() { return "Stack is empty.\n"; }
};

template <class T, unsigned N>
class fixedsizestack{
    T data[N]; //not sure how to do this with a vector...
    unsigned pos;
public:
    fixedsizestack() = default;
    ~fixedsizestack() = default;
    T& top(){
      return data[pos];
    };
    void pop(){
      if (pos == 0){
        throw Empty();
      }
      ~data[pos--];
      assert(pos >= 0);
    };
    void push(const T& newval){
      if (pos == N){
        throw Full();
      }
      data[++pos] = newval;
      assert(pos <= N);
    };
    void clear(){
      for(; pos>0; --pos){
        ~data[pos];
      }
    };
    unsigned size(){
      return pos;
    };
    
    bool full(){
      return pos == N;
    };
    bool empty(){
      return pos == 0;
    };
};


//add partial implementation for bool types
template <unsigned N>
class fixedsizestack<bool, N>{
    unsigned char data[N/8+1];
    unsigned pos;
    class bit_proxy{
        unsigned char& byte;
        unsigned char mask;
    public:
        bit_proxy(unsigned char& byte, unsigned short p) : byte(byte), mask(1 << p){};
        operator bool() const {return byte & mask;};
        bit_proxy& operator=(bool b){
          if(b){
            byte|= mask;
          }else{
            byte&= ~mask;
          }
          return *this;
        }
      
    };
public:
    fixedsizestack() = default;
    ~fixedsizestack() = default;
    bool top(){
      unsigned char& tmp = data[pos / 8];
      return bit_proxy(tmp, pos % 8);
    };
    void pop(){
      if (pos == 0){
        throw Empty();
      }
      pos--;
      assert(pos >= 0);
    };
    
    void push(const bit_proxy& newval){
      this->push(newval);
    };
    
    void push(const bool& newval){
      if (pos == N){
        throw Full();
      }
      ++pos;
      bit_proxy(data[pos / 8], pos % 8) = newval;
      assert(pos <= N);
    };
    
    
    void clear(){
      pos = 0;
      //no need to call destructors on bools
    };
    unsigned size(){
      return pos;
    };
    
    bool full(){
      return pos == N;
    };
    bool empty(){
      return pos == 0;
    };
};





int main(){
  const unsigned N = {100};
  auto stack = fixedsizestack<bool, N>();
  for(int i = 1; i <=N; i++){
    stack.push(false);
  }
  assert(!stack.top());
  assert(stack.size() == N);
  assert(stack.full());
  stack.clear();
  assert(stack.empty());
  
  bool exceptionThrown = false;
  try
  {
    stack.pop();
  }
  catch(Empty&){
    exceptionThrown = true;
  }
  assert(exceptionThrown);
  
  exceptionThrown = false;
  try
  {
    for(int i = 1; i <=N+1; i++){
      stack.push(true);
    }
  }
  catch(Full&){
    exceptionThrown = true;
  }
  assert(stack.top());
  assert(exceptionThrown);
  return 0;
}