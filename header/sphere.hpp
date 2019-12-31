#ifndef SPHEREHPP
#define SPHEREHPP

#include "hittable.hpp"

/******************************************************************************
* SPHERE
* Creates a sphere in the scene.                                        
******************************************************************************/
class sphere: public hittable {
  public:
    // CONSTRUCTORS
    sphere() {}
    sphere(vec3 cen, float r) : center(cen), radius(r) {};
    
    // FUNCTIONS
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
    
    // VARIABLES
    vec3 center;
    float radius;
};

#endif // !SPHEREHPP