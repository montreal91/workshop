
#pragma once


#include <cassert>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "mage.h"


class MSociety {
public:
    MSociety();
    
    void AddCitizen( MMage& new_citizen );
    void LiveOneYear();
    void LiveManyYears( const int years );

    void PrintStatistics( std::ostream& os ) const;

private:
    void AgeAllUp();
    void Reproduce();
    void RemoveDead();

    // int GetTotalPopulation()

    std::vector<MMage> m_males;
    std::vector<MMage> m_females;

    long m_total_births;
    long m_total_deaths;
    long m_current_year;
};
