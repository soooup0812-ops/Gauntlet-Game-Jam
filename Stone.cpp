#include "Stone.hpp"

const float screenWidth = 800.0f;
const float screenHeight = 900.0f;

Stone::Stone(Vector2 startPosition) : m_position(startPosition) {
    m_velocity.x = 0.0f;
    m_velocity.y = 0.0f;
    m_radius = 15.0f;
    m_isTossed = false;
    m_isOnGround = true;
    m_isPickedUp = false;
}

void Stone::update() {
    if (m_isTossed == true) {
        const float gravity = 0.5f;
        m_velocity.y += gravity; //move faster going down
        m_position.y += m_velocity.y; //vertical movement
        m_position.x += m_velocity.x; //horizontal movement
    }

    //left wall collision
    if (m_position.x - m_radius <= 0.0f) {
        m_position.x = m_radius;
        m_velocity.x = -m_velocity.x * 0.7f; //Bounce off and lose velocity
    }

    //right wall collision
    if (m_position.x + m_radius >= screenWidth) {
        m_position.x = screenWidth - m_radius;
        m_velocity.x = -m_velocity.x * 0.7f;
    }

    //ceiling collision
    if (m_position.y - m_radius <= 0.0f) {
        m_position.y = m_radius;
        m_velocity.y = -m_velocity.y * 0.7f;
    }

    //floor collision
    if (m_position.y + m_radius >= screenHeight) {
        m_position.y = screenHeight - m_radius;
        m_velocity.y = 0.0f;
        m_velocity.x = 0.0f;
        m_isOnGround = true;
    }
}

void Stone::draw() {
    if (m_isPickedUp == true) {
        return;
    }

    Color stoneColor = GRAY;
    DrawCircle(static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_radius, stoneColor); //drawCircle needs integers
}

void Stone::toss(Vector2 velocity) {
    m_velocity = velocity;
    m_isTossed = true;
    m_isOnGround = false;
    m_isPickedUp = false;
}