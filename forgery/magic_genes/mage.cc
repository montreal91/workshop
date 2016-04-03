
#include "mage.h"

MMage::MMage() :
m_magic_genes( 0 ),
m_endurance_genes( 0 ),
m_sex( true ),
m_current_age( 0 ),
m_estimated_age( 0 ),
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

// TODO: test this constructor
MMage::MMage( int magic, int endurance, bool female ) :
m_magic_genes( magic ),
m_endurance_genes( endurance ),
m_sex( female ),
m_current_age( 0 ),
m_estimated_age( 0 ),
m_estimated_children( 0 ) {
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<int> age_dis( 6, 16 );

    // simulates normal distribution with minimal value 30 and maximum value 80
    for ( int i = 0; i < 5; i++ ) {
        this->m_estimated_age += age_dis( gen );
    }

    if ( this->m_sex ) {
        std::uniform_int_distribution<int> children_dis( 0, 2 );
        for ( int i = 0; i < 3; i++ ) {
            this->m_estimated_children += children_dis( gen );
        }
    }
}

MMage::~MMage() {}

int
MMage::GetMagicGenes() const {
    return this->m_magic_genes;
}

int
MMage::GetEnduranceGenes() const {
    return this->m_endurance_genes;
}

int
MMage::GetCurrentAge() const {
    return this->m_current_age;
}

int
MMage::GetEstimatedAge() const {
    return this->m_estimated_age;
}

int
MMage::GetEstimatedChildren() const {
    return this->m_estimated_children;
}

bool
MMage::GetSex() const {
    return this->m_sex;
}
