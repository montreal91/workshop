
#ifndef __RAY_H__
#define __RAY_H__

#include "Vector3.h"

struct Triangle {
    Point3_t vert0;
    Point3_t vert1;
    Point3_t vert2;
};

class Ray {
public:
    Ray();
    Ray( const Point3_t& origin, const Vector3& direction );
    Ray( const Ray& ray );
    ~Ray();

    Point3_t    GetOrigin() const;
    Vector3     GetDirection() const;
    int         GetIntersectionWithTriangle( const Triangle& tris, Point3_t* intersection ) const;

    static const int    FAIL;
    static const int    SUCCESS;
    static const double EPSILON;

private:
    bool        IsNotBaricentric( const double var ) const;

    Point3_t    origin;
    Vector3     direction;
};

#endif
