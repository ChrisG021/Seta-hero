#ifndef ARROW_H
#define ARROW_H

#include "raylib.h"

typedef struct Arrow{
    float x, y;
    float speed;
    int color;
    int flag;
    float spawnTime;
} Arrow;

void DrawArrows(Arrow arrows[], int count);
void UpdateArrows(Arrow arrows[], int count);

#endif
