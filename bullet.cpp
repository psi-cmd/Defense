//
// Created by longbang-cmd on 2019/12/5.
//

#include "bullet.h"


Bullet::Bullet(Enemy **tar, int x, int y) {
    target = tar;
    Pos.x = x;
    Pos.y = y;
    texture = MBullet_Texture;
}

void Bullet::render() {
    move();
    SDL_RenderCopy(gRenderer, texture, nullptr, &Pos);
}

void Bullet::move() {
    if (*target == nullptr){
        delete this;
        game->Bullet_Array[game->Bullet_Num] = nullptr;
        return;
    }
    if (abs(Pos.x - (*target)->Pos.x) < VEL && abs(Pos.y - (*target)->Pos.y) < VEL) {
        (*target)->Health -= 10;
        delete this;
        game->Bullet_Array[game->Bullet_Num] = nullptr;
        return;
    }
    float xtoy = (Pos.x - (*target)->Pos.x) / (Pos.y - (*target)->Pos.y);
    VelY = sqrt(VEL * VEL / (1 + xtoy * xtoy));
    ((*target)->Pos.y - Pos.y) < 0 ? VelY = -VelY : 0;
    VelX = VelY * xtoy;
    Pos.x += VelX;
    Pos.y += VelY;
}


