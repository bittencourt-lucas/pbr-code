#ifndef  BOUNDING_BOX_H_
#define  BOUNDING_BOX_H_

#include <iostream>
#include <iomanip>

#include <glm/glm.hpp>

#include "../Engine/ray.h"
#include "../Engine/intersection_record.h"

class BoundingBox
{
  public:

    BoundingBox( void );

    BoundingBox( const glm::dvec3 &min, const glm::dvec3 &max );

    ~BoundingBox( void );

    double getArea( void ) const;

    bool intersect( const Ray &ray ) const;

    BoundingBox operator + ( const BoundingBox &rhs ) const
    {
        return BoundingBox{ glm::min( min_, rhs.min_ ),
                     glm::max( max_, rhs.max_ ) };
    }

    glm::dvec3 min_;

    glm::dvec3 max_;

    glm::dvec3 centroid_;

};

#endif /* BOUNDING_BOX_H_ */