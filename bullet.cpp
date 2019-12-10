//
// Created by longbang-cmd on 2019/12/5.
//

#include "bullet.h"

float visual;


Bullet::Bullet(Enemy *tar, int x, int y) {
    target = tar;
    Pos.x = x;
    Pos.y = y;
    texture = MBullet_Texture;
}

void Bullet::render() {
    move();
    if (exist)
        SDL_RenderCopy(gRenderer, texture, nullptr, &Pos);
    else {
        delete this;
        game->Bullet_Array[game->Bullet_Num] = nullptr;
    }
}

void Bullet::move() {
    /* if (target == nullptr){
         delete this;
         game->Bullet_Array[game->Bullet_Num] = nullptr;
         return;
     }*/
    if (abs(Pos.x - (target)->Pos.x) < VEL && abs(Pos.y - (target)->Pos.y) < VEL) {
        (target)->Health -= 10;
        exist = false;
        return;
    }
    float xtoy;
    if (Pos.y - (target)->Pos.y < 1000 && Pos.x - (target)->Pos.x < 1000 && -1000 < Pos.y - (target)->Pos.y &&
        -1000 < Pos.x - (target)->Pos.x && (Pos.y - (target)->Pos.y) != 0)
        xtoy = (Pos.x - (target)->Pos.x) / (Pos.y - (target)->Pos.y);
    else exist = false;
    VelY = sqrt(VEL * VEL / (1 + xtoy * xtoy));
    ((target)->Pos.y - Pos.y) < 0 ? VelY = -VelY : 0;
    visual = VelY;
    VelX = VelY * xtoy;
    Pos.x += VelX;
    Pos.y += VelY;
}

/*void Bullet::nearest() {
    for (int i=0; i<255; ++i){
        game->Enemy_Array[i]->Pos.x
    }
}*/


