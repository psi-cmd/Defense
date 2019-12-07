//
// Created by longbang-cmd on 2019/12/5.
//

#ifndef START_BULLET_H
#define START_BULLET_H

std::string MBullet_Pic = R"(..\image\bullet.png)";
SDL_Texture *MBullet_Texture = nullptr;

class Bullet {
public:
    int VEL = 8;

    Bullet(Enemy **tar, int x, int y);

    void render();

    void move();

private:
    Enemy **target;  //二级指针防止飞弹
    SDL_Texture *texture;
    float VelX;
    float VelY;
    SDL_Rect Pos = {0, 0, 16, 15};  //位置

};

#endif //START_BULLET_H
