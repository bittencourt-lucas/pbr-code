#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include <memory>

#include "../Engine/ray.h"
#include "../Engine/intersection_record.h"
#include "../Acceleration/bounding_box.h"

class Primitive
{
public:

    typedef std::unique_ptr< Primitive > PrimitiveUniquePtr;

    Primitive( void );

    virtual ~Primitive( void );

    virtual bool intersect( const Ray &ray,
                            IntersectionRecord &intersection_record ) const = 0;

    virtual BoundingBox getAABB( void ) const = 0;
};

#endif /* PRIMITIVE_H_ */

