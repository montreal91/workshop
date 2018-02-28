
#pragma once


#include <iostream>
#include <vector>
#include <random>


class MMage {
public:
    MMage( bool female = true );
    MMage( MMage& mother, MMage& father );

    int     GetCurrentAge() const;
    int     GetEstimatedAge() const; // TODO: remove in release
    // int     GetCurrentChildren() const;
    int     GetEstimatedChildren() const;
    bool    GetSex() const;

    void    AgeUp();
    bool    IsAlive() const;

    void    AddChild();
    bool    IsReadyToMate() const;

private:
    bool    m_sex; // true - female, false = male

    int     m_current_age;
    int     m_estimated_age;
    int     m_current_children;
    int     m_estimated_children;
};
