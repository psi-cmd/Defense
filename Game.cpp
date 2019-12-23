//
// Created by longbang-cmd on 2019/12/3.
//

#include "main.h"
#include "Game.h"
#include "enemy.h"
#include <cmath>

Game::Game() {
//    Enemy_Count = Enemy_num[0];
    for (int i = 0; i < 256; Enemy_Array[i] = nullptr, ++i);
//    for (int j = 0; j < 15; Tower_Array[j] = nullptr, ++j);
    for (int j = 0; j < 256; Bullet_Array[j] = nullptr, ++j);
    for (int j = 0; j < 256; Shell_Array[j] = nullptr, ++j);
    printf("");

}


void Game::Enemy_Wave() {
    if (Enemy_Count && SDL_GetTicks() - Refresh_Tick >= Interval) {
        Refresh_Tick = SDL_GetTicks();
        Enemy_Add(Enemy1);
        Enemy_Count--;
    } else {
        if (Wave < WAVE) {
            wave_timer == 0 ? wave_timer = 120, Enemy_Count = Enemy_num[Wave++] : 0;
            wave_timer--;
        } else if (If_No_Enemy()) {
            pause = true;
            game->win = true;
        }
    }
}

void Game::Enemy_Add(Enemy_Type n) {
    int Num_Temp = Enemy_Num;
    while (true) {
        if (Enemy_Array[Enemy_Num++] == nullptr) {
            if (Num_Temp == Enemy_Num) {
                std::cout << "New enemy allocate error: Please expand array length!" << std::endl;
                Exit_Game(1);
            }
            switch (n) {
                case Enemy1:
                    Enemy_Array[Enemy_Num - 1] = new class Enemy1((int) rand() % 16);
                    break;
            }
            return;
        }
    }
}


void Game::Tower_init() {
    for (int i = 0; i < Tower_point; ++i) {
        if (Tower_Array[i] && restart)
            delete Tower_Array[i];
        Tower_Array[i] = new Tower(i);
    }
}

void Game::Exit_Game(int n) {
    Quit = true;
}

void Game::Render() {
    Enemy_Num = 0;
    do {
        if (Enemy_Array[Enemy_Num] != nullptr) {
            Enemy_Array[Enemy_Num]->render();
        }
        Enemy_Num++;
    } while (Enemy_Num != 0);
    do {
        if (Tower_Array[Tower_Num] != nullptr) {
            Tower_Array[Tower_Num]->render();
        }
        Tower_Num++;
    } while (Tower_Num < Tower_point);
    Tower_Num = 0;
    Bullet_Num = 0;
    Shell_Num = 0;
    do {
        if (Bullet_Array[Bullet_Num] != nullptr) {
            Bullet_Array[Bullet_Num]->render();
        }
        Bullet_Num++;
    } while (Bullet_Num != 0);
    do {
        if (Shell_Array[Shell_Num] != nullptr) {
            Shell_Array[Shell_Num]->render();
        }
        Shell_Num++;
    } while (Shell_Num != 0);
}

void Game::Tower_Build() {
    if (menu_open >= 0 && Mouse_Point.x && Mouse_Point.y) {
        if (icon_clicked(&choice_icon[choice_Mtower])) {
            if (game->money < 100)
                return;
            Tower_Array[menu_open]->buildTower(Magic);
            Tower_Array[menu_open]->tower_level = 1;
        } else if (icon_clicked(&choice_icon[choice_Cannon])) {
            if (game->money < 125)
                return;
            Tower_Array[menu_open]->buildTower(Cannon);
            Tower_Array[menu_open]->tower_level = 1;
        }
        menu_open = -1;
        return;
    }
    for (int i = 0; i < Tower_point; ++i) {
        if (SDL_PointInRect(&Mouse_Point, &(Tower_Array[i]->self_rect)) && !Tower_Array[i]->tower_level) {
            menu_open = i;
        }
    }
}


void Game::Detect() {
    for (auto &i : Tower_Array) {
        if (i->type != None) {
            int Is_target = 0;
            int Distance = -100000;
            for (int j = 0; j < 256; ++j) {
                if (Enemy_Array[j] != nullptr &&
                    !Enemy_Array[j]->dying &&
                    i->in_range(Enemy_Array[j]->Pos)) {
                    Enemy_Array[j]->Distance_Covered > Distance
                    ? Is_target = j, Distance = Enemy_Array[j]->Distance_Covered : 0;
                    i->target = &Enemy_Array[Is_target];
                }
            }
        }
    }

}

void Game::Restart() {
    restart = true;
    game->win = false;
    for (int i = 0; i < 256; ++i) {
        if (Enemy_Array[i]) {
            delete Enemy_Array[i];
            Enemy_Array[i] = nullptr;
        }
        if (Bullet_Array[i]) {
            delete Bullet_Array[i];
            Bullet_Array[i] = nullptr;
        }
    }
    Tower_init();
    life = 6;
    money = 350;
    Wave = 0;
    wave_timer = 0;
    Enemy_Count = 0;
}

bool Game::If_No_Enemy() {
    bool temp = true;
    for (auto &i : Enemy_Array) {
        if (i)
            temp = false;
    }
    return temp;
}


bool icon_clicked(SDL_Rect *chosen_icon) {
    SDL_Rect temp = relative_rect(TowerPosition[menu_open].x - 10, TowerPosition[menu_open].y - 47, chosen_icon);
    return SDL_PointInRect(&Mouse_Point, &temp);
}

