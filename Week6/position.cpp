#include "position.h"

position position::operator+(const position& p){
  x_+= p.GetX();
  y_+= p.GetY();
  z_+= p.GetZ();
  return *this;
}

position position::operator-(const position& p){
  x_-= p.GetX();
  y_-= p.GetY();
  z_-= p.GetZ();
  return *this;
}

ostream& operator<<(ostream& os,const position& p)
{
  os << "x: " << p.GetX() << ", y: " << p.GetY() << ", z: " << p.GetZ();
  os << endl;
  return os;

}

