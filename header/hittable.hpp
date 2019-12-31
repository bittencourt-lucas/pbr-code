#ifndef HITTABLEHPP
#define HITTABLEHPP

#include "ray.hpp"

// Data gathered by the hittable class
struct hit_record {
  float t;
  vec3 p;
  vec3 normal;
};

/******************************************************************************
* HITTABLE
* Abstract class that has a hit function, which will determine whether the ray
* hit something along the way.                                         
******************************************************************************/
class hittable {
  public:
    virtual bool hit(
      const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif // !HITTABLEHPP