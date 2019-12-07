#ifndef START_MAIN_H
#define START_MAIN_H
//本文件负责统筹所有.h头文件，并载入窗口对象。
#include <iostream>
#include "enemy.h"
#include "tower.h"
#include "Game.h"
#include "bullet.h"


//声明：有关游戏逻辑的函数，函数命名一律以“名词——动词（）”方式进行。
SDL_Window *gWindow = nullptr;  //窗体
SDL_Texture *map = nullptr;
std::string mapfile = R"(..\image\map_demo.png)";
std::string towergroundfile = R"(..\image\raw.png)";

SDL_Rect WayPoint[20] = {760, 290, 35, 30};


const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 857;

bool Quit = false;
SDL_Event e;
auto *game = new Game;

Uint32 time, start;

int TowerWidth = 90;
//SDL_Surface *loadSurface(const std::string &path);

SDL_Texture *loadTexture(const std::string &path);

bool loadTextures(std::string *picture_path, SDL_Texture **texture_array, int n);

//SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];   //必须放在main.cpp里

SDL_Renderer *gRenderer = nullptr;


#endif //START_MAIN_H
