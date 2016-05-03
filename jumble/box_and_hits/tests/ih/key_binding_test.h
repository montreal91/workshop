
#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include <SFML/Window/Keyboard.hpp>

#include "src/ih/key_binding.h"

class EKeyBindingTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE( EKeyBindingTest );
    CPPUNIT_TEST( TestGetAssignedKey );
    CPPUNIT_TEST( TestAssignKey );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();

protected:
    ih::EKeyBinding m_kb;

    void TestGetAssignedKey();
    void TestAssignKey();
};
