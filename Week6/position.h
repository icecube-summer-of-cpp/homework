#ifndef POSITION_H
#define POSITION_H

#include <cmath>

class position{
  public:
    position():
      x_(NAN),
      y_(NAN),
      z_(NAN)
      {}
    position(double x, double y, double z): 
      x_(x),
      y_(y),
      z_(z)
      {}

    double GetX() const {return x_;}
    double GetY() const {return y_;}
    double GetZ() const {return z_;}
    void SetX(double x){
      x_ = x;
    }
    void SetY(double y){
      y_ = y;
    }
    void SetZ(double z){
      z_ = z;
    }

    // I only give the addition and substraction operators
    // as a proof of concent, all other operators should be
    // straightforward but are very time consuming
    position operator+(const position&);
    position operator-(const position&);

  private:
    double x_;
    double y_;
    double z_;
};

#endif
