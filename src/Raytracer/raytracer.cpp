#include "raytracer.h"

RayTracer::RayTracer( Camera &camera,
                      const Scene &scene,
                      const glm::vec3 background_color,
                      Buffer &buffer,
                      int samples ) :
        camera_( camera ),
        scene_( scene ),
        background_color_{ background_color },
        buffer_( buffer ),
        samples_( samples )
{}

void RayTracer::integrate( void )
{
    IntersectionRecord intersection_record;

    // Image space origin (i.e. x = 0 and y = 0) at the top left corner.

    // Loops over image rows
    for ( std::size_t y = 0; y < buffer_.v_resolution_; y++ )
    {
        std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw( 6 )
                        << std::setprecision( 2 )
                        << 100.0 * y / ( buffer_.v_resolution_ - 1 )
                        << "%";

        std::clog << progress_stream.str();

        // Loops over image columns
        for ( std::size_t x = 0; x < buffer_.h_resolution_; x++ )
        {
            intersection_record.t_ = std::numeric_limits< double >::max();
            glm::vec3 antialiasing(.0f, .0f,.0f);

            for ( std::size_t i = 0; i < samples_; i++) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0, 1);//uniform distribution between 0 and 1

                Ray ray{ camera_.getWorldSpaceRay( glm::vec2{ x + dis(gen), y + dis(gen) } ) };

                if ( scene_.intersect( ray, intersection_record ) ) {
                    //buffer_.buffer_data_[x][y] = glm::vec3{ 1.0f, 0.0f, 0.0f };
                    glm::vec3 N{ glm::normalize((ray.origin_ + intersection_record.t_ * ray.direction_) - glm::vec3{ 0.0f, 0.0f, -1.0f }) };
                    antialiasing = antialiasing + intersection_record.t_ + N;
                }
            }
            buffer_.buffer_data_[x][y] = glm::vec3{ antialiasing.x / samples_, antialiasing.y / samples_, antialiasing.z / samples_ };
        }
    }

    std::clog << std::endl;
}

