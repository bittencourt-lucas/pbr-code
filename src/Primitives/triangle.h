#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>
#include "../Primitives/primitive.h"
#include "../Engine/intersection_record.h"
#include "../Engine/ray.h"

class Triangle : public Primitive
{
public:

    Triangle( void );

    Triangle( const glm::vec3 &v1,
              const glm::vec3 &v2,
              const glm::vec3 &v3 );

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    glm::vec3 v1_ = { 0.0f, 0.0f, 0.0f };
    glm::vec3 v2_ = { 0.0f, 0.0f, 0.0f };
    glm::vec3 v3_ = { 0.0f, 0.0f, 0.0f };

};

#endif /* TRIANGLE_H_ */

