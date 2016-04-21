
#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <cmath>

#include "Vector2.h"


class Vector3 {
public:
    Vector3();
    Vector3( double x );
    Vector3( double x, double y, double z );
    Vector3( const Vector2& vec );
    Vector3( const Vector3& vec );
    ~Vector3();

    Vector3 operator+( const Vector3& vec ) const;
    Vector3 operator-( const Vector3& vec ) const;
    Vector3 operator*( const double alpha ) const;
    void    operator+=( const Vector3& vec );
    void    operator-=( const Vector3& vec );
    void    operator*=( const double alpha );
    bool    operator==( const Vector3& vec ) const;
    bool    operator!=( const Vector3& vec ) const;

    double  DotProduct( const Vector3& vec ) const;
    Vector3 CrossProduct( const Vector3& vec ) const;

    bool    IsCollinearTo( const Vector3& vec ) const; // untested
    bool    IsNullVector() const; // untested
    double  GetLength() const;
    Vector3 GetNormalizedVector() const;

    double x, y, z;

};


typedef Vector3 Point3_t;

#endif
