
#include "Vector3.h"


Vector3::Vector3() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3::Vector3( double x ) {
    this->x = x;
    this->y = x;
    this->z = x;
}

Vector3::Vector3( double x, double y, double z ) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3( const Vector2& vec ) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = 0;
}

Vector3::Vector3( const Vector3& vec ) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
}

Vector3::~Vector3() {
}

Vector3
Vector3::operator+( const Vector3& vec ) const {
    double x = this->x + vec.x;
    double y = this->y + vec.y;
    double z = this->z + vec.z;
    return Vector3( x, y, z );
}

Vector3
Vector3::operator-( const Vector3& vec ) const {
    double x = this->x - vec.x;
    double y = this->y - vec.y;
    double z = this->z - vec.z;
    return Vector3( x, y, z );
}

Vector3
Vector3::operator*( const double alpha ) const {
    double x = this->x * alpha;
    double y = this->y * alpha;
    double z = this->z * alpha;
    return Vector3( x, y, z );
}

void
Vector3::operator+=( const Vector3& vec ) {
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;
}

void
Vector3::operator-=( const Vector3& vec ) {
    this->x -= vec.x;
    this->y -= vec.y;
    this->z -= vec.z;
}

void
Vector3::operator*=( const double alpha ) {
    this->x *= alpha;
    this->y *= alpha;
    this->z *= alpha;
}

bool
Vector3::operator==( const Vector3& vec ) const {
    return this->x == vec.x && this->y == vec.y && this->z == vec.z;
}

bool
Vector3::operator!=( const Vector3& vec ) const {
    return this->x != vec.x || this->y != vec.y || this->z != vec.z;
}

double
Vector3::DotProduct( const Vector3& vec ) const {
    return this->x * vec.x + this->y * vec.y + this->z * vec.z;
}

Vector3
Vector3::CrossProduct( const Vector3& vec ) const {
    double x = this->y * vec.z - this->z * vec.y;
    double y = -this->x * vec.z + this->z * vec.x;
    double z = this->x * vec.y - this->y * vec.x;
    return Vector3( x, y, z );
}

bool
Vector3::IsNullVector() const {
    double  epsilon = 0.00001;
    bool    cond1   = fabs( this->x ) < epsilon;
    bool    cond2   = fabs( this->y ) < epsilon;
    bool    cond3   = fabs( this->z ) < epsilon;
    return cond1 && cond2 && cond3;
}

bool
Vector3::IsCollinearTo( const Vector3& vec ) const {
    double product = this->DotProduct( vec );
    return fabs( product ) <= 0.00001;
}

double
Vector3::GetLength() const {
    return std::sqrt( this->x * this->x + this->y * this->y + this->z * this->z );
}

Vector3
Vector3::GetNormalizedVector() const {
    double length = this->GetLength();
    return Vector3( this->x / length, this->y / length, this->z / length );
}
