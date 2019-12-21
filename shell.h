#ifndef TEST_SHELL_H
#define TEST_SHELL_H

std::string CShell_Pic = R"(..\image\shell.png)";
SDL_Texture *CShell_Texture = nullptr;

class Shell {
public:
    int VEL = 14;
    Shell(Enemy **tar,int x,int y);
    void render();
    void move();
    void nearest();
    bool exist = true;
    int counter=0;
private:
    Enemy **ptarget; //二级指针防止飞弹
    Enemy *target;
    SDL_Texture *texture;
    float VelX;
    float VelY;
    float angle=0;
    SDL_Point Center;
    SDL_Point Cen = {10,10}; //旋转中心
    SDL_Rect Pos = {0, 0, 20, 20};  //位置
};

#endif //TEST_SHELL_H
