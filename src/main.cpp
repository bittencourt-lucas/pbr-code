#include <iostream>
#include <iomanip>
#include <fstream>
#include "../header/vec3.hpp"
#include "../header/ray.hpp"
#include "../header/sphere.hpp"
#include "../header/triangle.hpp"
#include "../header/hittable.hpp"
#include "../header/hittable_list.hpp"

vec3 color(const ray& r, hittable *world) {
  hit_record rec;
  if (world->hit(r, 0.0, MAXFLOAT, rec)) {
    return 0.5 * vec3(rec.normal.x() + 1,
                      rec.normal.y() + 1,
                      rec.normal.z() + 1);
  } else {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    // Background color with Linear Interpolation
    // blendedValue = (1 - t) * startValue + t * endValue
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

int main() {
  // Image resolution
  int nx = 800;
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
  vec3 horizontal(3.0, 0.0, 0.0);
  vec3 vertical(0.0, 3.0, 0.0);
  vec3 origin(1.0, 0.0, 1.0);

  int n = 3;
  hittable *list[n];
  list[0] = new sphere(vec3(0,0,-1), 0.5);
  list[1] = new triangle(vec3(0.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));
  list[2] = new sphere(vec3(0,-100.5,-1), 100);
  hittable *world = new hittable_list(list, n);

  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {

      float u = float(i) / float(nx);
      float v = float(j) / float(ny);
      ray r(origin, lower_left_corner + u * horizontal + v * vertical);

      vec3 p = r.point_at_parameter(2.0);
      vec3 col = color(r, world);

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
