#include "scene.h"

Scene::Scene( void )
{}

Scene::~Scene( void )
{}

bool Scene::intersect( const Ray &ray,
                       IntersectionRecord &intersection_record ) const
{
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    std::size_t num_primitives = primitives_.size();

    // Loops over the list of primitives, testing the intersection of each primitive against the given ray 
    for ( std::size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++ )
        if ( primitives_[primitive_id]->intersect( ray, tmp_intersection_record ) )
            if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) )
            {
                intersection_record = tmp_intersection_record;
                intersection_result = true; // the ray intersects a primitive!
            }

    return intersection_result;
}

void Scene::load( void ) 
{
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.0f,  0.0f }, 0.2f } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.0f, -1.0f }, 0.2f } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f,-0.5f, -2.0f }, 0.2f } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.5f, -3.0f }, 0.2f } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3 { 0.25f, 0.5f, -1.0f },
                                            glm::vec3 { 0.5f, 0.0f, 0.0f }, glm::vec3 { 0.0f, 0.0f, 0.0f } } ) );
}

void Scene::load(const std::string& filename) {
    Assimp::Importer assimp_importer;
    const aiScene* assimp_scene_ =
        assimp_importer.ReadFile(filename, aiProcess_FindDegenerates | aiProcess_Triangulate);

    if (!assimp_scene_) throw std::runtime_error(assimp_importer.GetErrorString());

    if (assimp_scene_->HasMeshes()) {
        std::unordered_map<std::string, long unsigned int>::const_iterator submeshes_it;

        for (unsigned int mesh_id = 0; mesh_id < assimp_scene_->mNumMeshes; mesh_id++) {
            const aiMesh* mesh_ptr = assimp_scene_->mMeshes[mesh_id];

            for (unsigned int vertex_id = 0; vertex_id < mesh_ptr->mNumVertices; vertex_id += 3) {
                const aiVector3D* vertex_ptr = &mesh_ptr->mVertices[vertex_id];

                glm::vec3 v0(vertex_ptr[0].x, vertex_ptr[0].y, vertex_ptr[0].z);
                glm::vec3 v1(vertex_ptr[1].x, vertex_ptr[1].y, vertex_ptr[1].z);
                glm::vec3 v2(vertex_ptr[2].x, vertex_ptr[2].y, vertex_ptr[2].z);
                
                primitives_.push_back(std::make_unique<Triangle>(v0, v1, v2));
            }
        }
    }
}
