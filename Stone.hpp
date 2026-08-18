#pragma once

#include <vector>

#include "raylib.h"

class Stone{
public:
    Stone(float startX);

    void update();
    void draw();
    void toss(Vector2 velocity);

private:
    Vector2 m_position;
    Vector2 m_velocity;
    float m_radius, m_mass;
    bool m_isTossed;
    bool m_isOnGround;
    bool m_isPickedUp;
};