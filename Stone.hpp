#pragma once

#include <vector>

#include "raylib.h"

class Stone{
public:
    Stone(Vector2 startPosition);

    void update();
    void draw();
    void toss(Vector2 velocity);
    float getRadius() const { return m_radius; } //getter
    bool isOnGround() const { return m_isOnGround; } //getter, setter is innate to update() and toss()
    bool isTossed() const { return m_isTossed; } //getter, setter is also innate to the two above
    bool isPickedUp() const { return m_isPickedUp; } //getter

    Vector2 getPosition() const { return m_position; } //getter
    void setPosition(Vector2 position) { m_position = position; } //setter
    void setPickedUp(bool pickedUp) { m_isPickedUp = pickedUp; } // setter

private:
    Vector2 m_position;
    Vector2 m_velocity;
    float m_radius;
    bool m_isOnGround;
    bool m_isTossed;
    bool m_isPickedUp;
};