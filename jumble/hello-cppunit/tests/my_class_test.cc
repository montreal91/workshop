
#include "my_class_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MyClassTest);

// void
// MyClassTest::setUp() {
//     this
// }

void
MyClassTest::TestGettersAndSetters() {
    CPPUNIT_ASSERT_EQUAL(this->my_object.GetX(), 0);
    CPPUNIT_ASSERT_EQUAL(this->my_object.GetY(), 0);

    this->my_object.SetX(4);
    this->my_object.SetY(5);

    CPPUNIT_ASSERT_EQUAL(this->my_object.GetX(), 4);
    CPPUNIT_ASSERT_EQUAL(this->my_object.GetY(), 5);
}

void
MyClassTest::TestConstructors() {
    MyClass my_object1 = MyClass();

    CPPUNIT_ASSERT_EQUAL(my_object1.GetX(), 0);
    CPPUNIT_ASSERT_EQUAL(my_object1.GetY(), 0);

    MyClass my_object2 = MyClass(3);

    CPPUNIT_ASSERT_EQUAL(my_object2.GetX(), 3);
    CPPUNIT_ASSERT_EQUAL(my_object2.GetY(), 3);

    MyClass my_object3 = MyClass(3, 3*3);

    CPPUNIT_ASSERT_EQUAL(my_object3.GetX(), 3);
    CPPUNIT_ASSERT_EQUAL(my_object3.GetY(), 9);
}
