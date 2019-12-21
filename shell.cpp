#include "shell.h"
#include <cmath>

float visual2;

Shell::Shell(Enemy **tar, int x, int y) {
    ptarget = tar;
    target = *tar;
    Pos.x = x;
    Pos.y = y;
    texture = CShell_Texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &(Center.x), &(Center.y));
    Center.x /= 2;
    Center.y /= 2;
}

void Shell::render() {
    move();
    if (exist) {
        SDL_RenderCopyEx(gRenderer, texture, nullptr, &Pos, angle, &Cen, SDL_FLIP_NONE);
    }
    else {
        smogpos.x=Pos.x-10;
        smogpos.y=Pos.y-5;
        for (counter=0; counter < 10; counter++){
            SDL_RenderCopy(gRenderer, Smoke_Texture[counter], nullptr, &smogpos);
        }
//        SDL_RenderCopy(gRenderer, smog[0], nullptr, &smogpos);
//        SDL_RenderCopy(gRenderer, texture, nullptr, &target->Pos);
        if (counter==10) {
            delete this;
            game->Shell_Array[game->Shell_Num] = nullptr;
        }
    }
}


void Shell::move() {
    if (*ptarget == nullptr || (**ptarget).dying){
        smogpos.x=(target)->Pos.x-2;
        smogpos.y=(target)->Pos.y-5;
        SDL_RenderCopy(gRenderer, smog[4], nullptr, &smogpos);
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
    visual2 = VelY;
    VelX = VelY * xtoy;
    Pos.x += VelX;
    Pos.y += VelY;
    angle+=20;

}

void Shell::nearest() {
    int near = 1000000, temp, pot_target=-1,k=0;
    for (int i=0; i<256; ++i){
        if (game->Enemy_Array[i]) {
            temp = (game->Enemy_Array[i]->Pos.x - Pos.x) * (game->Enemy_Array[i]->Pos.x - Pos.x) +
                   (game->Enemy_Array[i]->Pos.y - Pos.y) * (game->Enemy_Array[i]->Pos.y - Pos.y);
            temp < near && !game->Enemy_Array[i]->dying ? near = temp, pot_target = i : 0;
        }
    }
    if (pot_target == -1) {
        exist = false;
        return;
    }

    target = game->Enemy_Array[pot_target];
    ptarget = &game->Enemy_Array[pot_target];
}