#include "triangle.h"

#define EPSILON 0.000001

Triangle::Triangle( void )
{}

Triangle::Triangle( const glm::vec3 &v1,
                    const glm::vec3 &v2,
                    const glm::vec3 &v3 ) :
        v1_{ v1 },
        v2_{ v2 },
        v3_{ v3 }
{}

bool Triangle::intersect( const Ray &ray,
                        IntersectionRecord &intersection_record ) const
{
    /**********************************************************************************************
    * Ray-Triangle intersection using the algorithm from Fast, Minimum Storage
    * Ray/Triangle Intersection by Tomas Möller and Ben Trumbore.
    * Avaliable at: https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
    **********************************************************************************************/

    glm::vec3 edge1, edge2, tvec, pvec, qvec;
    float det, inv_det;

    // Find vectors for two edges sharing v1
    edge1 = v2_ - v1_;
    edge2 = v3_ - v2_;

    // Begin calculating the determinant
    pvec = glm::cross(ray.direction_, edge2);

    // If determinant is near zero, ray lies plane of triangle
    det = glm::dot(edge1, pvec);

    // Culling branch
    #ifdef CULL_TEST
        if (det < EPSILON)
            return false;

        // Distance from the ray origin to v1
        tvec = ray.origin_ - v1_;

        // Calculates U parameter and test bounds
        float u = glm::dot(tvec, pvec);
        if (u < 0.0f || u > det)
            return false;

        // Prepares to test V parameter
        qvec = glm::cross(tvec, edge1);

        // Calculates V parameter and tests bounds
        float v = glm::dot(ray.direction_, qvec);
        if (v < 0.0 || u + v > det)
            return false;

        // Calculates T, scale parameters, ray intersects triangle
        float t = glm::dot(edge2, qvec);
        inv_det = 1.0f / det;
        t *= inv_det;

    // Non-Culling Branch
    #else
        if (det > -EPSILON && det < EPSILON)
            return false;
        inv_det = 1.0f / det;

        // Calculates distance from v1 to ray origin
        tvec = ray.origin_ - v1_;

        // Calculates U parameter and tests bounds
        float u = glm::dot(tvec, pvec) * inv_det;
        if (u < 0.0f || u > 1.0f)
            return false;

        // Prepares to test V parameter
        qvec = glm::cross(tvec, edge1);

        // Calculates V parameter and test bounds
        float v = glm::dot(ray.direction_, qvec) * inv_det;
        if (v < 0.0f || (u + v) > 1.0f)
            return false;

        // Calculates T
        float t = glm::dot(edge2, qvec) * inv_det;
    #endif

    intersection_record.t_ = t;
    intersection_record.position_ = ray.origin_ + ray.direction_ * intersection_record.t_;
    intersection_record.normal_ = glm::normalize( glm::cross( v2_ - v1_, v3_ - v1_ ) );

    return true;
}

