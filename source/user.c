#include"user.h"

int  userEventTrigger(Arrow * arrow,Vector2 center){
    int userClick;
    int colision =CheckCollisionCircles((Vector2){center.x,center.y},30,(Vector2){arrow->x,arrow->y},30)? 1:0;
    if (colision && IsKeyDown(KEY_UP))
    {
        return 1;
    }
    if (colision && IsKeyDown(KEY_LEFT))
    {
        return 2;
    }
    if (colision && IsKeyDown(KEY_DOWN))
    {
        return 3;
    }
    if (colision && IsKeyDown(KEY_RIGHT))
    {
        return 4;
    }
    return 0;
    
}