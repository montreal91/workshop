
#pragma once

class MyClass {
public:
    MyClass();
    MyClass(int var);
    MyClass(int x, int y);
    ~MyClass();

    int GetX() const;
    void SetX( int x );

    int GetY() const;
    void SetY( int y);

private:
    int x;
    int y;
};
