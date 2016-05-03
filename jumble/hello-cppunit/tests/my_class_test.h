
#include <cppunit/extensions/HelperMacros.h>

#include "src/my_class.h"


class MyClassTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE( MyClassTest );
    CPPUNIT_TEST(TestGettersAndSetters);
    CPPUNIT_TEST(TestConstructors);
    CPPUNIT_TEST_SUITE_END();

protected:
    MyClass my_object;

// public:
//     void setUp();

protected:
    void TestGettersAndSetters();
    void TestConstructors();
};
