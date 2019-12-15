#include "tower.h"
#include <cmath>


Tower::Tower(int n) {
    self_rect = TowerPosition[n];
}

#define DILUTE 2

void Tower::attack() {  //attack 由render掌管
    PicOrder / DILUTE < 5 ? SDL_RenderCopy(gRenderer, MtowerTexture[(int) (PicOrder / DILUTE)], nullptr, &self_rect) :
    SDL_RenderCopy(gRenderer, Texture_Now, nullptr, (&self_rect));
    SDL_RenderCopy(gRenderer, MtowerManTexture[(int) (PicOrder / DILUTE)], nullptr, &Man_rect);
    if ((float) PicOrder / DILUTE == 5) {
        game->Bullet_Array[game->Bullet_point++] = new Bullet(target, (&self_rect)->x + 38, (&self_rect)->y + 0);
    }
    PicOrder / DILUTE < 9 ? PicOrder++ : PicOrder = 0, target = nullptr;
}

void Tower::buildTower(TowerType tower_type) {
    switch (tower_type) {
        case Arrow:
            break;
        case Barracks:
            break;
        case Canon:
            Ctower_Init();
            break;
        case Magic:
            Mtower_Init();
            break;
    }
    Update_Rect(&self_rect);
}


void Tower::Update_Rect(SDL_Rect *r) {
    int w, h;
    SDL_QueryTexture(Texture_Now, nullptr, nullptr, &w, &h);
    HtoW = (float) h / w;
    h = TowerWidth * HtoW;
    r->y = r->y + r->h - h + 5;
    r->h = h;
}

void Tower::render() {
    if (target == nullptr || CDstart > 0) {
        CDstart--;
        SDL_RenderCopy(gRenderer, Texture_Now, nullptr, &self_rect);
        if (type == Magic) {
            SDL_RenderCopy(gRenderer, Man_in_Tower, nullptr, &Man_rect);
        }
    } else {
        attack();
    }
}

bool Tower::in_range(SDL_Rect target) {
    return sqrt((target.x - attackX) * (target.x - attackX) + (target.y - attackY) * (target.y - attackY)) < 166;
}

void Tower::Mtower_Init() {
    game->money -= 500;
    type = Magic;
    Texture_Now = TowerStaticTexture[1];
    SDL_QueryTexture(Texture_Now, nullptr, nullptr, &(Center.x), &(Center.y));
    Center.x /= 2;
    Center.y /= 2;
    Man_rect = self_rect;
    Man_rect.x += 30;
    Man_rect.y -= 18;
    Man_rect.h = 30;
    Man_rect.w = 30;
    attackX = (&self_rect)->x + 44;
    attackY = (&self_rect)->y + 12;
    Man_in_Tower = MtowerManTexture[0];
}

void Tower::Ctower_Init() {
    type = Canon;
    Texture_Now = TowerStaticTexture[2];
}

void Tower::shoot() {

}
