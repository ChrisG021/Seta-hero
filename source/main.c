#include "raylib.h"
#include"user.h"
#include "arrow.h"
#include<stdio.h>


#define screenWidth 1280
#define screenHeight 800
#define NUM_ARROWS 10


typedef struct Point
{
    float x,y;
}Point;

int main() {
    int newSize = 64;

    InitWindow(screenWidth, screenHeight, "Seta Hero");
    SetTargetFPS(60);

    Texture2D arrowsTexture[4];
    Image img1 = LoadImage("content/arrows/up.png"); 
    ImageResize(&img1, newSize, newSize);
    arrowsTexture[0] = LoadTextureFromImage(img1);
    UnloadImage(img1);
    Image img2 = LoadImage("content/arrows/left.png");
    ImageResize(&img2, newSize, newSize);
    arrowsTexture[1] = LoadTextureFromImage(img2);
    UnloadImage(img2);
    Image img3 = LoadImage("content/arrows/down.png");
    ImageResize(&img3, newSize, newSize);
    arrowsTexture[2] = LoadTextureFromImage(img3);
    UnloadImage(img3);
    Image img4 = LoadImage("content/arrows/right.png");
    ImageResize(&img4, newSize, newSize);
    arrowsTexture[3] = LoadTextureFromImage(img4);
    UnloadImage(img4);

    Arrow arrows[NUM_ARROWS]={
        {1380,400,7,GetRandomValue(1,4),0,0.5f},
        {1380,400,7,GetRandomValue(1,4),0,1.0f},
        {1380,400,7,GetRandomValue(1,4),0,2.0f},
        {1380,400,7,GetRandomValue(1,4),0,2.3f},
        {1380,400,7,GetRandomValue(1,4),0,2.6f},
        {1380,400,7,GetRandomValue(1,4),0,3.0f},
        {1380,400,7,GetRandomValue(1,4),0,3.5f},
        {1380,400,7,GetRandomValue(1,4),0,4.0f},
        {1380,400,7,GetRandomValue(1,4),0,4.5f},
        {1380,400,7,GetRandomValue(1,4),0,4.8f},
    };

    Point center;
    center.x = 200;
    center.y = screenHeight/2;

    while (!WindowShouldClose()) {
        UpdateArrows(arrows, NUM_ARROWS,(Vector2){center.x,center.y});

        BeginDrawing();
        ClearBackground(WHITE);

        DrawLine(0, screenHeight / 2 - 32, screenWidth, screenHeight / 2 - 32, BLACK);
        DrawLine(0, screenHeight / 2 + 32, screenWidth, screenHeight / 2 + 32, BLACK);
        DrawCircle(center.x,center.y, 32, BLACK);

        DrawArrows(arrows, NUM_ARROWS,arrowsTexture);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
