
#include "Ray.h"
#include <iostream>


const int       Ray::FAIL       = 0;
const int       Ray::SUCCESS    = 1;
const double    Ray::EPSILON    = 0.000001;


Ray::Ray() {
    this->origin    = Point3_t();
    this->direction = Vector3( 1, 0, 0 );
}

Ray::Ray( const Point3_t& origin, const Vector3& direction ) {
    this->origin    = origin;
    this->direction = direction.GetNormalizedVector();
}

Ray::Ray( const Ray& ray ) {
    this->origin    = ray.origin;
    this->direction = ray.direction;
}

Ray::~Ray() {
}

Point3_t
Ray::GetOrigin() const {
    return this->origin;
}

Vector3
Ray::GetDirection() const {
    return this->direction;
}

int
Ray::GetIntersectionWithTriangle( const Triangle& tris, Point3_t* intersection ) const {
    Vector3 edge1   = tris.vert1 - tris.vert0;
    Vector3 edge2   = tris.vert2 - tris.vert0;

    Vector3 pvec    = this->direction.CrossProduct( edge2 );

    double det      = pvec.DotProduct( edge1 );

    if ( det > -EPSILON && det < EPSILON ) return FAIL;

    double inv_det  = 1.0 / det;
    Vector3 tvec    = this->origin - tris.vert0;
    double u        = tvec.DotProduct( pvec ) * inv_det;
    if ( this->IsNotBaricentric( u ) ) return FAIL;

    Vector3 qvec    = tvec.CrossProduct( edge1 );
    double v        = this->direction.DotProduct( qvec ) * inv_det;
    if ( this->IsNotBaricentric( v ) ) return FAIL;

    double t        = edge2.DotProduct( qvec ) * inv_det;

    intersection->x = this->origin.x + this->direction.x * t;
    intersection->y = this->origin.y + this->direction.y * t;
    intersection->z = this->origin.z + this->direction.z * t;

    return SUCCESS;
}

bool
Ray::IsNotBaricentric( const double var ) const {
    return var < 0.0 || var > 1.0;
}
