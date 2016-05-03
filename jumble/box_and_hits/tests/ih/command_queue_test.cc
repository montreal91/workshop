
#include "command_queue_test.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ECommandQueueTest);

void
ECommandQueueTest::TestGetSize() {
    ih::ECommandQueue ecq;
    CPPUNIT_ASSERT_EQUAL( ecq.GetSize(), 0 );
    for ( int i = 0; i < 10; i++ ) {
        ih::EsCommand command;
        ecq.Push(command);
        CPPUNIT_ASSERT_EQUAL( ecq.GetSize(), i + 1 );
    }

    for ( int i = 0; i < ecq.GetSize(); i++ ) {
        ecq.Pop();
        CPPUNIT_ASSERT_EQUAL( ecq.GetSize(), 10 - (i+1) );
    }
}

void
ECommandQueueTest::TestPushAndPop() {
    ih::ECommandQueue ecq;
    for ( int i = 0; i < 10; i++ ) {
        ih::EsCommand command;
        ecq.Push(command);
        CPPUNIT_ASSERT_EQUAL( ecq.GetSize(), i + 1 );
    }

    ih::EsCommand unique_command1;
    unique_command1.category = ih::EeCategory::PlayerShip;

    ih::EsCommand unique_command2;
    unique_command2.category = ih::EeCategory::Projectile;

    ecq.Push(unique_command1);
    ecq.Push(unique_command2);

    CPPUNIT_ASSERT_EQUAL( ecq.GetSize(), 12 );

    for ( int i = 0; i < 10; i++ ) {
        auto command_from_queue = ecq.Pop();
        CPPUNIT_ASSERT( command_from_queue.category == ih::EeCategory::None );
        CPPUNIT_ASSERT_EQUAL( ecq.GetSize(), 12 - (i + 1) );
    }

    auto command_from_queue = ecq.Pop();
    CPPUNIT_ASSERT( command_from_queue.category == ih::EeCategory::PlayerShip );
    CPPUNIT_ASSERT_EQUAL( ecq.GetSize(), 1 );

    command_from_queue = ecq.Pop();
    CPPUNIT_ASSERT( command_from_queue.category == ih::EeCategory::Projectile );
    CPPUNIT_ASSERT_EQUAL( ecq.GetSize(), 0 );
}
