#ifndef DIRECTION_H
#define DIRECTION_H

#include <cmath>
#include <iostream>

using namespace std;

class direction{
  public:
    direction():
      zen_(NAN),
      azi_(NAN)
      {}
    direction(double zen, double azi):
      zen_(zen),
      azi_(azi)
      {}

    double GetZen() const {return zen_;}
    double GetAzi() const {return azi_;}
    void SetZen(double zen){
      zen_ = zen;
    }
    void SetAzi(double azi){
      azi_ = azi;
    }

    // I only give the addition and substraction operators
    // as a proof of concent, all other operators should be
    // straightforward but are very time consuming
    direction operator+(const direction&);
    direction operator-(const direction&);

    friend ostream& operator<<(ostream& ,const direction&);
    
  private:
    double zen_;
    double azi_;

};

#endif
