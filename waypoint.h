#include "SDL.h"
#include "SDL_image.h"
#ifndef START_WAYPOINT_H
#define START_WAYPOINT_H

#define Rect_Num 12

struct circle {
    int conter;   //conter等于-1时为顺时针，等于1时为逆时针。
    int centerX;
    int centerY;
    float Sa, Sb;
    float Fa, Fb;
    bool over_flat;
} ;
// 顺/逆时针，圆心x， 圆心y，入圆线a， 入圆线b， 出圆线a， 出圆线b，是否超过半圈。
static struct circle Circles[6] = {
        -1, 795, 229, 1, 0, 59, 129, false,
        1, 613, 199, 59, 129, 0, 1, false,
        -1, 460, 228, 0, 1, 1, 0,false,
        1,328, 384, 1, 0, 148, -25, true,
        -1, 574, 512, 148, -25, 131, -26, false,
        1, 522, 695, 131, -26, 0, 1, false
};
//struct circle circle1 = {-1, 850, 290};

SDL_Rect Way_Rect[Rect_Num] = {};

#endif //START_WAYPOINT_H
