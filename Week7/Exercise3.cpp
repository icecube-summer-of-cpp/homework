#include<iostream>
#include<memory>
#include <assert.h>

template <typename T>
class my_stack
{
  void check_index(int i) const {assert(i<max_size && i>=0);}
  public:
    explicit my_stack(int size):
      max_size(size), data( new T[max_size]), my_size(0){}

    //return last element
    T top() const {
      if (my_size>0 && max_size>0);
      return data[my_size-1];
    }
    //add new element
    void push (T newone){
      check_index(my_size);
      data[my_size] = newone;
      my_size++;
    }
    //clear stack
    void clear(){
      for(int i=0;i<my_size;i++){
	data[i] = 0;
	my_size--;
      } 
    }
    //remove last element
    void pop(){
      if (my_size>0 and max_size>0){ 
	data[my_size-1] = 0;
      	my_size--;
      }
    }
    int size() const {return my_size;}
    int maxsize() const {return max_size;}
    int full() const {return max_size==my_size;}
    int empty() const {return my_size==0;}

    const T& operator[](int i) const{
      check_index(i);
      return data[i];
    }

  private:
    int		 		my_size;
    int				max_size;
    std::unique_ptr<T[]>	data;
};


int main(){
  using namespace std;
  my_stack<float> test(5);

  cout << "Maximum stack size: " << test.maxsize() << endl;
  cout << "Stack size: "  <<test.size() << endl;
  cout << "Stack empty? " <<test.empty() << endl;
  cout << "Stack full? "  <<test.full() << endl;
  test.push(int(3));
  cout << "Added one variable. Stack size: " <<test.size() << endl;
  cout << "Stack empty? " <<test.empty() << endl;
  cout << "Stack full? "  <<test.full() << endl;
  cout << "What's the value? " << test[0] << endl;
  //cout << "What if we try to overflow? " << test[5] << endl;
  test.pop();
  cout << "Popped" << endl;
  cout << "Maximum stack size: " << test.maxsize() << endl;
  cout << "Stack size: "  <<test.size() << endl;
  cout << "Stack empty? " <<test.empty() << endl;
  cout << "Stack full? "  <<test.full() << endl;
  test.clear();
  cout << "Cleared the stack" << endl;
  cout << "Maximum stack size: " << test.maxsize() << endl;
  cout << "Stack size: "  <<test.size() << endl;
  cout << "Stack empty? " <<test.empty() << endl;
  cout << "Stack full? "  <<test.full() << endl;

  return 0;
}
