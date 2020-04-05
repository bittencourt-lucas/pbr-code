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
#include "../Acceleration/bvh.h"

class Scene
{
public:

    Scene( void );

    ~Scene( void );

    void buildAccelerationStructure( void );

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    bool acceleratedIntersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    void load( void );

    void load( const std::string&, glm::vec3, glm::vec3, std::string );

    std::vector< Primitive::PrimitiveUniquePtr > primitives_;

    enum AccelerationStructure
    {
        NONE,
        BVH_ACCELERATION
    };

    AccelerationStructure acceleration_structure_ = AccelerationStructure::NONE;

private:

    void buildBVH( void );

    const BVH *bvh_ = nullptr;

};

#endif /* SCENE_H_ */

