
#include <vector>
#include <iostream>

#include "mage.h"

int main() {
    std::vector<MMage> mages;
    for( int i = 0; i < 20; i++ ) {
        MMage m = MMage();
        mages.push_back( m );
    }

    for( const auto& mage : mages ) {
        std::cout << mage.GetEstimatedAge() << " ";
        std::cout << mage.GetEstimatedChildren() << "\n";
    }
    return 0;
}
