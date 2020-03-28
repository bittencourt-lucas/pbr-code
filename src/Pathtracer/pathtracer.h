#ifndef PATHTRACER_H_
#define PATHTRACER_H_

#include <sstream>
#include <iomanip>
#include <cmath>

#include "../Camera/camera.h"
#include "../Engine/scene.h"
#include "../Engine/buffer.h"

class PathTracer
{
public:

    PathTracer( Camera &camera,
               const Scene &scene,
               const glm::vec3 background_color,
               Buffer &buffer );

    void integrate( void );

private:

    const Camera &camera_;

    const Scene &scene_;

    glm::dvec3 background_color_;

    Buffer &buffer_;

};

#endif /* PATHTRACER_H_ */

