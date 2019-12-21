//
// Created by longbang-cmd on 2019/12/5.
//

#ifndef START_BULLET_H
#define START_BULLET_H

std::string MBullet_Pic = R"(..\image\bullet.png)";
SDL_Texture *MBullet_Texture = nullptr;

std::string smogfile[5] = {R"(..\image\smog0.png)",R"(..\image\smog1.png)",R"(..\image\smog2.png)",R"(..\image\smog3.png)",R"(..\image\smog4.png)"};
SDL_Texture *smog[5];
SDL_Rect smogpos={0,0,12,16};

std::string Smoke_Pic[10] = {
        R"(..\image\smoke0.png)",
        R"(..\image\smoke1.png)",
        R"(..\image\smoke2.png)",
        R"(..\image\smoke3.png)",
        R"(..\image\smoke4.png)",
        R"(..\image\smoke5.png)",
        R"(..\image\smoke6.png)",
        R"(..\image\smoke7.png)",
        R"(..\image\smoke8.png)"
};

SDL_Texture *Smoke_Texture[10];

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
