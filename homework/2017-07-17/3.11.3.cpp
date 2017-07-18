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
    T data[N];
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


int main(){
  const unsigned N = {100};
  auto stack = fixedsizestack<int, N>();
  for(int i = 1; i <=N; i++){
    stack.push(i);
  }
  assert(stack.top() == N);
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
      stack.push(i);
    }
  }
  catch(Full&){
    exceptionThrown = true;
  }
  assert(exceptionThrown);
  return 0;
}