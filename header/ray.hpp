#ifndef RAYHPP
#define RAYHPP
#include "vec3.hpp"

/******************************************************************************
* RAY
* The ray is a function p(t) = A + t * B, where p is a 3D position along a
* line in 3D, A is the ray origin, B is the ray direction, and t is a real
* number. p(t) moves a point along the ray.                                           
******************************************************************************/
class ray {
  public:
    // CONSTRUCTORS
    ray() {}
    ray(const vec3& a, const vec3& b) { A = a; B = b; }
    
    // FUNCTIONS
    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    vec3 point_at_parameter(float t) const { return A + t * B; }

    // VARIABLES
    vec3 A;
    vec3 B;
};

#endif // !RAYHPP