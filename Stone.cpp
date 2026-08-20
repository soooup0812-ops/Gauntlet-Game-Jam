#include "Stone.hpp"

const float screenWidth = 800.0f;
const float screenHeight = 900.0f;

Stone::Stone(Vector2 startPosition, float radius) : m_position(startPosition) {
    m_velocity.x = 0.0f;
    m_velocity.y = 0.0f;
    m_radius = radius;
    m_isTossed = false;
    m_isOnGround = true;
    m_isPickedUp = false;
}

void Stone::update(const GameModifiers& modifiers) {
    float dt = GetFrameTime();
    if (m_isTossed == true) {
        const float gravity = modifiers.rainActive ? 700.0f : 400.0f; //if rain active increase gravity
        m_velocity.y += gravity * dt; //move faster going down

        if (modifiers.windActive) {
            m_velocity.x += 150.0f * dt; 
        }
        
        m_position.y += m_velocity.y * dt; //vertical movement
        m_position.x += m_velocity.x * dt; //horizontal movement
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