#include "Hand.hpp"

const float screenWidth = 800.0f;
const float screenHeight = 900.0f;

Hand::Hand() {
    m_position = { 0.0f, 0.0f };
    m_height = 40.0f;
    m_width = 120.0f;
    m_chargeTime = 0.0f;
}

void Hand::update(std::vector<Stone>& allStones) {
    if (isThrowingPhase()) {
        m_position = { screenWidth / 2.0f, screenHeight - 100.0f};
    } else {
        m_position = GetMousePosition();
    }

    for (Stone* stonePtr : heldStones) {
        stonePtr -> setPosition(m_position);
    }

    Rectangle handCollision = {
        m_position.x - m_width / 2.0f,
        m_position.y - m_height / 2.0f,
        m_width,
        m_height 
    };

    if (!stonesToToss.empty()) {
        stonesToToss[0]->setPosition(m_position);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isThrowingPhase()) {
        for (Stone& stone : allStones) {
            if (stone.isOnGround()) {
                if (CheckCollisionCircleRec(stone.getPosition(), stone.getRadius(), handCollision)) {
                    pickUpStone(&stone);
                    break;
                }
            }
        }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        m_chargeTime += GetFrameTime();
        if (m_chargeTime > 4.0f) {
            m_chargeTime = 4.0f;
        }
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        tossStone();
        m_chargeTime = 0.0f;
    }
}

void Hand::draw() {
    DrawRectangle(
        static_cast<int>(m_position.x - m_width/2.0f),
        static_cast<int>(m_position.y - m_height/2.0f),
        static_cast<int>(m_width),
        static_cast<int>(m_height),
        WHITE
    );
}

void Hand::pickUpStone(Stone* stone) {
    if (stone != nullptr) {
        heldStones.push_back(stone);
        stone->setPickedUp(true);
    }
}

void Hand::tossStone() {
    if (!stonesToToss.empty()) {
        float power = 30.0f + (m_chargeTime * 15.0f);
        Vector2 tossVelocity = { power * 0.4f, -power };

        Stone* stoneToToss = stonesToToss[0];
        stoneToToss -> toss(tossVelocity);
        stonesToToss.erase(stonesToToss.begin());
    }
}

void Hand::queueStoneToToss(Stone* stone) {
    stonesToToss.push_back(stone);
}

bool Hand::isThrowingPhase() const {
    return !stonesToToss.empty();
}

void Hand::clearStones() {
    heldStones.clear();
    stonesToToss.clear();
}