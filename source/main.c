#include "raylib.h"
#include "arrow.h"

#define screenWidth 1280
#define screenHeight 800
#define NUM_ARROWS 15
typedef struct Point
{
    float x,y;
}Point;

int main() {
    InitWindow(screenWidth, screenHeight, "Seta Hero");
    SetTargetFPS(60);

    Arrow arrows[NUM_ARROWS];
    Point center;
    center.x = 200;
    center.y = screenHeight/2;

    float times[NUM_ARROWS] = {
    0.5, 1.0, 1.5, 2.0, 2.5,
    3.0, 3.5, 0, 4.5, 5.0,
    5.5, 6.0, 6.5,6.8, 7.1}
    ;

    for (int i = 0; i < NUM_ARROWS; i++) {
        arrows[i].x = screenWidth + 100;
        arrows[i].y = screenHeight / 2;
        arrows[i].speed = 5;
        arrows[i].color = GetRandomValue(0, 3);
        arrows[i].flag = 0;
        arrows[i].spawnTime = times[i];
    }


    while (!WindowShouldClose()) {
        UpdateArrows(arrows, NUM_ARROWS);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawLine(0, screenHeight / 2 - 30, screenWidth, screenHeight / 2 - 30, WHITE);
        DrawLine(0, screenHeight / 2 + 30, screenWidth, screenHeight / 2 + 30, WHITE);
        DrawCircle(center.x,center.y, 30, WHITE);

        DrawArrows(arrows, NUM_ARROWS);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
