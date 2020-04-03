#ifndef PATHTRACER_H_
#define PATHTRACER_H_

#include <sstream>
#include <iomanip>
#include <cmath>

#include <omp.h>
#include <glm/glm.hpp>

#include "../Camera/camera.h"
#include "../Engine/scene.h"
#include "../Engine/buffer.h"

class PathTracer
{
public:

    PathTracer( Camera &camera,
               const Scene &scene,
               const glm::vec3 background_color,
               Buffer &buffer,
               const size_t num_samples,
               const size_t maximum_depth );

    void integrate( void );

    glm::vec3 radiance( Ray& ray, int curr_depth );

    Ray get_new_ray( IntersectionRecord inter_rec );

private:

    const Camera &camera_;

    const Scene &scene_;

    glm::dvec3 background_color_;

    Buffer &buffer_;

    const size_t num_samples_;

    const size_t maximum_depth_;

};

#endif /* PATHTRACER_H_ */

