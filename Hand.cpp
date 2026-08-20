#include "Hand.hpp"

#include <cstdlib>
#include <ctime>

const float screenWidth = 800.0f;
const float screenHeight = 900.0f;

Hand::Hand() {
    m_position = { 0.0f, 0.0f };
    m_height = 80.0f;
    m_width = 120.0f;
    m_chargeTime = 0.0f;
}

Hand::~Hand() {
    UnloadTexture(m_openTexture);
    UnloadTexture(m_clenchTexture);
}

void Hand::update(std::vector<Stone>& allStones, bool canClick, bool tooStrongActive) {
    float dt = GetFrameTime();

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
        for (size_t i = 0; i < stonesToToss.size(); ++i) {
            float offsetX = -((stonesToToss.size() - 1) * 20.0f) + (i * 40.0f);
            stonesToToss[i]->setPosition({m_position.x + offsetX, m_position.y});
        }
    }

    if (!canClick) {
        m_chargeTime = 0.0f;
    }

    if (canClick && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isThrowingPhase()) {
        for (Stone& stone : allStones) {
            if ((stone.isOnGround() || stone.isTossed()) && !stone.isPickedUp()) { //!isPickedUp() to prevent double click leading to duplicated pointer
                if (CheckCollisionCircleRec(stone.getPosition(), stone.getRadius(), handCollision)) {
                    pickUpStone(&stone);
                    break;
                }
            }
        }
    }

    if (canClick && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        m_chargeTime += dt;
        if (m_chargeTime > 4.0f) {
            m_chargeTime = 4.0f;
        }
    }

    if (canClick && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        tossStone(tooStrongActive);
        m_chargeTime = 0.0f;
    }
}

void Hand::draw(bool tooStrongActive) {
    if (m_openTexture.id == 0) {
        m_openTexture = LoadTexture("assets/open.png");
        m_clenchTexture = LoadTexture("assets/clench.png");
    }
    
    Texture2D currentTexture = (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || isThrowingPhase()) ? m_clenchTexture : m_openTexture;
    Rectangle source = { 0.0f, 0.0f, static_cast<float>(currentTexture.width), static_cast<float>(currentTexture.height) };
    Rectangle dest = { m_position.x, m_position.y, m_width, m_height };
    Vector2 origin = { m_width / 2.0f, m_height / 2.0f };

    DrawTexturePro(currentTexture, source, dest, origin, 0.0f, WHITE);
}

void Hand::pickUpStone(Stone* stone) {
    if (stone != nullptr) {
        heldStones.push_back(stone);
        stone->setPickedUp(true);
    }
}

void Hand::tossStone(bool tooStrongActive) {
    if (!stonesToToss.empty()) {
        float multiplier = tooStrongActive ? 2.5f : 1.0f;
        float power = 600.0f + (m_chargeTime * 400.0f) * multiplier;

        for (Stone* stoneToToss : stonesToToss) {
            float randomDirection = ((static_cast<float>(rand())/RAND_MAX) * 1.6f) - 0.8f; //divide by RAND_MAX to turn whole numbers returned by rand() to float
            Vector2 tossVelocity = { power * randomDirection, -power };
            stoneToToss->setPickedUp(false);
            stoneToToss -> toss(tossVelocity);
        }
    }
    stonesToToss.clear();
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