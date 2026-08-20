#include "Game.hpp"

#include <string>
#include <cstdlib>
#include <ctime>

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
    SetWindowMinSize(static_cast<int>(screenWidth), static_cast<int>(screenHeight));
    SetWindowMaxSize(static_cast<int>(screenWidth), static_cast<int>(screenHeight));
    SetTargetFPS(60);

    srand(static_cast<unsigned int>(time(nullptr)));

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
    } else if (currentState == GAMEOVER && IsKeyPressed(KEY_ENTER)) {
        resetGame();
    } else if (currentState == GAMEWON && IsKeyPressed(KEY_ENTER)) {
        resetGame();
    }
}

void Game::update() {
    float dt = GetFrameTime();

    if (currentState == PLAYING && modifiers.wifiActive) {
        SetTargetFPS(30);
    } else {
        SetTargetFPS(60);
    }

    if (currentState == PLAYING) {
        if (flashTimer > 0.0f) {
            flashTimer -= dt;
        }

        if (modifiers.thunderActive && flashTimer <= 0.0f) {
            if (rand() % 350 == 0) {
                flashTimer = 0.4f;
            }
        }

        if (roundStartTimer > 0.0f) {
            roundStartTimer -= dt;
            inputLocked = true;
        } else {
            inputLocked = false;
        }

        bool canClick = !inputLocked;

        hand.update(allStones, canClick, modifiers.tooStrongActive);
    
        bool allGroundStonesCollected = true;

        for (Stone& stone : allStones) {
            stone.update(modifiers);

            if (stone.isOnGround() && !stone.isPickedUp() && !stone.isTossed()) {
                allGroundStonesCollected = false;
            }

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
                
                if (currentRound >= 7) {
                    currentState = GAMEWON;
                } else {
                    startNextRound();
                }
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

        std::string modText = "Modifiers: ";
        if (modifiers.rainActive) modText += "[Rain] ";
        if (modifiers.windActive) modText += "[Wind] ";
        if (modifiers.thunderActive) modText += "[Thunder] ";
        if (modifiers.wifiActive) modText += "[Wi-Fi] ";
        if (modifiers.smallerRocksActive) modText += "[Small Rocks] ";
        if (modifiers.tooStrongActive) modText += "[Too Strong] ";
        DrawText(modText.c_str(), 20, 50, 16, DARKBLUE);

        for (Stone& stone : allStones) { stone.draw(); }

        hand.draw(modifiers.tooStrongActive);

        //modifier effects
        if (flashTimer > 0.0f) {
            float alpha = flashTimer / 0.4f; 
            DrawRectangle(0, 0, static_cast<int>(screenWidth), static_cast<int>(screenHeight), Fade(WHITE, alpha));
        }

        if (modifiers.rainActive) {
            for (int i = 0; i < 40; ++i) {
                float rx = static_cast<float>((i * 37) % static_cast<int>(screenWidth));
                float ry = static_cast<float>((static_cast<int>(GetTime() * 400 + i * 50)) % static_cast<int>(screenHeight));
                DrawLineV({rx, ry}, {rx - 2.0f, ry + 15.0f}, Fade(BLUE, 0.3f));
            }
        }

        if (modifiers.wifiActive) {
            int alphaPulse = static_cast<int>(GetTime() * 5) % 2;
            if (alphaPulse == 0) {
                DrawText("LAG [Wi-Fi]", screenWidth - 120, 20, 16, RED);
            }
        }

        if (modifiers.windActive) {
            for (int i = 0; i < 6; ++i) {
            float wx = static_cast<float>((static_cast<int>(GetTime() * 200 + i * 130)) % static_cast<int>(screenWidth));
            float wy = 100.0f + (i * 100.0f);
            DrawLineV({wx, wy}, {wx + 40.0f, wy}, Fade(SKYBLUE, 0.4f));
            }
        }

    }else if (currentState == GAMEOVER) {
        DrawText("Game Over", (screenWidth / 2) - MeasureText("Game Over", 100) / 2, 150, 100, DARKGRAY);
        DrawText("Press [ENTER] to restart", screenWidth / 2 - (MeasureText("Press [ENTER] to restart", 20) / 2 ) - 125, 350, 40, DARKGRAY);
    }else if (currentState == GAMEWON) {
        DrawText("Game Won!", (screenWidth / 2) - MeasureText("Game Over", 100) / 2, 150, 100, GOLD);
        DrawText("Press [ENTER] to play again", screenWidth / 2 - (MeasureText("Press [ENTER] to play again", 20) / 2 ) - 125, 350, 40, DARKGRAY);
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
    modifiers.updateModifiersForRound(currentRound);
    float radius = modifiers.smallerRocksActive ? 10.0f : 20.0f;

    for (int i = 0; i < 4; ++i) {
        float spaceBetween = static_cast<float>(screenWidth) / (4 + 1);
        allStones.emplace_back(Vector2 {spaceBetween * (i + 1), screenHeight - 15.0f}, radius);
    }

    for (int i = 0; i < tossCount; ++i) {
        float offsetX = (screenWidth / 2.0f) - (120.f / 2.0f) + 20.0f + (i * 40.0f);
        allStones.emplace_back(Vector2 {offsetX, screenHeight - 100.0f}, radius);
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
    modifiers.updateModifiersForRound(currentRound);
    float radius = modifiers.smallerRocksActive ? 10.0f : 20.0f;

    for (int i = 0; i < 4; ++i) {
        float spaceBetween = static_cast<float>(screenWidth) / (4 + 1);
        allStones.emplace_back(Vector2 {spaceBetween * (i + 1), screenHeight - 15.0f}, radius);
    }

    for (int i = 0; i < tossCount; ++i) {
        float offsetX = (screenWidth / 2.0f) - (120.f / 2.0f) + 20.0f + (i * 40.0f);
        allStones.emplace_back(Vector2 {offsetX, screenHeight - 100.0f}, radius);
        allStones.back().setPickedUp(true);
        hand.queueStoneToToss(&allStones.back());
    }
    

    roundStartTimer = 0.5f;
}