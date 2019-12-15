#include "enemy.h"
#include "waypoint.h"
#include <iostream>
#include <SDL.h>
#include <cmath>


//bool watch;

bool Enemy::overline(State state) {
    circle c = Circles[circle_num];
    double temp;
    switch (state) {
        case IN:
            temp = c.Fa * (X - c.centerX) + c.Fb * (Y - c.centerY);
            if (judgement && judgement * temp <= 0) {
                if (c.over_flat && !flat_overed){
                    flat_overed = true;
                    break;
                }
                exiting_circle = true;
                judgement = 0;
                return true;
            }
            break;
        case OUT:
            temp = c.Sa * (X - c.centerX) + c.Sb * (Y - c.centerY);
            if (judgement && judgement * temp <= 0) {
                in_circle = true;
                flat_overed = false;
                judgement = 0;
                return true;
            }
            break;
    }
    judgement = temp;
    return false;
}

Enemy::Enemy(int n) {
    //Initialize the offsets
    Pos = WayPoint[0];
    Pos.y += n;
    //Initialize the velocity
    PicOrder = 0;
}


void Enemy::move_control() {
    if (exiting_circle) {
        circle_num++;
        in_circle = false;
        exiting_circle = false;
    }
    move(Circles[circle_num]);
}


void Enemy::move(struct circle Circle) {
    Distance_Covered += VEL;
//    Pos.x += VelX;
    if (in_circle) {
        double Vxtoy;
        int temp;
        temp = X - Circle.centerX > 0 ? -1 : 1;
        Vxtoy = -(Y - Circle.centerY) / (X - Circle.centerX + Circle.conter * 0.0000000001);
        VelY = temp * Circle.conter * sqrt(VEL / (1 + Vxtoy * Vxtoy));
        VelX = VelY * Vxtoy;
        overline(IN);
    } else overline(OUT);
    X += VelX;
    Y += VelY;
    Pos.x = (int) X;
    Pos.y = (int) Y;  //这里是为了记录具体位置。
}

void Enemy::render() {
    if (Health <= 0 || Pos.y > 870) {
        PicOrder < (Picture_max - 2) * 2 ? PicOrder = (Picture_max - 2) * 2 : 0;  //设定死亡动画只有两帧。
        dying = true;
        death();
        return;
    }
    move_control();
    SDL_RenderCopy(gRenderer, Texture_Set[PicOrder / 2], nullptr, &Pos);
    PicOrder++;
    PicOrder = PicOrder % ((Picture_max - 2) * 2);
    //Update screen
}

void Enemy::death() {
    game->Enemy_Array[game->Enemy_Num] = nullptr;
    delete this;
}


Enemy1::Enemy1(int n) : Enemy(n) {
    Texture_Set = DevilTexture;
    Picture_max = Enemy1_pic;
    SDL_QueryTexture(Texture_Set[0], nullptr, nullptr, &(Center.x), &(Center.y));
    Center.x /= 2;
    Center.y /= 2;
    Health = 30;
    VEL = 40;
    VelX = -VEL;
    X = Pos.x;
    Y = Pos.y;
    life_cost = 10;
}

void Enemy1::death() {
    if (PicOrder < Picture_max * 2) {
        SDL_RenderCopy(gRenderer, Texture_Set[PicOrder++ / 2], nullptr, &Pos);
        return;
    }
    if (Pos.y > 870)
        game->life -= life_cost;
    Enemy::death();
}
