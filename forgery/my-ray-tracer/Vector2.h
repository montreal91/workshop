
#ifndef __VECTOR2_H__
#define __VECTOR2_H__


class Vector2 {
public:
    Vector2();
    Vector2( double x );
    Vector2( double x, double y );
    Vector2( const Vector2& vec );
    ~Vector2();

    Vector2 operator+( const Vector2& vec ) const;
    Vector2 operator-( const Vector2& vec ) const;
    Vector2 operator*( const double alpha ) const;
    void    operator+=( const Vector2& vec );
    void    operator-=( const Vector2& vec );
    void    operator*=( const double alpha );
    bool    operator==( const Vector2& vec ) const;
    bool    operator!=( const Vector2& vec ) const;

    double  DotProduct( const Vector2& vec ) const;

    double x, y;

};


typedef Vector2 Point2_t;

#endif
