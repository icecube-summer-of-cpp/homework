#include <iostream>
#include <vector>
#include <random>
#include <assert.h>
#include <map>
#include <memory>
#include <cstring>


typedef std::array<unsigned char, 16> uuid_t;
class unique_id{
    static std::map<uuid_t, std::weak_ptr<char> > uuidobjmap;
protected:
    std::shared_ptr<char> id;
public:
    unique_id(){
      id = std::make_shared<char>('a');
    }
    unique_id(uuid_t uuid){//needed if we want to implement serialisation
      if (uuidobjmap.find(uuid) == uuidobjmap.end() ) {
            id = std::make_shared<char>('a');
            uuidobjmap[uuid] = id;
      } else {
        auto tmp = uuidobjmap[uuid];
        if (auto spt = tmp.lock()){
          id = spt;
        } else {
          id = std::make_shared<char>('a');
          uuidobjmap[uuid] = id;
        }
      }
    }
    
    uuid_t serialize(){
      uuid_t uuid;
      for(unsigned  int i=0; i<16; ++i){
        uuid[i] = (unsigned char) rand(); //yeah yeah, c style cast but i actually only want one byte here
      }
      uuidobjmap[uuid] = id;
      return uuid;
    }
    
    ~unique_id() = default;
    unique_id& operator=(unique_id&& src) = default;
    unique_id(unique_id&& v) = default;
    unique_id(const unique_id& c) = default;
    unique_id& operator=(const unique_id& src) = default;
    
    bool operator==(const unique_id& rhs) const {
        return this->id.get() ==  rhs.id.get();
    };
    
    bool operator!=(const unique_id& rhs) const {
        return this->id.get() !=  rhs.id.get();
    }
};

std::map<uuid_t, std::weak_ptr<char> > unique_id::uuidobjmap;

struct linalgvec4 {
    double x;
    double y;
    double z;
    double t;
    
    
    linalgvec4 operator+ (const linalgvec4& rhs){
      auto tmp = linalgvec4(*this);
      tmp.x += rhs.x;
      tmp.y += rhs.y;
      tmp.z += rhs.z;
      return tmp;
    }
    
    linalgvec4 operator- (const linalgvec4& rhs){
      auto tmp = linalgvec4(*this);
      tmp.x -= rhs.x;
      tmp.y -= rhs.y;
      tmp.z -= rhs.z;
      return tmp;
    }
    
    linalgvec4 operator* (const double rhs){
      auto tmp = linalgvec4(*this);
      tmp.x *= rhs;
      tmp.y *= rhs;
      tmp.z *= rhs;
      return tmp;
    }
    
    bool operator== (const linalgvec4& rhs){
      return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && this->t == rhs.t;
    }

};

class position : public linalgvec4 {};
class direction : public linalgvec4 {};

//class for objects that have a position and a direction
//implement all manipulation (like moving down the track or rotation from it) here
struct movingObj{
    position pos;
    direction dir;
    
    bool operator== (const movingObj& rhs){
      return this->pos == rhs.pos && this->dir == rhs.dir;
    }
    
    void moveby(double time){
      this->pos.x = this->pos.x + this->dir.x * time;
      this->pos.y = this->pos.y + this->dir.y * time;
      this->pos.z = this->pos.z + this->dir.z * time;
      this->pos.t = this->pos.t + time;
      
    }
};

struct particle : virtual public unique_id , public movingObj{
    double energy;
    unsigned int ptype;
    particle(double energy=0, unsigned  int ptype = 0, position pos=position(), direction dir=direction(), unique_id id=unique_id()){
      static_cast<unique_id>(*this) = id;
      this->ptype = ptype;
      this->pos = pos;
      this->dir = dir;
      this->energy = energy;
    }
};

struct sim_info{
    unsigned int id;
    unsigned int subid;
    double weight;
};


enum reconstructions{
    foo,
    bar,
};

//baseclass for reconstruction results
class reconstruction_result{
    double quality;
};

struct reco_info{
    enum reconstructions reconstruction;
    std::shared_ptr<reconstruction_result> reco_result;
};

class sim_particle : public particle{
    sim_info info;
    std::shared_ptr<particle> parent;
};


class reco_particle : public particle{
    double reconstruction_quality;
};


int main(){
  auto a = unique_id();
  auto b = unique_id();
  auto tmp = a.serialize();
  auto c = unique_id(tmp);
  assert(a==a);
  assert(a!=b);
  assert(a==c);
  auto p1 = particle();
  auto p2 = particle();
  assert(p1!=p2);
  return 0;
}
