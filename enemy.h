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

enum State {
    IN,
    OUT
};

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
    Enemy(int n);

//    const SDL_Rect FigSize = {0, 0, 35, 30};  //敌军图片大小
    //Maximum axis velocity of the dot
    float VEL = 1;  //因为逻辑问题，现在它实际上是个平方

//    ~Enemy();
    void move(struct circle Circle);  //敌军移动
    void move_control();
    void render();  //显示刷新
    virtual void death();  //去世操作
    bool overline(State state);
    int Health{};
    SDL_Rect Pos{};  //位置
    double Distance_Covered = 0;
    bool dying = false;
    SDL_Point Center{};


private:

    int circle_num = 0;
    bool in_circle = false;  //是否进入圆范围内
    bool exiting_circle = false;
    bool flat_overed = false;
    double judgement = 0;

protected:
    int PicOrder = 0;
    double VelX{}, VelY=0;  //速度
    double X{}, Y{};
    int Picture_max{};
    SDL_Texture **Texture_Set{};
    int life_cost=1;
};

class Enemy1 : public Enemy {
public:
    Enemy1(int n);
    void death();
private:
    std::string *Texture{};
};


#endif //START_ENEMY_H
