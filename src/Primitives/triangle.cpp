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

BoundingBox Triangle::getAABB( void ) const
{
	BoundingBox aabb;

	aabb.min_ = glm::min( glm::min( v1_, v2_ ), v3_ );
	aabb.max_ = glm::max( glm::max( v1_, v2_ ), v3_ );
	aabb.centroid_ = ( 1.0f / 3.0f ) * ( v1_ + v2_ + v2_ );
	return aabb;
}