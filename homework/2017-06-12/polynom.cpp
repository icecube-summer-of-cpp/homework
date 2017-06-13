#include "polynom.h"


unsigned long Polynom::order() {
  const auto tmp = this->coeff.size();
  if (tmp <= 1){
    return 0;
  }else{
    return tmp -1;
  }
}

std::ostream& operator<< (std::ostream& stream, const Polynom &rhs) {
  unsigned long lsize = rhs.coeff.size()-1;
  for(unsigned long i = 0; i<=lsize; ++i){
    double tmp = rhs.coeff[lsize-i];
    if(tmp == 0){
      continue;
    }
    if(i!=0 && tmp >0){
      stream << "+";
    }
    stream << rhs.coeff[lsize-i];
    if (lsize-i != 0){
      stream << "x^" << lsize-i;
    }
  }
  return stream;
}

Polynom operator << (Polynom const &lhs, unsigned long shift){
  if(lhs.coeff.size() <= shift){
    return Polynom({});
  }else{
    Polynom tmp({});
    for(unsigned long i =shift; i< lhs.coeff.size(); ++i){
      tmp.coeff.push_back(lhs.coeff[i]);
    }
    return tmp;
  }
};

Polynom operator >> (Polynom const &lhs, unsigned int shift){
  Polynom tmp({});
  for(auto i=0; i< shift; ++i){
    tmp.coeff.push_back(0);
  }
  for(auto i: lhs.coeff){
    tmp.coeff.push_back(i);
  }
  return tmp;
};

Polynom operator*(Polynom const& lhs, double const &rhs) {
  Polynom tmp(lhs);
  for(auto &i : tmp.coeff){
    i *= rhs;
  }
  return tmp;
}

Polynom operator+(Polynom const& lhs, Polynom const& rhs)  {
  unsigned long lsize = lhs.coeff.size();
  unsigned long rsize = rhs.coeff.size();
  
  if(lsize>=rsize){
    Polynom tmp(lhs);
    for(int i=0; i<rsize; ++i){
      tmp.coeff[i] += rhs.coeff[i];
    }
    //remove elements which are 0 at the end
    for(unsigned long i=tmp.coeff.size()-1; i !=0; --i){
      if (tmp.coeff[i] != 0){
        break;
      }
      tmp.coeff.pop_back();
    }
    return tmp;
  }else{
    Polynom tmp(rhs);
    for(int i=0; i<lsize; ++i){
      tmp.coeff[i] += lhs.coeff[i];
    }
    //remove elements which are 0 at the end
    for(unsigned long i=tmp.coeff.size()-1; i !=0; --i){
      if (tmp.coeff[i] != 0){
        break;
      }
      tmp.coeff.pop_back();
    }
    return tmp;
  }
}

Polynom operator+(Polynom const& lhs, double const &rhs)  {
  unsigned long lsize = lhs.coeff.size();
  switch(lsize){
    case 0:
      return Polynom({rhs});
    case 1:
      return Polynom({lhs.coeff[0] + rhs});
    default:
      Polynom tmp(lhs);
      tmp.coeff[0] += rhs;
      return tmp;
  }
}

Polynom operator*(Polynom const& lhs, Polynom const& rhs)  {
  Polynom sum({});
  Polynom tmp(lhs);
  for(const auto i: rhs.coeff){
    sum = sum + (tmp * i);
    tmp = tmp >> 1;
  }
  return sum;
}

Polynom pow(Polynom const& lhs, unsigned long const& rhs)  {
  switch(rhs){
    case 0:
      return Polynom({});
    case 1:
      return lhs;
    default:
      Polynom tmp(lhs);
      for(unsigned long i = 0; i<rhs-1; ++i){
        tmp = tmp * lhs;
      }
      return tmp;
  }
}


double eval(Polynom const& pol, const double& x) {
  unsigned long lsize = pol.coeff.size();
  
  switch (lsize) {
    case 0:
      return 0;
    case 1:
      return pol.coeff[0];
    default:
      double tmp = pol.coeff[0];
      if (x != 0) {
        double x_tmp = x;
        for (int i = 1; i < lsize; ++i) {
          tmp += x_tmp * pol.coeff[i];
          x_tmp *= x;
        }
      }
      return tmp;
  }
}

Polynom eval(Polynom const& pol, Polynom const& x){
  Polynom res = Polynom({});
  Polynom tmp = Polynom({1});
  for(auto i: pol.coeff){
    res = res + (tmp * i);
    tmp = tmp * x;
  }
  return res;
}


