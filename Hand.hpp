#pragma once

#include <vector>

#include "raylib.h"
#include "Stone.hpp"

class Hand {
public:
    Hand();
    ~Hand();

    void update(std::vector<Stone>& allStones, bool canClick, bool tooStrongActive);
    void draw(bool tooStrongActive);
    void pickUpStone(Stone* stone);
    void tossStone(bool tooStrongActive);

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
    Texture2D m_openTexture;
    Texture2D m_clenchTexture;
};