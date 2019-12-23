#ifndef START_MAIN_H
#define START_MAIN_H
//本文件负责统筹所有.h头文件，并载入窗口对象。
#include <iostream>
#include "enemy.h"
#include "tower.h"
#include "Game.h"
#include "bullet.h"
#include "shell.h"
//#include "picture_change.h"
#include <ctime>
#include <random>


SDL_Point Mouse_Point;

//声明：有关游戏逻辑的函数，函数命名一律以“名词——动词（）”方式进行。
SDL_Window *gWindow = nullptr;  //窗体
SDL_Texture *map = nullptr;

SDL_Texture *startbg;
SDL_Texture *starticon;
SDL_Texture *pause_pic;
SDL_Texture *re;
SDL_Texture *statef;
SDL_Texture *numf[10];
SDL_Texture *defeat;
SDL_Texture *victory;
SDL_Texture *again;
SDL_Texture *quit;
SDL_Texture *choice_ring[3];
SDL_Texture *nextwave;

std::string mapfile = R"(..\image\map_demo.png)";
std::string towergroundfile = R"(..\image\raw.png)";
std::string startbgfile = R"(..\image\startbg_demo.png)";
//std::string starticonfile = R"(..\image\starticon.png)";
std::string pausefile = R"(..\image\pause.png)";
std::string refile = R"(..\image\re.png)";
std::string statefile = R"(..\image\state.png)";
std::string numffile[10] = {R"(..\image\num\0.png)", R"(..\image\num\1.png)", R"(..\image\num\2.png)",
                            R"(..\image\num\3.png)", R"(..\image\num\4.png)", R"(..\image\num\5.png)",
                            R"(..\image\num\6.png)", R"(..\image\num\7.png)", R"(..\image\num\8.png)",
                            R"(..\image\num\9.png)"};
std::string defeatfile = R"(..\image\defeat.png)";
std::string victoryfile = R"(..\image\victory.png)";
std::string againfile = R"(..\image\again.png)";
std::string quitfile = R"(..\image\quit.png)";
std::string choicefile[3] = {R"(..\image\choice.png)",R"(..\image\choice1.png)",R"(..\image\choice2.png)"};
std::string nextwavefile = R"(..\image\wave.png)";

SDL_Rect WayPoint[20] = {1020, 290, 35, 30};
SDL_Rect startpos = {374,390,252,123};
SDL_Rect difficultypos[3] = {38, 355, 262, 311,
                          349, 353, 270, 291,
                          673, 326, 291, 343};

SDL_Rect pausepos = {900,30,50,46};
SDL_Rect repos = {353,374,295,109};
SDL_Rect statepos = {30,30,276,96};
SDL_Rect lifepos[3] = {104, 50, 13, 19,
                       117, 50, 13, 19,
                       130, 50, 13, 19};
SDL_Rect moneypos[4] = {200,50,13,19,
                        213,50,13,19,
                        226,50,13,19,
                        239,50,13,19};
SDL_Rect wavepos[2] = {182,92,13,19,
                       212,92,13,19};
SDL_Rect resultpos[3] = {250,190,500,172,
                         340,400,320,95,
                         340,540,320,95};

SDL_Rect choice_icon[choice_total] = {
        36, 0, 43, 47,
        36, 100, 43, 47
};
SDL_Rect nextwavepos = {938,281,55,40};

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 857;

bool Quit = false;
bool pause=false;
int menu_open=-1;

SDL_Event e;
auto *game = new Game;

Uint32 _time, start;

//SDL_Surface *loadSurface(const std::string &path);

SDL_Texture *loadTexture(const std::string &path);

bool loadTextures(std::string *picture_path, SDL_Texture **texture_array, int n);

//SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];   //必须放在main.cpp里

SDL_Renderer *gRenderer = nullptr;


#endif //START_MAIN_H
