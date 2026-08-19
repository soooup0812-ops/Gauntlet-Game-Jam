#include "Game.hpp"

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
    Game game;
    game.run();
    return 0;
}