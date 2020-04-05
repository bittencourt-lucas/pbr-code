#include "pathtracer.h"

PathTracer::PathTracer( Camera &camera,
                        const Scene &scene,
                        const glm::vec3 background_color,
                        Buffer &buffer,
                        const size_t num_samples,
                        const size_t maximum_depth ) :
        camera_( camera ),
        scene_( scene ),
        background_color_{ background_color },
        buffer_( buffer ),
        num_samples_( num_samples ),
        maximum_depth_( maximum_depth )
                       
{}

void PathTracer::integrate( void )
{
    IntersectionRecord intersection_record;

    // Image space origin (i.e. x = 0 and y = 0) at the top left corner.

    // Loops over image rows
    #pragma omp parallel for schedule(dynamic, 1) private(intersection_record)
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
            for ( std::size_t i = 0; i < num_samples_; i++) {

                Ray ray{ camera_.getWorldSpaceRay( glm::vec2{  x + static_cast <float> ( rand( ) ) / static_cast <float> ( RAND_MAX ),
                                                            y + static_cast <float> ( rand( ) ) / static_cast <float> ( RAND_MAX ) } ) };
                buffer_.buffer_data_[x][y] += radiance(ray, 0);

            }
            buffer_.buffer_data_[x][y] /= num_samples_;
        }
    }

    std::clog << std::endl;
}

glm::vec3 PathTracer::radiance( Ray& ray, int curr_depth )
{
    IntersectionRecord inter_rec;
    glm::vec3 Lo = { .0f, .0f, .0f };
    Ray refl_ray;

    inter_rec.t_ = std::numeric_limits< double >::max();

    if ( curr_depth < maximum_depth_ )
    {
        if ( scene_.intersect( ray, inter_rec ) )
        {
            if (inter_rec.material_ == "diffuse") {
                refl_ray = get_new_ray_diffuse( inter_rec );

                Lo = inter_rec.emittance_ + 2.0f * (float)M_PI *
                    inter_rec.brdf_ * radiance( refl_ray, ++curr_depth ) *
                    glm::dot(inter_rec.normal_, refl_ray.direction_ );
            }
            else if (inter_rec.material_ == "mirror") {
                refl_ray = get_new_ray_mirror( inter_rec, ray );

                Lo = radiance( refl_ray, ++curr_depth );
            }
        }
    }

    return Lo;
}

Ray PathTracer::get_new_ray_diffuse( IntersectionRecord inter_rec )
{
    float r1 = static_cast <float> ( rand( ) ) / static_cast <float> ( RAND_MAX );
    float r2 = static_cast <float> ( rand( ) ) / static_cast <float> ( RAND_MAX );

    float theta = glm::acos( 1 - r1 );
    float phi = 2 * M_PI * r2;

    ONB onb_;
    onb_.setFromV(inter_rec.normal_);

    glm::vec3 spheric_to_cartesian { glm::cos(phi) * glm::sin(theta), glm::cos(theta), glm::sin(phi) * glm::sin(theta) };

    return Ray { inter_rec.position_ + (inter_rec.normal_ * 0.001f), onb_.getBasisMatrix() * spheric_to_cartesian };
}

Ray PathTracer::get_new_ray_mirror( IntersectionRecord inter_rec, Ray curr_ray )
{
    ONB onb_;
    onb_.setFromV(inter_rec.normal_);

    glm::vec3 reflect = glm::transpose(onb_.getBasisMatrix()) * curr_ray.direction_;

    reflect = { reflect.x, -reflect.y, reflect.z };

    return Ray { inter_rec.position_ + (inter_rec.normal_ * 0.001f), onb_.getBasisMatrix() * reflect };
}