#include "raylib.h"
#include"user.h"
#include "arrow.h"
#include<stdio.h>


#define screenWidth 1280
#define screenHeight 800


typedef struct Point
{
    float x,y;
}Point;

int main() {

    InitWindow(screenWidth, screenHeight, "Seta Hero");
    SetTargetFPS(60);
    InitAudioDevice();

    //======================IMAGE LOGIC=================
    int newSize = 64;
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
    //========================== settings =========================

    Point center;
    //initialize dinamic arrows
    // Arrows are initialized here, but they will be loaded from a file later
    Arrow *arrows = NULL;
    int NUM_ARROWS = 0;
    int score = 0;
    center.x = 200;
    center.y = screenHeight/2;
    float songTimer = 0.0f;
    

    //======================MUSIC LOGIC================= 
    // Load music based on the selected option
    int op =1 ;
    Music music;


    switch (op)
    {
    case 1:
        arrows = loadFromFile("content/music/wildflower.txt", &NUM_ARROWS);
        music = LoadMusicStream("content/music/wildflower.mp3");
        break;
    case 2:
        arrows = loadFromFile("content/music/Mortals.txt", &NUM_ARROWS);
        music = LoadMusicStream("content/music/Mortals.mp3");
        break;
    
    default:
        break;
    }
    
    // Verifica se o carregamento deu certo antes de continuar
    if (arrows == NULL) {
        printf("Nenhuma seta foi carregado. Saindo...\n");
        CloseWindow();
        return -1;
    }
    // Initialize music

    SetMasterVolume(0.5f); // Set volume to 50%
    // Load and play music  
    // Music music = LoadMusicStream("content/music/wildflower.mp3");
    PlayMusicStream(music);
    //===================================================


    // Main game loop
    while (!WindowShouldClose()) {

        UpdateArrows(arrows, NUM_ARROWS,(Vector2){center.x,center.y}, songTimer, &score);
        DrawRectangle(0,0,130,40,LIGHTGRAY);
        DrawText(TextFormat("Score: %d", score), 20, 15, 20, BLACK);
        UpdateMusicStream(music);
        songTimer+= GetFrameTime();

        BeginDrawing();
        ClearBackground((Color){224,224,224,255});

        DrawRectangle(0,screenHeight / 2 -37,screenWidth,5,LIGHTGRAY);

        DrawRectangle(0,screenHeight / 2 -32,screenWidth,64,GRAY);

        DrawRectangle(0,screenHeight / 2 +32,screenWidth,5,LIGHTGRAY);

        DrawCircle(center.x,center.y, 40, BLACK);
        DrawCircle(center.x,center.y, 32, WHITE);


        DrawArrows(arrows, NUM_ARROWS,arrowsTexture);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
