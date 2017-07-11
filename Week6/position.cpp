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
