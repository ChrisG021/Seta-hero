#include "arrow.h"
#include"user.h"
#include<stdio.h>

// float currentTime = GetTime();
void DrawArrows(Arrow arrows[], int count, Texture2D arrowsTexture[]) {
    for (int i = 0; i < count; i++) {
        if (arrows[i].flag == 1) { // só desenha se estiver ativa
            
            Texture2D currentTexture;
            int posX, posY;

            switch (arrows[i].direction) {
                case 1:
                    currentTexture = arrowsTexture[0];
                    // Calcula a posição centralizada
                    posX = arrows[i].x - currentTexture.width / 2;
                    posY = arrows[i].y - currentTexture.height / 2;
                    DrawTexture(currentTexture, posX, posY, WHITE);
                    break;
                case 2:
                    currentTexture = arrowsTexture[1];
                    posX = arrows[i].x - currentTexture.width / 2;
                    posY = arrows[i].y - currentTexture.height / 2;
                    DrawTexture(currentTexture, posX, posY, WHITE);
                    break;
                case 3:
                    currentTexture = arrowsTexture[2];
                    posX = arrows[i].x - currentTexture.width / 2;
                    posY = arrows[i].y - currentTexture.height / 2;
                    DrawTexture(currentTexture, posX, posY, WHITE);
                    break;           
                case 4:
                    currentTexture = arrowsTexture[3];
                    posX = arrows[i].x - currentTexture.width / 2;
                    posY = arrows[i].y - currentTexture.height / 2;
                    DrawTexture(currentTexture, posX, posY, WHITE);
                    break;
            }
        }
    }
}

void UpdateArrows(Arrow arrows[], int count, Vector2 userCenter) {
    float currentTime = GetTime();

    //dor de cabeça da peeeeeeeeeeeeeeste
    for (int i = 0; i < count; i++) {
        // Se a seta já foi acertada (flag=2), ignore-a completamente.
        if (arrows[i].flag == 2) {
            continue;
        }

        // Ativa a seta se ela estiver inativa (flag=0) e seu tempo de spawn chegou.
        if (arrows[i].flag == 0 && currentTime >= arrows[i].spawnTime) {
            arrows[i].flag = 1;
        }

        // Se a seta estiver ativa (flag=1), processa sua lógica.
        if (arrows[i].flag == 1) {
            // Verifica se o evento do usuário a desativa (acerto).
            if (userEventTrigger(&arrows[i], userCenter) == arrows[i].direction) {
                // Seta foi acertada! Mude o estado para 2 (permanentemente desativada).
                arrows[i].flag = 2;
                continue; // Pula para a próxima seta.
            }

            // Move a seta.
            arrows[i].x -= arrows[i].speed;

            // Usar estado 2 aqui também previne que ela reapareça caso o tempo de spawn ainda seja válido.
            if (arrows[i].x < -30) {
                arrows[i].flag = 2; // Ou 0 se você quiser que ela possa ser reciclada no futuro.
                                   // Para um jogo de ritmo, 2 é mais seguro.
            }
        }
    }
}

