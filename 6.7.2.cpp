//
// Created by Frederik Lauber on 04.07.17.
//

#include <cassert>
#include <iostream>


//this is totally uter stupid
//wasting so much space for the ones class but data
//needs to be here or we cannot define the [] operator
class vector_expression{
protected:
    int     my_size;
    double* data;
public:
    vector_expression(int size) : my_size(size), data(new double[size]) {}
    
    vector_expression() : my_size(0), data(0) {}
    
    virtual ~vector_expression() { delete[] data; }
    
    int size() const { return my_size; }
    int size() { return my_size; }
    
    double& operator[](const unsigned int i) {
      assert(i<my_size);
      return data[i];
    }
    
    void operator=(const vector_expression& that)
    {
      assert(that.my_size == my_size);
      for (int i=0; i<my_size; ++i)
        data[i] = that[i];
    }
    
    vector_expression operator+(const vector_expression& that) const {
      assert(that.size() == my_size);
      vector_expression sum(my_size);
      for (int i= 0; i < my_size; ++i)
        sum[i] = (*this)[i] + that[i];
      return sum;
    }
};

//this will start out with all ones but if we wan tto have a &ed [] operator the user may change it later...
class ones : public  vector_expression{
    using vector_expression::vector_expression;
    ones(int size) : vector_expression(size) {
      for(int i=0; i<size; ++i){
        data[i] = 1;
      }
    }
};



class vector : public vector_expression
{
public:
    using vector_expression::vector_expression;
    
    vector(const vector& that)
            :vector_expression(that.size())
    {
      for (int i=0; i<my_size; ++i) { data[i] = that.data[i]; }
    }
    

};

std::ostream& operator<<(std::ostream& os, const vector& v)
{
  os << '[';
  for (int i= 0; i < v.size(); ++i) os << v[i] << ',';
  os << ']';
  return os;
}

double dot(const vector& v, const vector& w)
{
  double s;
  for (int i= 0; i < v.size(); i++)
    s+= v[i] * w[i];
  return s;
}

int main() {
  vector v(4);
  v[0] = v[1] = 1.0; v[2] = 2.0; v[3] = -3.0;
  std::cout << v << std::endl;
  
  vector w(v.size());
  w = v;
  
  const vector z(w);
  std::cout << "z[3] is " << z[3] << '\n';
  
  std::cout << "w is " << w << '\n';
  v[1]= 9.;
  std::cout << "w is " << w << '\n';
  
  
  vector sum(w + v);
  
  return 0;
}