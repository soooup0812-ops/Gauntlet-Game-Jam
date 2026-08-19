#pragma once

#include <vector>

#include "raylib.h"
#include "Stone.hpp"

class Hand {
public:
    Hand();

    void update(std::vector<Stone>& allStones);
    void draw();
    void pickUpStone(Stone* stone);
    void tossStone();

    void queueStoneToToss(Stone* stone);
    bool isThrowingPhase() const;
    void clearStones();

private:
    std::vector<Stone*> heldStones; //stones picked up
    std::vector<Stone*> stonesToToss; //stones thrown at start of round
    Vector2 m_position;
    float m_chargeTime;
    float m_width;
    float m_height;
};