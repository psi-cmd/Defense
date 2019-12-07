#include "enemy.h"
#include <iostream>
#include <SDL.h>


Enemy::Enemy() {
    //Initialize the offsets
    Pos = WayPoint[0];
    //Initialize the velocity
    VelX = 1;
    VelY = 2;
    PicOrder = 0;
}



void Enemy::move() {
    Distance_Covered += VEL;
    Pos.x -= VelX;
//    Pos.y -= VelY;

}


void Enemy::render() {
    if (Health <= 0){
        death();
        return;
    }
    move();
    SDL_RenderCopy(gRenderer, Texture_Set[PicOrder / 2], nullptr, &Pos);
    PicOrder++;
    PicOrder = PicOrder % ((Picture_max - 2) * 2);
    //Update screen
}

void Enemy::death() {
    game->Enemy_Array[game->Enemy_Num] = nullptr;
    delete this;
}

bool Enemy::escaping(int x, int y){
    return (x - Pos.x) * (x - Pos.x) +
           (y - Pos.y) * (y - Pos.y) >
           (x - Pos.x - VelX) * (x - Pos.x - VelX) +
           (y - Pos.y - VelY) * (y - Pos.y - VelY);

}

/*Enemy::~Enemy() {
//    free(Pos);
}*/

Enemy1::Enemy1() {
    Texture_Set = DevilTexture;
    Picture_max = Enemy1_pic;
    Health = 30;
    VEL = 1;
}
