
#pragma once


#include <cassert>
#include <cfloat>
#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>

#include <SFML/System/Vector2.hpp>


class CwZeroFinder {
public:
    typedef std::pair<float, float> CwInterval_t;
    typedef std::function<float(float, sf::Vector2f, sf::Vector2f)> CwRealFunction_t;

    CwZeroFinder(
        CwRealFunction_t& fun,
        sf::Vector2f& param1,
        sf::Vector2f& param2
    );
    float GetZero() const;

private:
    bool GetSign(float point) const;
    bool IsFunctionGrowing(float start, float finish) const;
    bool IsFunctionPositive(float point) const;
    void DefineSignChangeInterval();

    CwRealFunction_t    m_function;
    sf::Vector2f        m_param1;
    sf::Vector2f        m_param2;
    CwInterval_t        m_interval;
};
