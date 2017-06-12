//
// Created by Frederik Lauber on 12.06.17.
//

#include <iostream>
#include "old_res.h"
#include <memory>


class Val{
    std::shared_ptr<Val> previous;
public:
    double val;
    Val(double x, std::shared_ptr<Val> prev){
      addVal(x);
      this->val = x;
      this->previous = prev;
    }
    ~Val(){
      popVal();
    }
};

//struct val_deleter{
//    void operator()(Val* x){
//      popVal();
//    }
//};

class valManager{
  std::shared_ptr<Val> val;
public:
    //double popVal(){
    //  auto res = this->val.val;
    //  this->val = this->previous;
    //  return res;
    //};
    std::shared_ptr<Val> addVal(double x){
      std::shared_ptr<Val> tmp (new Val(x, this->val));
      this->val = tmp;
      return tmp;
    };
};

int main(){
  {
    valManager vM;
    auto tmp0 = vM.addVal(23);
    auto tmp1 = vM.addVal(123213);
    auto tmp2 = vM.addVal(232332);
    std::cout << tmp0->val << std::endl;
    std::cout << tmp1->val << std::endl;
    std::cout << tmp2->val << std::endl;
  }
  return 0;
}