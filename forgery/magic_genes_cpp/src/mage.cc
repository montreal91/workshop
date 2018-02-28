
#include "mage.h"


MMage::MMage( bool female ) :
m_sex( female ),
m_current_age( 0 ),
m_estimated_age( 0 ),
m_current_children( 0 ),
m_estimated_children( 0 ) {
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<int> age_dis( 6, 16 );

    // simulates normal distribution with minimal value 30 and maximum value 80
    for ( int i = 0; i < 5; i++ ) {
        this->m_estimated_age += age_dis( gen );
    }

    std::uniform_int_distribution<int> children_dis( 0, 2 );
    for ( int i = 0; i < 3; i++ ) {
        this->m_estimated_children += children_dis( gen );
    }
}

MMage::MMage( MMage& mother, MMage& father ) :
m_sex( true ),
m_current_age( 0 ),
m_estimated_age( 0 ),
m_current_children( 0 ),
m_estimated_children( 0 ) {
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<int> age_dis( 3, 12 );

    if ( age_dis( gen ) % 2 == 0 ) {
        this->m_sex = true;
    } else {
        this->m_sex = false;
    }

    // simulates normal distribution with minimal value 25 and maximum value 80
    for ( int i = 0; i < 5; i++ ) {
        this->m_estimated_age += age_dis( gen );
    }
    std::uniform_int_distribution<int> children_dis( 0, 1 );
    for ( int i = 0; i < 3; i++ ) {
        this->m_estimated_children += children_dis( gen );
    }
}

int
MMage::GetCurrentAge() const {
    return this->m_current_age;
}

int
MMage::GetEstimatedAge() const {
    return this->m_estimated_age;
}

// int
// MMage::GetEstimatedChildren() const {
//     return this->m_current_children;
// }

int
MMage::GetEstimatedChildren() const {
    return this->m_estimated_children;
}

bool
MMage::GetSex() const {
    return this->m_sex;
}

void
MMage::AgeUp() {
    this->m_current_age++;
}

bool
MMage::IsAlive() const {
    return this->m_current_age <= this->m_estimated_age;
}

void
MMage::AddChild() {
    this->m_current_children++;
}

bool
MMage::IsReadyToMate() const {
    return this->m_current_children < this->m_estimated_children && this->m_current_age > 16;
}
