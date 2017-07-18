#include <utility>
#include <iostream>
#include <memory>

template<typename T>
class make_uniqueown {
    T *obj;
public:
    make_uniqueown<T>(T &&arg) {
      obj = new T(std::forward<T>(arg));
    }
    
    ~make_uniqueown() {
      delete this->obj;
    };
    
    make_uniqueown<T>& operator=(make_uniqueown<T>&& src) = default;
    make_uniqueown<T>(make_uniqueown<T>&& v) = default;
    make_uniqueown<T>(const make_uniqueown<T>& c) = delete;
    make_uniqueown<T>& operator=(const make_uniqueown<T>& src) = delete;
    T* get() const
    { return obj; }
    
};


int main(){
  auto a = make_uniqueown<int>(1);
  auto b = std::make_unique<int>(2);
  std::cout << *a.get();
  std::cout << *b.get();
  return 0;
}