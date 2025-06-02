#include "arrow.h"

// float currentTime = GetTime();
void DrawArrows(Arrow arrows[], int count) {
    for (int i = 0; i < count; i++) {
        if (arrows[i].flag == 1) { // só desenha se estiver ativa
            switch (arrows[i].color)
            {
                case 0:
                    DrawCircle(arrows[i].x, arrows[i].y, 30, RED);
                    break;
                case 1:
                    DrawCircle(arrows[i].x, arrows[i].y, 30, GREEN);
                    break;
                case 2:
                    DrawCircle(arrows[i].x, arrows[i].y, 30, BLUE);
                    break;       
                case 3:
                    DrawCircle(arrows[i].x, arrows[i].y, 30, GRAY);
                    break;
            }
        }
    }
}

void UpdateArrows(Arrow arrows[], int count) {
    float currentTime = GetTime();

    for (int i = 0; i < count; i++) {
        if (!arrows[i].flag && currentTime >= arrows[i].spawnTime) {
            arrows[i].flag = 1; // ativa a seta quando o tempo chega
        }

        if (arrows[i].flag) {
            arrows[i].x -= arrows[i].speed;

            if (arrows[i].x < -30) {
                arrows[i].flag = 0;
            }
        }
    }
}
