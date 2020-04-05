#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/glm.hpp>

#include "../Primitives/primitive.h"
#include "../Engine/intersection_record.h"
#include "../Engine/ray.h"

class Sphere : public Primitive
{
public:

    Sphere( void );

    Sphere( const glm::vec3 &center,
            float radius );

    Sphere( const glm::vec3 &center,
            float radius,
            const glm::vec3 &brdf,
            const glm::vec3 &emittance,
            std::string material );

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    glm::vec3 center_ = { 0.0f, 0.0f, 0.0f };

    float radius_= 1.0f;

    glm::vec3 brdf_ = { 0.0f, 0.0f, 0.0f };
    glm::vec3 emittance_ = { 0.0f, 0.0f, 0.0f };

    std::string material_ = "diffuse";

private:

    static const float kIntersectionTestEpsilon_;
};

#endif /* SPHERE_H_ */

