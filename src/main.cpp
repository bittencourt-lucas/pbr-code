#include <iostream>
#include <iomanip>
#include <fstream>
#include "../header/ray.hpp"

// This function uses the equation of the sphere to calculate whether the
// ray hits a hardcoded sphere or not
bool hit_sphere(const vec3& center, float radius, const ray& r) {
  // t^2*dot(B,B) + 2t*dot(B,A-C) + dot(A-C, A-C) - R^2 = 0
  vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = 2.0 * dot(oc, r.direction());
  float c = dot(oc, oc) - radius * radius;
  float discriminant = b * b - 4 * a * c;
  return (discriminant > 0);
}

vec3 color(const ray& r) {
  vec3 unit_direction = unit_vector(r.direction());
  float t = 0.5 * (unit_direction.y() + 1.0);
  // Checks the ray is hitting the sphere
  if (hit_sphere(vec3(0, 0, -1), 0.5, r))
    return vec3(1.0, 0.0, 0.0);
  // Background color with Linear Interpolation
  // blendedValue = (1 - t) * startValue + t * endValue
  return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
  // Image resolution
  int nx = 1600;
  int ny = 800;

  // Save the rendered image to a .ppm file
  std::string path = "/home/lbittencourt/Documentos/Universidade/pbr-code/output/";
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  std::string timestamp = asctime(timeinfo);

  std::clog << "Buffer saving started... ";

  std::ofstream rendering_file;

  rendering_file.open( path + timestamp + ".ppm" );

  rendering_file << "P3\n" << nx << " " << ny << "\n255\n";

  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);

  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {

      float u = float(i) / float(nx);
      float v = float(j) / float(ny);
      ray r(origin, lower_left_corner + u * horizontal + v * vertical);
      vec3 col = color(r);

      int ir = int(255.99 * col[0]);
      int ig = int(255.99 * col[1]);
      int ib = int(255.99 * col[2]);

      rendering_file << ir << " " << ig << " " << ib << "\n";
    }
  }

  rendering_file.close();
  std::clog << "finished!\n";

  return EXIT_SUCCESS;
}
