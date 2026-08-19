#include "Game.hpp"

float dt = GetFrameTime();

Game::Game() {
    currentState = MENU;
    currentRound = 1;
    tossCount = getTossCount(currentRound);
}

int Game::getTossCount(int round) const {
    if (round >= 6) return 3; 
    else if (round >= 3) return 2;
    else return 1;
}

void Game::run(){
    InitWindow(screenWidth, screenHeight, "Ambatutoss");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(static_cast<int>(screenWidth), static_cast<int>(screenHeight));
    SetWindowMaxSize(static_cast<int>(screenWidth), static_cast<int>(screenHeight));
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        processInput();
        update();
        render();
    }

    CloseWindow();
}

void Game::processInput() {
    if (currentState == MENU && IsKeyPressed(KEY_ENTER)) {
        resetGame();
    } else if (currentState == GAMEOVER && IsKeyPressed(KEY_ENTER))
        resetGame();
}

void Game::update() {
    if (currentState == PLAYING) {
        if (roundStartTimer > 0.0f) {
            roundStartTimer -= dt;
            inputLocked = true;
        } else {
            inputLocked = false;
        }

        bool canClick = !inputLocked;

        hand.update(allStones, canClick);
    
        bool allGroundStonesCollected = true;
        for (const Stone& stone : allStones) {
            if (stone.isOnGround() && !stone.isPickedUp() && !stone.isTossed()) {
                allGroundStonesCollected = false;
                break;
            }
        }

        for (Stone& stone : allStones) {
        stone.update();

            if (stone.isTossed() && stone.isOnGround() && !stone.isPickedUp()) { //lose case 1 : a tossed stone was not caught
                currentState = GAMEOVER;
                return;
            }

            if (stone.isTossed() && stone.isPickedUp() && !allGroundStonesCollected) { //lose case 2 : tossed stone was caught before collecting all ground stones
                currentState = GAMEOVER;
                return;
            }
        }

        if (!hand.isThrowingPhase()) {
            bool allStonesCollected = true;
            for (const Stone& stone : allStones) {
                if (!stone.isPickedUp()) {
                    allStonesCollected = false;
                    break;
                }
            }

            if (allStonesCollected == true) { //win!
                startNextRound();
            }
        }
    }
}

void Game::render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (currentState == MENU) {
        DrawText("AMBATUTOSS", (screenWidth / 2) - MeasureText("AMBATUTOSS", 100) / 2, 150, 100, DARKGRAY);
        DrawText("Press [ENTER] to start", screenWidth / 2 - (MeasureText("Press [ENTER] to start", 20) / 2 ) - 125, 350, 40, DARKGRAY);
    } else if (currentState == PLAYING) {
        HideCursor();
        DrawText(TextFormat("Round: %d", currentRound), 20, 20, 20, GRAY);

        for (Stone& stone : allStones) { stone.draw(); }

        hand.draw();
    }else if (currentState == GAMEOVER) {
        DrawText("Game Over", (screenWidth / 2) - MeasureText("Game Over", 100) / 2, 150, 100, DARKGRAY);
        DrawText("Press [ENTER] to restart", screenWidth / 2 - (MeasureText("Press [ENTER] to restart", 20) / 2 ) - 125, 350, 40, DARKGRAY);
    }

    EndDrawing();
}

void Game::resetGame() {
    allStones.clear();
    hand.clearStones();
    currentRound = 1;
    int tossCount = getTossCount(currentRound);
    allStones.reserve(4 + tossCount);
    inputLocked = true;

    for (int i = 0; i < 4; ++i) {
        float spaceBetween = static_cast<float>(screenWidth) / (4 + 1);
        allStones.emplace_back(Vector2 {spaceBetween * (i + 1), screenHeight - 15.0f});
    }

    for (int i = 0; i < tossCount; ++i) {
        allStones.emplace_back(Vector2 {static_cast<float>(screenWidth / 2), screenHeight - 15.0f});
        allStones.back().setPickedUp(true);
        hand.queueStoneToToss(&allStones.back());
    }

    currentState = PLAYING;
    roundStartTimer = 0.5f;
}

void Game::startNextRound() {
    currentRound++;
    tossCount = getTossCount(currentRound);
    allStones.clear();
    hand.clearStones();
    allStones.reserve(4 + tossCount);
    inputLocked = true;

    for (int i = 0; i < 4; ++i) {
        float spaceBetween = static_cast<float>(screenWidth) / (4 + 1);
        allStones.emplace_back(Vector2 {spaceBetween * (i + 1), screenHeight - 15.0f});
    }

    for (int i = 0; i < tossCount; ++i) {
        allStones.emplace_back(Vector2 {static_cast<float>(screenWidth / 2), screenHeight - 15.0f});
        allStones.back().setPickedUp(true);
        hand.queueStoneToToss(&allStones.back());
    }

    roundStartTimer = 0.5f;
}