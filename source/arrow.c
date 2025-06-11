#include "arrow.h"
#include"user.h"
#include<stdio.h>

//Dinamic allocation of arrows from a file, before the user get  the press the option
Arrow* loadFromFile(const char* filename, int* a_count) {
    FILE* file = fopen(filename, "r");
    if(file ==NULL){
        printf("Erro ao abrir o arquivo %s\n", filename);
        *a_count = 0;
        return NULL;
    }

    int count = 0;
    float tempTime;
    int tempDir;

    //line counts for dinamic allocation
    while (fscanf(file,"%f %d", &tempTime, &tempDir) == 2) {
        count++;
    }

    if (count==0) {
        printf("Nenhuma seta encontrada no arquivo %s\n", filename);
        fclose(file);
        *a_count = 0;
        return NULL; 
    }
    Arrow* arrows = (Arrow*)malloc(count * sizeof(Arrow));
    if (arrows == NULL) {
        printf("Erro ao alocar memoria para as setas\n");
        fclose(file);
        *a_count = 0;
        return NULL; 
    }

    rewind(file);
    int i =0;
    while (fscanf(file, "%f %d", &tempTime, &tempDir) == 2) {
        arrows[i].direction = tempDir;
        arrows[i].flag = 0; 
        arrows[i].speed = 7; 
        arrows[i].x = 1380;
        arrows[i].y = 400;
        arrows[i].spawnTime = tempTime; 
        i++;
    }
    fclose(file);
    *a_count = count;        
    return arrows; 
    
    //so pra lembrar:: no fim o a count é o numero de setas que foram carregadas do arquivo e loop do while vai alocar dinamicamente o numero de setas que foram carregadas do arquivo com tempo e orientação deifinidas no txt
}

void DrawArrows(Arrow *arrows, int count, Texture2D arrowsTexture[]) {
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

void  UpdateArrows(Arrow *arrows, int count, Vector2 userCenter, float songTimer, int *score) {
 // Variável para armazenar a pontuação
    //dor de cabeça da peeeeeeeeeeeeeeste
    for (int i = 0; i < count; i++) {
        // Se a seta já foi acertada (flag=2), ignore-a completamente.
        if (arrows[i].flag == 2) {
            continue;
        }

        // Ativa a seta se ela estiver inativa (flag=0) e seu tempo de spawn chegou.
        //troquei o current time por songTimer, que é o tempo da musica
        if (arrows[i].flag == 0 && songTimer >= arrows[i].spawnTime) {
            arrows[i].flag = 1;
        }

        // Se a seta estiver ativa (flag=1), processa sua lógica.
        if (arrows[i].flag == 1) {
            // Verifica se o evento do usuário a desativa (acerto).
            if (userEventTrigger(&arrows[i], userCenter) == arrows[i].direction) {
                // Seta foi acertada! Mude o estado para 2 (permanentemente desativada).
                *score+=10;
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

