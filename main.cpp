#include "raylib.h"
#include "Stone.hpp"

int GetStoneCountForRound(int round) {
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

    const int screenWidth = 800;
    const int screenHeight = 600;

    float floor = screenHeight;

    InitWindow(screenWidth, screenHeight, "Ambatutoss");
    SetTargetFPS(60);

    Stone test(400.0f);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Ambatutoss", 190, 200, 20, LIGHTGRAY);

        test.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}