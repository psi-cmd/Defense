/*
// * 进度：
// * 窗口就绪，塔位置就绪，正在进行图片刷新机制。
// * 刷新ok，开始放置
// */
//总启动文件，统筹所有.cpp文件，完成初始化，窗口载入和各类图片载入功能。即游戏底层。
#include <SDL_image.h>
#include <SDL.h>
#include <string>
//#include <SDL_ttf.h>
#include "main.h"
#include "enemy.cpp"
#include "tower.cpp"
#include "game_logic.cpp"
#include "Game.cpp"
#include "bullet.cpp"

using namespace std;

bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {  //初始化可视媒体模块
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        success = false;
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            cout << "Warning: Linear texture filtering not enabled!" << endl;
        }
        gWindow = SDL_CreateWindow("Defense-Design", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);  //创建窗体
        if (gWindow == nullptr) {
            cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);  //对screen创造刷新器
            if (gRenderer == nullptr) {
                cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
                success = false;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
                    success = false;
                }
            }
        }
    }

    /*if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        success = false;
    }*/
    return success;
}

void close() {
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    SDL_DestroyTexture(map);  //干掉图片
    map = nullptr;  //释放指针
    SDL_DestroyWindow(gWindow);  //干掉窗口
    gWindow = nullptr;  //释放指针
    IMG_Quit();
    SDL_Quit();  //退出
}

SDL_Texture *loadTexture(const std::string &path) {  //最终要演变为一个全局加载函数。
    SDL_Texture *newTexture = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        cout << "Unable to load image %s! SDL_image Error: " << path.c_str() << IMG_GetError() << endl;
    } else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == nullptr) {
            cout << "Unable to create texture from %s! SDL Error: " << path.c_str() << SDL_GetError() << endl;
        }
        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

bool loadTextures(std::string *picture_path, SDL_Texture **texture_array, int n) {
    for (int i = 0; i < n; ++i) {
        texture_array[i] = loadTexture(picture_path[i]);
        SDL_SetTextureBlendMode(texture_array[i], SDL_BLENDMODE_BLEND);
        if (texture_array[i] == nullptr) {
            printf("Failed to load texture image!\n");
            return false;
        }
    }
    return true;
}


bool loadMedia() {
    loadSingle();
    int success = true;
    loadTextures(DevilPicture, DevilTexture, Enemy1_pic);
    loadTextures(MtowerPicture, MtowerTexture, MTower_pic);
    loadTextures(MtowerMan_pic, MtowerManTexture, MTower_Man_pic);
    TowerStaticTexture[1] = MtowerTexture[0];
    return success;
}

int WinMain(int argc, char **argv) {
    srand(time(nullptr));
    if (!init()) {
        cout << "failed to initialize!" << endl;
    } else {
        if (!loadMedia()) {
            cout << "Failed to load media!" << endl;
        }  //所有显示都给渲染器了。
    }
    game->Tower_init();
    start = _time = SDL_GetTicks();
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, startbg, nullptr, nullptr);  //渲染器开始背景
    SDL_RenderCopy(gRenderer, starticon, nullptr, &startpos);  //渲染器开始按钮
    while (!Quit)   //游戏进入界面循环
    {
        if (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {  //按窗口右上角的叉
                Quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                SDL_GetMouseState(&(Mouse_Point.x), &(Mouse_Point.y));
                if (SDL_PointInRect(&Mouse_Point, &startpos)) break;
            }
        }
        SDL_RenderPresent(gRenderer);
    }
    while (!Quit) {  //游戏主循环
        while (SDL_PollEvent(&e) != 0) {  //事件池，没事就返回0
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {  //按窗口右上角的叉
                Quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN || e.key.keysym.sym == SDLK_p) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&(Mouse_Point.x), &(Mouse_Point.y));
                    if (SDL_PointInRect(&Mouse_Point, &pausepos)) {
                        _time = SDL_GetTicks() - _time;
                        pause = true;
                        SDL_RenderCopy(gRenderer, re, nullptr, &repos);
                        SDL_RenderPresent(gRenderer);
                    }
                    game->Tower_Build(Magic, (Mouse_Point.x), (Mouse_Point.y));
                }
            }
            while (!Quit && pause) {
                if (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) Quit = true;
                    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&(Mouse_Point.x), &(Mouse_Point.y));
                        if (SDL_PointInRect(&Mouse_Point, &repos)) {
                            _time = SDL_GetTicks() - _time;
                            pause = false;
                            break;
                        }
                    }
                }
            }
        }
        if (SDL_GetTicks() - _time >= 60) {
            _time = SDL_GetTicks();
            refresh();
        }
    }
    close();
    return 0;
}