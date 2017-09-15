
#include "zero_finder.h"


CwZeroFinder::CwZeroFinder(
    CwRealFunction_t& fun,
    sf::Vector2f& param1,
    sf::Vector2f& param2 ) :
m_function( fun ),
m_param1( param1 ),
m_param2( param2 ) {
    this->DefineSignChangeInterval();
}

bool
CwZeroFinder::IsFunctionGrowing(float start, float finish) const{
    float start_val = this->m_function(
        start,
        this->m_param1,
        this->m_param2
    );
    float finish_val = this->m_function(
        finish,
        this->m_param1,
        this->m_param2
    );
    return finish_val > start_val;
}

bool
CwZeroFinder::IsFunctionPositive(float point) const {
    float val = this->m_function(
        point,this->m_param1, this->m_param2
    );
    return val >= 0.0f;
}

float
CwZeroFinder::GetZero() const {
    float start = this->m_interval.first;
    float finish = this->m_interval.second;
    assert(GetSign(start) != GetSign(finish));
    float middle = 0.0f;
    if (!this->IsFunctionGrowing( start, finish ) ) {
        do {
            middle = (start + finish) / 2;
            if (this->IsFunctionPositive(middle)) {
                start = middle;
            } else {
                finish = middle;
            }
        } while (fabs(finish - start) / 2 > 0.01f);
    } else {
        do {
            middle = (start + finish) / 2;
            if (this->IsFunctionPositive(middle)) {
                finish = middle;
            } else {
                start = middle;
            }
        } while (fabs(finish - start) / 2 > 0.01f);
    }
    return middle;
}

bool
CwZeroFinder::GetSign(float point) const {
    float c1 = this->m_function(
        point,
        this->m_param1,
        this->m_param2
    );
    float c2 = std::fabs(
        this->m_function(point, this->m_param1, this->m_param2)
    );
    return c1 == c2;
}

void
CwZeroFinder::DefineSignChangeInterval() {
    float start     = 0.0f;
    float finish    = 0.0f;
    float step      = 1.0f;
    float increment = 1.0f;
    do {
        start = finish;
        finish += step * increment;
        increment++;
        if (finish >= 1000000.0f) {
            throw std::runtime_error("No sign change.");
        }
    } while (this->GetSign(start) == this->GetSign(finish));
    this->m_interval = CwInterval_t(start, finish);
}
