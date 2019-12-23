#include <iostream>
#include <iomanip>
#include <fstream>
#include "../header/vec3.hpp"

int main() {
  // Image resolution
  int nx = 800;
  int ny = 600;

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
  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
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
