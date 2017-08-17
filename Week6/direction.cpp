#include "direction.h"

direction direction::operator+(const direction& d){
  zen_ += d.GetZen();
  azi_ += d.GetAzi();
  return *this;
}

direction direction::operator-(const direction& d){
  zen_ += d.GetZen();
  azi_ += d.GetAzi();
  return *this;
}

ostream& operator<<(ostream& os, const direction& d)
{
  os << "zenith: " << d.GetZen() << ", azimuth: " << d.GetAzi() << endl;
  return os;
}
