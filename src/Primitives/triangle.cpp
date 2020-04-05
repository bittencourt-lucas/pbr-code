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

Triangle::Triangle( const glm::vec3 &v1,
                    const glm::vec3 &v2,
                    const glm::vec3 &v3,
                    const glm::vec3 &brdf,
                    const glm::vec3 &emittance,
                    std::string material ) :
        v1_{ v1 },
        v2_{ v2 },
        v3_{ v3 },
        brdf_{ brdf },
        emittance_{ emittance },
        material_{ material }
{}

bool Triangle::intersect( const Ray &ray,
                        IntersectionRecord &inter_rec ) const
{
    float beta, gamma, t, M;
    float a, b, c, d, e, f, g, h, i, j, k, l;
    float ei_minus_hf, gf_minus_di, dh_minus_eg;
    float ak_minus_jb, jc_minus_al, bl_minus_kc;

    a = v1_.x - v2_.x;
    b = v1_.y - v2_.y;
    c = v1_.z - v2_.z;

    d = v1_.x - v3_.x;
    e = v1_.y - v3_.y;
    f = v1_.z - v3_.z;

    g = ray.direction_.x;
    h = ray.direction_.y;
    i = ray.direction_.z;

    j = v1_.x - ray.origin_.x;
    k = v1_.y - ray.origin_.y;
    l = v1_.z - ray.origin_.z;

    ei_minus_hf = (e * i) - (h * f);
    gf_minus_di = (g * f) - (d * i);
    dh_minus_eg = (d * h) - (e * g);

    ak_minus_jb = (a * k) - (j * b);
    jc_minus_al = (j * c) - (a * l);
    bl_minus_kc = (b * l) - (k * c);

    M = a * (ei_minus_hf) + b * (gf_minus_di) + c * (dh_minus_eg);

    t = -(f * (ak_minus_jb) + e * (jc_minus_al) + d * (bl_minus_kc)) / M;

    if (t < 0.0f)
        return false;

    gamma = (i * (ak_minus_jb) + h * (jc_minus_al) + g * (bl_minus_kc)) / M;

    if (gamma < 0.0f || gamma > 1.0f)
        return false;

    beta = (j * (ei_minus_hf) + k * (gf_minus_di) + l * (dh_minus_eg)) / M;

    if (beta < 0.0f || beta > (1.0f - gamma))
        return false;

    inter_rec.t_ = t;
    inter_rec.position_ = ray.origin_ + (t * ray.direction_);
    inter_rec.normal_ = glm::normalize(glm::cross(v2_ - v1_, v3_ - v1_));
    inter_rec.brdf_ = brdf_ / ((float) M_PI);
    inter_rec.emittance_ = emittance_;
    inter_rec.material_ = material_;

    if (glm::dot(inter_rec.normal_, ray.direction_) > 0.0f)
        inter_rec.normal_ = -inter_rec.normal_;
    
    return true;
}

// bool Triangle::intersect( const Ray &ray,
//                         IntersectionRecord &intersection_record ) const
// {
//     /**********************************************************************************************
//     * Ray-Triangle intersection using the algorithm from Fast, Minimum Storage
//     * Ray/Triangle Intersection by Tomas Möller and Ben Trumbore.
//     * Avaliable at: https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
//     **********************************************************************************************/

//     glm::vec3 edge1, edge2, tvec, pvec, qvec;
//     float det, inv_det;

//     // Find vectors for two edges sharing v1
//     edge1 = v2_ - v1_;
//     edge2 = v3_ - v2_;

//     // Begin calculating the determinant
//     pvec = glm::cross(ray.direction_, edge2);

//     // If determinant is near zero, ray lies plane of triangle
//     det = glm::dot(edge1, pvec);

//     // Culling branch
//     #ifdef CULL_TEST
//         if (det < EPSILON)
//             return false;

//         // Distance from the ray origin to v1
//         tvec = ray.origin_ - v1_;

//         // Calculates U parameter and test bounds
//         float u = glm::dot(tvec, pvec);
//         if (u < 0.0f || u > det)
//             return false;

//         // Prepares to test V parameter
//         qvec = glm::cross(tvec, edge1);

//         // Calculates V parameter and tests bounds
//         float v = glm::dot(ray.direction_, qvec);
//         if (v < 0.0 || u + v > det)
//             return false;

//         // Calculates T, scale parameters, ray intersects triangle
//         float t = glm::dot(edge2, qvec);
//         inv_det = 1.0f / det;
//         t *= inv_det;

//     // Non-Culling Branch
//     #else
//         if (det > -EPSILON && det < EPSILON)
//             return false;
//         inv_det = 1.0f / det;

//         // Calculates distance from v1 to ray origin
//         tvec = ray.origin_ - v1_;

//         // Calculates U parameter and tests bounds
//         float u = glm::dot(tvec, pvec) * inv_det;
//         if (u < 0.0f || u > 1.0f)
//             return false;

//         // Prepares to test V parameter
//         qvec = glm::cross(tvec, edge1);

//         // Calculates V parameter and test bounds
//         float v = glm::dot(ray.direction_, qvec) * inv_det;
//         if (v < 0.0f || (u + v) > 1.0f)
//             return false;

//         // Calculates T
//         float t = glm::dot(edge2, qvec) * inv_det;
//     #endif

//     intersection_record.t_ = t;
//     intersection_record.position_ = ray.origin_ + ray.direction_ * intersection_record.t_;
//     intersection_record.normal_ = glm::normalize( glm::cross( v2_ - v1_, v3_ - v1_ ) );

//     return true;
// }

