/*
 * 包含敌军的图片
 * 以及敌军的类
 */

#include <iostream>
#include <SDL_image.h>
#include <SDL.h>

#ifndef START_ENEMY_H
#define START_ENEMY_H

#define Total 1  //敌军类总数
#define Enemy1_pic 6

enum Enemy_Type {
    Enemy1
};

std::string DevilPicture[Enemy1_pic] = {
        R"(..\image\eneR1.png)",
        R"(..\image\eneR2.png)",
        R"(..\image\eneR3.png)",
        R"(..\image\eneR4.png)",
        R"(..\image\enes.png)",
        R"(..\image\ened.png)"
};

SDL_Texture *DevilTexture[Enemy1_pic];

//std::string *Picture_Paths[Total] = {DevilPicture};

//SDL_Texture **Enemy_Textures[Total] = {DevilTexture};



class Enemy {
public:
//    const SDL_Rect FigSize = {0, 0, 35, 30};  //敌军图片大小
    //Maximum axis velocity of the dot
    float VEL = 1;

    Enemy();  //建构函数
//    ~Enemy();
    void move();  //敌军移动
    void render();  //显示刷新
    void death();  //去世操作
    bool escaping(int x, int y);
    int Health;
    SDL_Rect Pos;  //位置
    float Distance_Covered = 0;

private:
    int VelX, VelY=0;  //速度
    int PicOrder = 0;
protected:
    int Picture_max;
    SDL_Texture **Texture_Set;
};

class Enemy1 : public Enemy {
public:
    Enemy1();
private:
    std::string *Texture{};
};


#endif //START_ENEMY_H
