#pragma once

#include <vector>

#include "raylib.h"
#include "Stone.hpp"
#include "Hand.hpp"
#include "Modifiers.hpp"

enum GameState {
    MENU,
    PLAYING,
    GAMEOVER,
    GAMEWON
};

class Game {
public:
    Game();
    void run();

private:
    void processInput();
    void update();
    void render();
    void resetGame();
    void startNextRound();
    int getTossCount(int round) const;

    const float screenWidth = 800.0f;
    const float screenHeight = 900.0f;

    GameState currentState;
    Hand hand;
    std::vector<Stone> allStones;
    int currentRound;
    int tossCount;
    float roundStartTimer;
    float flashTimer = 0.0f;
    bool inputLocked = false;
    GameModifiers modifiers;
};