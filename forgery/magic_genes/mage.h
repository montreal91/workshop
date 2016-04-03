
#pragma once

#include <iostream>
#include <vector>
#include <random>


class MMage {
public:
    MMage();
    MMage( int magic, int endurance, bool female = true );
    ~MMage();

    int GetMagicGenes() const;
    int GetEnduranceGenes() const;
    // int GetStabilityGenes() const;
    int GetCurrentAge() const;
    int GetEstimatedAge() const; // TODO: remove in release
    int GetEstimatedChildren() const; // TODO: think about this function
    bool GetSex() const;

private:
    int m_magic_genes;
    int m_endurance_genes;
    // int m_stability_genes;
    bool m_sex; // true - female, false = male

    int m_current_age;
    int m_estimated_age;
    int m_estimated_children;
};
