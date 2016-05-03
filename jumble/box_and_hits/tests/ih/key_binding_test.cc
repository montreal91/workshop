
#include "key_binding_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION( EKeyBindingTest );

void
EKeyBindingTest::setUp() {
    this->m_kb = ih::EKeyBinding();
}

void
EKeyBindingTest::TestGetAssignedKey() {
    CPPUNIT_ASSERT_EQUAL(
        this->m_kb.GetAssignedKey( ih::player_action::EeType::MoveForward ),
        sf::Keyboard::Up
    );
    CPPUNIT_ASSERT_EQUAL(
        this->m_kb.GetAssignedKey( ih::player_action::EeType::MoveBackward ),
        sf::Keyboard::Down
    );
    CPPUNIT_ASSERT_EQUAL(
        this->m_kb.GetAssignedKey( ih::player_action::EeType::RotateClockwise ),
        sf::Keyboard::Left
    );
    CPPUNIT_ASSERT_EQUAL(
        this->m_kb.GetAssignedKey( ih::player_action::EeType::RotateCounterClockwise ),
        sf::Keyboard::Right
    );
    CPPUNIT_ASSERT_EQUAL(
        this->m_kb.GetAssignedKey( ih::player_action::EeType::ActivateWeapon ),
        sf::Keyboard::Space
    );
    CPPUNIT_ASSERT_EQUAL(
        this->m_kb.GetAssignedKey( ih::player_action::EeType::DropBomb ),
        sf::Keyboard::LAlt
    );
}

void
EKeyBindingTest::TestAssignKey() {
    this->m_kb.AssignKey( ih::player_action::EeType::MoveForward, sf::Keyboard::Q );
    this->m_kb.AssignKey( ih::player_action::EeType::MoveBackward, sf::Keyboard::W );
    this->m_kb.AssignKey( ih::player_action::EeType::RotateClockwise, sf::Keyboard::E );
    this->m_kb.AssignKey(
        ih::player_action::EeType::RotateCounterClockwise,
        sf::Keyboard::A
    );
    this->m_kb.AssignKey( ih::player_action::EeType::ActivateWeapon, sf::Keyboard::S );
    this->m_kb.AssignKey( ih::player_action::EeType::DropBomb, sf::Keyboard::D );
    CPPUNIT_ASSERT_EQUAL(
        this->m_kb.GetAssignedKey( ih::player_action::EeType::MoveForward ),
        sf::Keyboard::Q
    );
    CPPUNIT_ASSERT_EQUAL(
        this->m_kb.GetAssignedKey( ih::player_action::EeType::MoveBackward ),
        sf::Keyboard::W
    );
    CPPUNIT_ASSERT_EQUAL(
        this->m_kb.GetAssignedKey( ih::player_action::EeType::RotateClockwise ),
        sf::Keyboard::E
    );
    CPPUNIT_ASSERT_EQUAL(
        this->m_kb.GetAssignedKey( ih::player_action::EeType::RotateCounterClockwise ),
        sf::Keyboard::A
    );
    CPPUNIT_ASSERT_EQUAL(
        this->m_kb.GetAssignedKey( ih::player_action::EeType::ActivateWeapon ),
        sf::Keyboard::S
    );
    CPPUNIT_ASSERT_EQUAL(
        this->m_kb.GetAssignedKey( ih::player_action::EeType::DropBomb ),
        sf::Keyboard::D
    );
}
