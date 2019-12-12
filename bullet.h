//
// Created by longbang-cmd on 2019/12/5.
//

#ifndef START_BULLET_H
#define START_BULLET_H

std::string MBullet_Pic = R"(..\image\bullet.png)";
SDL_Texture *MBullet_Texture = nullptr;

class Bullet {
public:
    float VEL = 14;

    Bullet(Enemy **tar, int x, int y);

    void render();

    void move();

    void nearest();

    bool exist = true;

private:
    Enemy **ptarget; //二级指针防止飞弹
    Enemy *target;
    SDL_Point Center;
    SDL_Texture *texture;
    double VelX;
    double VelY;
    SDL_Rect Pos = {0, 0, 16, 15};  //位置

};

#endif //START_BULLET_H
