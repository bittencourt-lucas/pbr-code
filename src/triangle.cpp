#include "../header/triangle.hpp"

bool triangle::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  const float EPSILON = 1e-6f;

  vec3 edge1, edge2, tvec, pvec, qvec;
  float det, inv_det;

  // Find vectors for two edges sharing vertex
  edge1 = vertex1 - vertex0;
  edge2 = vertex2 - vertex0;
  
  // Begin calculating determinant - also used to calculate U parameter
  pvec = cross(r.direction(), edge2);

  // If determinant is near zero, ray lies in plane of triangle
  det = dot(edge1, pvec);

  // Culling branch
  #ifdef CULL_TEST
    if (det < EPSILON) return false;

    // Distance from the ray origin() to vert0
    tvec = r.origin() - vertex0;

    // Calculates U parameter and test bounds
    float u = dot(tvec, pvec);
    if (u < 0.0 || u > det)
      return false;

    // Prepares to test V parameter
    qvec = cross(tvec, edge1);

    // Calculates V parameter and tests bounds
    float v = dot(r.direction(), qvec);
    if (v < 0.0 || u + v > det)
      return false;

    // Calculates T, scale parameters, ray intersects triangle
    float t = dot(edge2, qvec);
    inv_det = 1.0 / det;
    t *= inv_det;

  // Non-Culling Branch
  #else
    if (det > -EPSILON && det < EPSILON) return false;

    inv_det = 1.0 / det;

    // Calculate distance from vert0 to ray origin()
    tvec = r.origin() - vertex0;

    // Calculate U parameter and test bounds
    float u = dot(tvec, pvec) * inv_det;
    if (u < 0.0 || u > 1.0) return false;

    // Prepare to test V parameter
    qvec = cross(tvec, edge1);

    // Calculate V parameter and test bounds
    float v = dot(r.direction(), qvec) * inv_det;
    if (v < 0.0 || (u + v) > 1.0) return false;

    // Calculate t, ray intersects triangle
    float t = dot(edge2, qvec) * inv_det;
  #endif
  
  rec.t = t;
  rec.p = r.point_at_parameter(rec.t);
  rec.normal = cross(edge1, edge2);
  return true;
}

// bool triangle::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
//   float a = vertex0.x() - vertex1.x();
//   float b = vertex0.y() - vertex1.y();
//   float c = vertex0.z() - vertex1.z();
//   float d = vertex0.x() - vertex2.x();
//   float e = vertex0.y() - vertex2.y();
//   float f = vertex0.z() - vertex2.z();
//   float g = r.direction().x();
//   float h = r.direction().y();
//   float i = r.direction().z();
//   float j = vertex0.x() - r.origin().x();
//   float k = vertex0.y() - r.origin().y();
//   float l = vertex0.z() - r.origin().z();

//   float ei_minus_hf = float(e * i - h * f);
//   float gf_minus_di = float(g * f - d * i);
//   float dh_minus_eg = float(d * h - e * g);
//   float ak_minus_jb = float(a * k - j * b);
//   float jc_minus_al = float(j * c - a * l);
//   float bl_minus_kc = float(b * l - k * c);


//   float M = a * (ei_minus_hf) + b * (gf_minus_di) + c * (dh_minus_eg);

//   float t = -(f * (ak_minus_jb) + e * (jc_minus_al) + d * (bl_minus_kc)) / M;

//   if (t < 0.0) return false;

//   float gamma = (i * (ak_minus_jb) + h * (jc_minus_al) + g * (bl_minus_kc)) / M;

//   if (gamma < 0.0 || gamma > 1.0) return false;

//   float beta = (j * (ei_minus_hf) + k * (gf_minus_di) + l * (dh_minus_eg)) / M;

//   if (beta < 0.0 || beta > 1.0 - gamma) return false;

//   rec.t = t;
//   rec.p = r.point_at_parameter(rec.t);
//   rec.normal = rec.p;
//   if (dot(rec.normal, r.direction()) > 0) rec.normal = -rec.normal;
  
//   return true;
// }