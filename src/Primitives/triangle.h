#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>

#include "../Primitives/primitive.h"
#include "../Engine/intersection_record.h"
#include "../Engine/ray.h"
#include "../Acceleration/bounding_box.h"

class Triangle : public Primitive
{
public:

    Triangle( void );

    Triangle( const glm::vec3 &v1,
              const glm::vec3 &v2,
              const glm::vec3 &v3 );
              
    Triangle( const glm::vec3 &v1,
              const glm::vec3 &v2,
              const glm::vec3 &v3,
              const glm::vec3 &brdf,
              const glm::vec3 &emittance,
              std::string material );

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    BoundingBox getAABB( void ) const;

    glm::vec3 v1_ = { 0.0f, 0.0f, 0.0f };
    glm::vec3 v2_ = { 0.0f, 0.0f, 0.0f };
    glm::vec3 v3_ = { 0.0f, 0.0f, 0.0f };

    glm::vec3 brdf_ = { 0.0f, 0.0f, 0.0f };
    glm::vec3 emittance_ = { 0.0f, 0.0f, 0.0f };

    std::string material_ = "diffuse";

};

#endif /* TRIANGLE_H_ */

