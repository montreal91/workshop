
#include "Vector2.h"

Vector2::Vector2() {
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2( double x ) {
    this->x = x;
    this->y = x;
}

Vector2::Vector2( double x, double y ) {
    this->x = x;
    this->y = y;
}

Vector2::Vector2( const Vector2& vec ) {
    this->x = vec.x;
    this->y = vec.y;
}

Vector2::~Vector2(){
}

Vector2
Vector2::operator+( const Vector2& vec ) const {
    double x = this->x + vec.x;
    double y = this->y + vec.y;
    return Vector2( x, y );
}

Vector2
Vector2::operator-( const Vector2& vec ) const {
    double x = this->x - vec.x;
    double y = this->y - vec.y;
    return Vector2( x, y );
}

Vector2
Vector2::operator*( const double alpha ) const {
    double x = this->x * alpha;
    double y = this->y * alpha;
    return Vector2( x, y );
}

void
Vector2::operator+=( const Vector2& vec ) {
    this->x += vec.x;
    this->y += vec.y;
}

void
Vector2::operator-=( const Vector2& vec ) {
    this->x -= vec.x;
    this->y -= vec.y;
}

void
Vector2::operator*=( const double alpha ) {
    this->x *= alpha;
    this->y *= alpha;
}

bool
Vector2::operator==( const Vector2& vec ) const {
    return this->x == vec.x && this->y == vec.y;
}

bool
Vector2::operator!=( const Vector2& vec ) const {
    return this->x != vec.x || this->y != vec.y;
}

double
Vector2::DotProduct( const Vector2& vec ) const {
    return this->x * vec.x + this->y * vec.y;
}
