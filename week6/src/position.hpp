#ifndef POSITION
#define POSITION

#include <iostream>

class position{
    public:
        position(): x_(0), y_(0), z_(0) {};
       
        float get_x(){ return x_; }
        float get_y(){ return y_; }
        float get_z(){ return z_; }
       
        bool operator==(const postition& rhs) const {
            return (x_ == rhs.get_x()) && (y_ == rhs.get_y()) && (z_ == rhs.get_z());
        };
       
        bool operator!=(const position& rhs) const { return !(*this == rhs); }
 
    private:
        float x_;
        float y_;
        float z_;
};

#endif
