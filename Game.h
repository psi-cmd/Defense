#include "enemy.h"
#include "bullet.h"

#ifndef START_GAME_H
#define START_GAME_H


enum choice_icon{
    choice_Mtower,
    choice_Cannon,
    choice_sell,
    choice_total
};

bool icon_clicked(SDL_Rect *chosen_icon);
//是什么对象管什么事，不能让别人插手（指设定私有变量）
//game类响应鼠标事件，所管辖的其他类不得响应鼠标事件。

//auto cmp = [](Enemy E1, Enemy E2) { return E1.Distance_Covered > };
class Game  //控制怪刷新，对象array维护，删除。
{
public:
    Game();

    void Restart();
    void Enemy_Add(Enemy_Type n);

    void Enemy_Wave();

    void Tower_Build();

    void Exit_Game(int n);

    void Render();

    void Tower_init();

    void Detect();   //所有非用户事件产生器

    bool If_No_Enemy();


    unsigned char Enemy_Num = 0;
    int Tower_Num = 0;
    unsigned char Bullet_Num = 0;

    Enemy *Enemy_Array[256];
    Tower *Tower_Array[Tower_point];
    Bullet *Bullet_Array[256];

    unsigned char Bullet_point = 0; //指向下一个子弹空位
    int money = 2000;
    int life = 10;
    int Enemy_Count = 10;
    int win=false;
private:
    Uint32 Refresh_Tick = 0;
    int Interval = 2000;
};

/*class Menu
{
    Menu(SDL_Rect *attach);
public:
    SDL_Rect *attached;
    SDL_Rect *Mtower_icon;
    SDL_Rect *Cannon_icon;
    SDL_Rect *Sell_icon;
};*/
#endif //START_GAME_H
