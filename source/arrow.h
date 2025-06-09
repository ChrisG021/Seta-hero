#ifndef ARROW_H
#define ARROW_H

#include "raylib.h"

typedef struct Arrow{
    float x, y;
    float speed;
    int direction;
    int flag;
    float spawnTime;
} Arrow;

void DrawArrows(Arrow arrows[], int count, Texture2D arrowsTexture[]);
void UpdateArrows(Arrow arrows[], int count,Vector2 userCenter);

#endif
