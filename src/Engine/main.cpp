#include "main.h"

int main( void )
{
    unsigned int x_resolution = 512;
    unsigned int y_resolution = 512;

    PinholeCamera camera{   -1.25f, 
                            1.25f, 
                            -1.25f, 
                            1.25f,
                            5.0f,
                            glm::ivec2{ x_resolution, y_resolution }, 
                            glm::vec3{ 7.3589f, 6.9258f,  4.9583f },     // position
                            glm::vec3{ 0.0f, 1.0f,  0.0f },     // up
                            glm::vec3{ 0.636f, 0.0f, 0.467f } };   // look at
    Scene scene{};
    
    // scene.load();
    scene.load("/home/lbittencourt/Documentos/Universidade/pbr-code/assets/room.obj", glm::vec3 { 0.725f, 0.71f, 0.68f }, glm::vec3 { .0f }, "diffuse");
    scene.load("/home/lbittencourt/Documentos/Universidade/pbr-code/assets/light.obj", glm::vec3 { 0.725f, 0.71f, 0.68f }, glm::vec3 { 50.0f }, "diffuse");
    //scene.load("/home/lbittencourt/Documentos/Universidade/pbr-code/assets/suzanne.obj", glm::vec3 { 0.14f, 0.45f, 0.091f }, glm::vec3 { .0f }, "diffuse");
    //scene.load("/home/lbittencourt/Documentos/Universidade/pbr-code/assets/seahorse.obj", glm::vec3 { 0.63f, 0.065f, 0.05f }, glm::vec3 { .0f }, "diffuse");
    scene.load("/home/lbittencourt/Documentos/Universidade/pbr-code/assets/mirror.obj", glm::vec3 { 1.0f }, glm::vec3 { .0f }, "mirror");

    Buffer rendering_buffer{ x_resolution, y_resolution };
    glm::vec3 background_color{ 0.0f, 0.0f, 0.0f };

    // // Set up the renderer.
    // RayTracer rt( camera,
    //               scene,
    //               background_color,
    //               rendering_buffer,
    //               5 );

    // rt.integrate(); // Renders the final image.

    // Set up the renderer.
    PathTracer pt( camera,
                   scene,
                   background_color,
                   rendering_buffer,
                   (size_t)500,
                   (size_t)3 );

    pt.integrate(); // Renders the final image.

    // Save the rendered image to a .ppm file.
    std::string path = "/home/lbittencourt/Documentos/Universidade/pbr-code/outputs/";
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    std::string timestamp = asctime(timeinfo);
    timestamp.pop_back();
    rendering_buffer.save( path + timestamp + ".ppm" );

    return EXIT_SUCCESS;
}

