#ifndef SCENE_H_
#define SCENE_H_

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <unordered_map>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include "../Primitives/primitive.h"
#include "../Primitives/sphere.h"
#include "../Primitives/triangle.h"

class Scene
{
public:

    Scene( void );

    ~Scene( void );

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    void load( void );

    void load( const std::string&, glm::vec3, glm::vec3, std::string );

    std::vector< Primitive::PrimitiveUniquePtr > primitives_;

};

#endif /* SCENE_H_ */

