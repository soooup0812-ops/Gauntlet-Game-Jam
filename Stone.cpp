#include "Stone.hpp"

Stone::Stone(float startX) : m_x(startX), m_y(585.0f) {
    m_velocityX = 0.0f;
    m_velocityY = 0.0f;
    m_radius = 15.0f;
    m_mass = 1.0f;
    m_isTossed = false;
    m_isOnGround = true;
    m_isPickedUp = false;
}

void Stone::update() {
    if (m_isTossed) {
        float gravity = 0.5f;
        m_velocityY += gravity; //move faster going down
        m_y += m_velocityY; //vertical movement
        m_x += m_velocityX; //horizontal movement
    }

    float screenWidth = 800.0f;
    float screenHeight = 600.0f;

    //left wall collision
    if (m_x - m_radius <= 0.0f) {
        m_x = m_radius;
        m_velocityX = -m_velocityX * 0.7f; //Bounce off and lose velocity
    }

    //right wall collision
    if (m_x + m_radius >= screenWidth) {
        m_x = screenWidth - m_radius;
        m_velocityX = -m_velocityX * 0.7f;
    }

    //ceiling collision
    if (m_y - m_radius <= 0.0f) {
        m_y = m_radius;
        m_velocityY = -m_velocityY * 0.7f;
    }

    //floor collision
    if (m_y + m_radius >= screenHeight) {
        m_y = screenHeight - m_radius;
        m_velocityY = 0.0f;
        m_velocityX = 0.0f;
        m_isTossed = false;
        m_isOnGround = true;
    }
}

void Stone::draw() {
    Color stoneColor = GRAY;
    DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), m_radius, stoneColor); //drawCircle needs integers
}

void Stone::toss(Vector2 velocity) {
    m_velocity = velocity;
    m_isTossed = true;
    m_isOnGround = false;
}