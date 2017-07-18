#ifndef DIRECTION
#define DIRECTION

#include <iostream>

/* constructor, assignment, move, destructor, comparison, getter, setters, tests, comments, printing, functionallity
 * 
 * DIRECTION            
 * ---------
 * + zenith  
 * + azimuth
 * - setter
 * - getter
 * - getter other formats
 * - setter other formats
 * * addition
 * * substraction
 * 
 */

class direction{
    public:
        direction(): azi_(0), zen_(0) {};
       
        float get_zenith(){ return zen_; }
        float get_azimuth(){ return azi_; }
       
        bool operator==(const direction& rhs) const {
            return (azi_ == rhs.get_azimuth()) && (zen_ == rhs.get_zenith());
        };
       
        bool operator!=(const direction& rhs) const { return !(*this == rhs); }
 
    private:
        float azi_;
        float zen_;
};

#endif
