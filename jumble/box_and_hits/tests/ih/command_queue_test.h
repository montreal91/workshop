
#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "src/ih/category.h"
#include "src/ih/command.h"
#include "src/ih/command_queue.h"

class ECommandQueueTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE( ECommandQueueTest );
    CPPUNIT_TEST( TestGetSize );
    CPPUNIT_TEST( TestPushAndPop );
    CPPUNIT_TEST_SUITE_END();

protected:
    void TestGetSize();
    void TestPushAndPop();
};
