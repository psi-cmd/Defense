//
// Created by longbang-cmd on 2019/12/3.
//

#include "main.h"
#include "Game.h"
#include <cmath>

Game::Game() {
    for (int i = 0; i < 256; Enemy_Array[i] = nullptr, ++i);
//    for (int j = 0; j < 15; Tower_Array[j] = nullptr, ++j);
    for (int j = 0; j < 256; Bullet_Array[j] = nullptr, ++j);
}


void Game::Enemy_Wave() {
    if (Enemy_Count && SDL_GetTicks() - Refresh_Tick >= Interval) {
        Refresh_Tick = SDL_GetTicks();
        Enemy_Add(Enemy1);
        Enemy_Count--;
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
                    Enemy_Array[Enemy_Num - 1] = new class Enemy1((int) rand()%16);
                    break;
            }
            return;
        }
    }
}


void Game::Tower_init() {
    for (int i = 0; i < Tower_point; ++i) {
        Tower_Array[i] = new Tower(i);
    }
}

void Game::Exit_Game(int n) {
    Quit = true;
}

void Game::Render() {
    Print_Dec(life, lifepos);
    Print_Dec(money, moneypos);
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
    do {
        if (Bullet_Array[Bullet_Num] != nullptr) {
            Bullet_Array[Bullet_Num]->render();
        }
        Bullet_Num++;
    } while (Bullet_Num != 0);

}

void Game::Tower_Build(TowerType type, int x, int y) {
    for (int i=0; i<Tower_point; ++i){
        if (In_Rect(x, y, Tower_Array[i]->rect)){
            Tower_Array[i]->buildTower(type);
            return;
        }
    }
}


void Game::Detect() {
    for (int i = 0; i < Tower_point; ++i) {
        if (Tower_Array[i]->type != None) {
            Enemy *Is_target = nullptr;
            int Distance = -100000, temp;
            for (int j = 0; j < 256; ++j) {
                if (Enemy_Array[j] != nullptr &&
                    !Enemy_Array[j]->dying &&
                    Tower_Array[i]->in_range(Enemy_Array[j]->Pos)) {
                    Enemy_Array[j]->Distance_Covered > Distance ? Is_target = Enemy_Array[j], Distance = Enemy_Array[j]->Distance_Covered : 0;
                    /*temp = (Enemy_Array[j]->Pos.x - Tower_Array[i]->attackX) *
                           (Enemy_Array[j]->Pos.x - Tower_Array[i]->attackX) +
                           (Enemy_Array[j]->Pos.y - Tower_Array[i]->attackY) *
                           (Enemy_Array[j]->Pos.y - Tower_Array[i]->attackY);
                    Enemy_Array[j]->escaping(Tower_Array[i]->attackX, Tower_Array[i]->attackY) ? 0 : temp = -temp;
                    temp > Distance ? Distance = temp, Is_target = Enemy_Array[j] : nullptr;*/
                    Tower_Array[i]->target = Is_target;
                }
            }
        }
    }

}




