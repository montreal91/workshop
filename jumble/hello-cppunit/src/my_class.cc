
#include <algorithm>
#include <stdexcept>

#include "my_class.h"

MyClass::MyClass() {
    this->x = 0;
    this->y = 0;
}

MyClass::MyClass(int val) {
    this->x = val;
    this->y = val;
}

MyClass::MyClass(int x, int y) {
    this->x = x;
    this->y = y;
}

MyClass::~MyClass() {}

int
MyClass::GetX() const {
    return this->x;
}

void
MyClass::SetX(int x) {
    this->x = x;
}

int
MyClass::GetY() const {
    return this->y;
}

void
MyClass::SetY(int y) {
    this->y = y;
}
