#include "tower.h"
#include <cmath>


Tower::Tower(int n) {
    rect = &TowerPosition[n];
}

#define DILUTE 2

void Tower::attack() {  //attack 由render掌管
    PicOrder / DILUTE < 5 ? SDL_RenderCopy(gRenderer, MtowerTexture[(int) (PicOrder / DILUTE)], nullptr, rect) :
    SDL_RenderCopy(gRenderer, Texture_Now, nullptr, rect);
    SDL_RenderCopy(gRenderer, MtowerManTexture[(int) (PicOrder / DILUTE)], nullptr, &Man_rect);
    if ((float) PicOrder / DILUTE == 5) {
        game->Bullet_Array[game->Bullet_point++] = new Bullet(&target, rect->x + 38, rect->y + 0);
    }
    PicOrder / DILUTE < 9 ? PicOrder++ : PicOrder = 0, target = nullptr;
}

void Tower::buildTower(TowerType tower_type) {
    switch (tower_type) {
        case None:
            break;
        case Arrow:
            break;
        case Barracks:
            break;
        case Canon:
            break;
        case Magic:
            Mtower_Init();
            break;
    }
    Update_Rect(rect);
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
        SDL_RenderCopy(gRenderer, Texture_Now, nullptr, rect);
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
    type = Magic;
    Texture_Now = TowerStaticTexture[1];
    Man_rect = *rect;
    Man_rect.x += 30;
    Man_rect.y -= 18;
    Man_rect.h = 30;
    Man_rect.w = 30;
    attackX = rect->x + 44;
    attackY = rect->y + 12;
    Man_in_Tower = MtowerManTexture[0];
}

void Tower::shoot() {

}
