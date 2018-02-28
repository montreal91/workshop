
#include "society.h"


MSociety::MSociety() :
m_males(0),
m_females(0),
m_total_births( 0 ),
m_total_deaths( 0 ),
m_current_year( 0 ) {}

void
MSociety::AddCitizen( MMage& new_citizen ) {
    if ( new_citizen.GetSex() ) {
        this->m_females.push_back( new_citizen );
    } else {
        this->m_males.push_back( new_citizen );
    }
}

void
MSociety::LiveOneYear() {
    this->AgeAllUp();
    this->Reproduce();
    this->RemoveDead();
    this->m_current_year++;
}

void
MSociety::LiveManyYears( const int years ) {
    assert( years > 0 );
    for ( int i = 0; i < years; i++ ) {
        this->LiveOneYear();
    }
}

void
MSociety::PrintStatistics( std::ostream& os ) const {
    int total_population = this->m_males.size() + this->m_females.size();
    os << "____________________________\n";
    os << "Current Year:      " << this->m_current_year << "\n\n";
    os << "Total population:  " << total_population << "\n";
    os << "Male population:   " << this->m_males.size() << "\n";
    os << "Female population: " << this->m_females.size() << "\n\n";

    os << "Total births:      " << this->m_total_births << "\n";
    os << "Total deaths:      " << this->m_total_deaths << "\n\n";
}

void
MSociety::AgeAllUp() {
    for ( auto& man : this->m_males ) {
        man.AgeUp();
    }

    for ( auto& woman : this->m_females ) {
        woman.AgeUp();
    }
}

void
MSociety::Reproduce() {
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<int> man_dis( 0, this->m_males.size() - 1 );

    for ( auto& woman : this->m_females ) {
        if ( woman.IsReadyToMate() ) {
            // std::cout << "m\n";
            int man_index = man_dis( gen );
            MMage new_mage( woman, this->m_males[man_index] );
            this->AddCitizen( new_mage );
            woman.AddChild();
            this->m_total_births++;
        }
    }
}

void
MSociety::RemoveDead() {
    for ( auto i = this->m_males.begin(); i != this->m_males.end(); ) {
        if ( !i->IsAlive() ) {
            i = this->m_males.erase( i );
            this->m_total_deaths++;
        } else {
            i++;
        }
    }
    this->m_males.shrink_to_fit();

    for ( auto i = this->m_females.begin(); i != this->m_females.end(); ) {
        if ( !i->IsAlive() ) {
            i = this->m_females.erase( i );
            this->m_total_deaths++;
        } else {
            i++;
        }
    }
    this->m_females.shrink_to_fit();
}
