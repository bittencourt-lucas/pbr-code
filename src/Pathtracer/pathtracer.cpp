#include "pathtracer.h"

PathTracer::PathTracer( Camera &camera,
                        const Scene &scene,
                        const glm::vec3 background_color,
                        Buffer &buffer) :
        camera_( camera ),
        scene_( scene ),
        background_color_{ background_color },
        buffer_( buffer )
                       
{}

void PathTracer::integrate( void ) {}