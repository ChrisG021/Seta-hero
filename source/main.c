#include "raylib.h"
#include "user.h"
#include "arrow.h"
#include <stdio.h>
#include <stdlib.h>

#define screenWidth 1280
#define screenHeight 800

typedef enum GameScreen { MENU = 0, GAMEPLAY, GAMEOVER } GameScreen;
GameScreen currentScreen = MENU;

typedef struct Point {
    float x, y;
} Point;

//==========settings value=============
Arrow *arrows = NULL;
int NUM_ARROWS = 0;
int score = 0;
float songTimer = 0.0f;
Music music;
int musicaSelecionada = -1;
Point center = {200, screenHeight / 2};
Texture2D arrowsTexture[4];
Texture2D logo;
//=====================================

float musicaDuration = 0.0f;

void InitGameplay(int opcao) {
    musicaSelecionada = opcao;
    score = 0;
    songTimer = 0.0f;

    if (arrows != NULL) {
        free(arrows);
        arrows = NULL;
    }

    switch (opcao) {
        case 1:
            arrows = loadFromFile("content/music/wildflower.txt", &NUM_ARROWS);
            music = LoadMusicStream("content/music/wildflower.mp3");
            break;
        case 2:
            arrows = loadFromFile("content/music/like_fire.txt", &NUM_ARROWS);
            music = LoadMusicStream("content/music/like_fire.mp3");
            break;
        case 3:
            arrows = loadFromFile("content/music/missing_life.txt", &NUM_ARROWS);
            music = LoadMusicStream("content/music/missing_life.mp3");
            break;
        default:
            break;
    }

    // Verifica se o carregamento deu certo antes de continuar
    if (arrows == NULL) {
        printf("Nenhuma seta foi carregado. Saindo...\n");
        CloseWindow();
        exit(1);
    }

     // Initialize music
    SetMasterVolume(0.5f);
    PlayMusicStream(music);
    musicaDuration = GetMusicTimeLength(music);
}

void UpdateGameplay() {
    UpdateMusicStream(music);
    songTimer += GetFrameTime();

    if (songTimer >= musicaDuration) {
        StopMusicStream(music);
        currentScreen = GAMEOVER;
        return;
    }

    // Main game loop
    UpdateArrows(arrows, NUM_ARROWS,(Vector2){center.x,center.y}, songTimer, &score);
        DrawRectangle(0,0,170,40,LIGHTGRAY);
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

void DrawMenu() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    int logoX = screenWidth / 2 - logo.width / 2;
    int logoY = 60;
    DrawTexture(logo, logoX, logoY, WHITE);

    const char *titulo = "Escolha uma música:";
    int tituloFontSize = 30;
    int tituloY = logoY + logo.height + 20;
    DrawText(titulo, screenWidth / 2 - MeasureText(titulo, tituloFontSize) / 2, tituloY, tituloFontSize, DARKGRAY);

    int botaoLargura = 250;
    int botaoAltura = 60;
    int botaoX = (screenWidth - botaoLargura) / 2;
    int espaco = 20;
    int inicioY = tituloY + 50;

    Rectangle botoes[3];
    for (int i = 0; i < 3; i++) {
        botoes[i] = (Rectangle){ botaoX, inicioY + i * (botaoAltura + espaco), botaoLargura, botaoAltura };
    }

    const char *labels[] = {"Wildflower - Billie E", "Like Fire - NSC", "Missing Life - NSC"};

    int fontSize = 24;
    for (int i = 0; i < 3; i++) {
        if (CheckCollisionPointRec(GetMousePosition(), botoes[i])) {
            DrawRectangleRec(botoes[i], LIGHTGRAY);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                InitGameplay(i + 1);
                currentScreen = GAMEPLAY;
            }
        } else {
            DrawRectangleRec(botoes[i], GRAY);
        }
        DrawText(labels[i], botaoX + (botaoLargura - MeasureText(labels[i], fontSize)) / 2, botoes[i].y + 15, fontSize, BLACK);
    }

    EndDrawing();
}

//Tela final
void DrawGameOver() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    const char *fim = "Fim de Jogo";
    const char *placar = TextFormat("Score: %d", score);

    int fontSize = 40;
    int y = screenHeight / 2 - 140;

    DrawText(fim, screenWidth / 2 - MeasureText(fim, fontSize) / 2, y, fontSize, DARKGRAY);
    DrawText(placar, screenWidth / 2 - MeasureText(placar, 30) / 2, y + 60, 30, BLACK);

    Rectangle botaoVoltar = { screenWidth / 2 - 150, y + 130, 300, 60 };

    if (CheckCollisionPointRec(GetMousePosition(), botaoVoltar)) {
        DrawRectangleRec(botaoVoltar, LIGHTGRAY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            currentScreen = MENU;
        }
    } else {
        DrawRectangleRec(botaoVoltar, GRAY);
    }

    const char *textoBotao = "Voltar ao menu";
    DrawText(textoBotao, botaoVoltar.x + (botaoVoltar.width - MeasureText(textoBotao, 24)) / 2, botaoVoltar.y + 15, 24, BLACK);

    EndDrawing();
}

int main(void) {
    InitWindow(screenWidth, screenHeight, "Seta Hero - Menu");
    SetTargetFPS(60);
    InitAudioDevice();

    int newSize = 64;
    Image img;

    //======================IMAGE LOGIC=================
    img = LoadImage("content/arrows/up.png");
    ImageResize(&img, newSize, newSize);
    arrowsTexture[0] = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("content/arrows/left.png");
    ImageResize(&img, newSize, newSize);
    arrowsTexture[1] = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("content/arrows/down.png");
    ImageResize(&img, newSize, newSize);
    arrowsTexture[2] = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("content/arrows/right.png");
    ImageResize(&img, newSize, newSize);
    arrowsTexture[3] = LoadTextureFromImage(img);
    UnloadImage(img);

    logo = LoadTexture("content/logo/setaherologo.png");

    // Logica das telas 
    while (!WindowShouldClose()) {
        switch (currentScreen) {
            case MENU:
                DrawMenu();
                break;
            case GAMEPLAY:
                UpdateGameplay();
                break;
            case GAMEOVER:
                DrawGameOver();
                break;
        }
    }

    // Finalização
    UnloadMusicStream(music);
    for (int i = 0; i < 4; i++) UnloadTexture(arrowsTexture[i]);
    UnloadTexture(logo);
    if (arrows != NULL) free(arrows);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
