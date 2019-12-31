#ifndef TRIANGLEHPP
#define TRIANGLEHPP

#include "hittable.hpp"

/******************************************************************************
* TRIANGLE
* Creates a triangle in the scene.                                        
******************************************************************************/
class triangle: public hittable {
  public:
    // CONSTRUCTORS
    triangle() {}
    triangle(vec3 vert0, vec3 vert1, vec3 vert2):
             vertex0(vert0), vertex1(vert1), vertex2(vert2) {};
    
    // FUNCTIONS
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
    
    // VARIABLES
    vec3 vertex0;
    vec3 vertex1;
    vec3 vertex2;
};

#endif // !TRIANGLEHPP