#include "raylib.h"
#include "Stone.hpp"
#include "Hand.hpp"

enum GameState {
    MENU,
    PLAYING,
    GAMEOVER
};

int getTossCount(int round) {
    if (round >= 6) return 3; 
    else if (round >= 3) return 2;
    else return 1;
}

int main() {
    //Raylib functions to know
    // const int screenWidth
    // const int screenHeight
    // InitWindow(screenWidth, screenHeight, "Title");
    // SetTargetFPS(60);
    // while (!WindowShouldClose())
    // BeginDrawing();
    // ClearBackground(color);
    // DrawText("Message", posX, posY, fontSize, color);
    // DrawCircle(centerX, centerY, radius, color);
    // EndDrawing();
    // CloseWindow();
    const float screenWidth = 800.0f;
    const float screenHeight = 900.0f;

    InitWindow(screenWidth, screenHeight, "Ambatutoss");
    SetWindowMinSize(static_cast<int>(screenWidth), static_cast<int>(screenHeight));
    SetWindowMaxSize(static_cast<int>(screenWidth), static_cast<int>(screenHeight));
    SetTargetFPS(60);

    GameState currentState = MENU;
    
    Hand hand;

    std::vector<Stone> allStones;

    int currentRound = 1;
    int tossCount = getTossCount(currentRound);

    while (!WindowShouldClose()) {
        if (currentState == MENU) {
            if (IsKeyPressed(KEY_ENTER)) {
                allStones.clear();
                hand.clearStones();
                allStones.reserve(4 + tossCount);

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
            }
        }
        else if (currentState == PLAYING) {
            hand.update(allStones);

            for (Stone& stone : allStones) {
                stone.update();

                if (stone.isTossed() && stone.isOnGround()) {
                    currentState = GAMEOVER;
                }
            }
        }
        else if (currentState == GAMEOVER) {
            if (IsKeyPressed(KEY_ENTER)) {
                allStones.clear();
                hand.clearStones();
                currentRound = 1;
                int tossCount = getTossCount(currentRound);
                allStones.reserve(4 + tossCount);

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
            }
        }

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
            DrawText("Press [ENTER] to start", screenWidth / 2 - (MeasureText("Press [ENTER] to start", 20) / 2 ) - 125, 350, 40, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}