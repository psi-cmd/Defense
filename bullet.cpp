//
// Created by longbang-cmd on 2019/12/5.
//

#include "bullet.h"

#include <cmath>

float visual;


Bullet::Bullet(Enemy **tar, int x, int y) {
    ptarget = tar;
    target = *tar;
    Pos.x = x;
    Pos.y = y;
    texture = MBullet_Texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &(Center.x), &(Center.y));
    Center.x /= 2;
    Center.y /= 2;
}

void Bullet::render() {
    move();
    if (exist)
        SDL_RenderCopy(gRenderer, texture, nullptr, &Pos);
    else {
        SDL_RenderCopy(gRenderer, texture, nullptr, &target->Pos);
        delete this;
        game->Bullet_Array[game->Bullet_Num] = nullptr;
    }
}

void Bullet::move() {
     if (*ptarget == nullptr || (**ptarget).dying){
         nearest();
         return;
     }
    float rX = Pos.x + Center.x - (target)->Pos.x - (target)->Center.x;
    float rY = Pos.y + Center.y - (target)->Pos.y - (target)->Center.y;
    if (abs(rX) < VEL && abs(rY) < VEL) {
        (target)->Health -= 10;
        exist = false;
        return;
    }
    float xtoy;
    if (rY < 1000 && rX < 1000 && -1000 < rY && -1000 < rX) {
        rY += 0.000001;
        xtoy = rX / rY;
    } else exist = false;
    VelY = std::sqrt(VEL * VEL / (1 + xtoy * xtoy));
    (rY) > 0 ? VelY = -VelY : 0;
    visual = VelY;
    VelX = VelY * xtoy;
    Pos.x += VelX;
    Pos.y += VelY;
}

void Bullet::nearest() {
    int near = 1000000, temp, pot_target=0;
    for (int i=0; i<255; ++i){
        if (game->Enemy_Array[i]) {
            temp = (game->Enemy_Array[i]->Pos.x - Pos.x) * (game->Enemy_Array[i]->Pos.x - Pos.x) +
                   (game->Enemy_Array[i]->Pos.y - Pos.y) * (game->Enemy_Array[i]->Pos.y - Pos.y);
            temp < near && !game->Enemy_Array[i]->dying ? near = temp, pot_target = i : 0;
        }
    }
    target = game->Enemy_Array[pot_target];
    ptarget = &game->Enemy_Array[pot_target];
}


