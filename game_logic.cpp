
//游戏整体逻辑都在这里
extern void Print_Dec(int n, SDL_Rect *pos);

extern void wave(int m, int n);

extern void pWinorLose(SDL_Texture *pic);


void refresh() {
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, map, nullptr, nullptr);  //渲染器加载地图
    SDL_RenderCopy(gRenderer, pause_pic, nullptr, &pausepos);  //暂停按钮
    SDL_RenderCopy(gRenderer, statef, nullptr, &statepos);  //血量栏
    game->Enemy_Wave();
    wave(game->Wave, WAVE);
    game->Detect();
    game->Render();
    if (menu_open >= 0) {
        if (game->money>=125) SDL_RenderCopy(gRenderer, choice_ring[0], nullptr, &choicepos[menu_open]);
        else if (game->money<100) SDL_RenderCopy(gRenderer, choice_ring[1], nullptr, &choicepos[menu_open]);
        else SDL_RenderCopy(gRenderer, choice_ring[2], nullptr, &choicepos[menu_open]);
    }
    if (game->If_No_Enemy())
        SDL_RenderCopy(gRenderer, nextwave, nullptr, &nextwavepos);
    Print_Dec(game->life, lifepos);
    Print_Dec(game->money, moneypos);
    SDL_RenderPresent(gRenderer);
    if (game->life <= 0) {
        pause = true;
    }
//    if (game->If_No_Enemy())
//        game->Enemy_Count = 10;
}

void Print_Dec(int n, SDL_Rect *pos) {
    int a, b, c, d;
    if (n < 0) n = 0;
    a = n / 1000;
    b = (n / 100) % 10;
    c = (n / 10) % 10;
    d = n % 10;
    if (n > 999) {
        SDL_RenderCopy(gRenderer, numf[a], nullptr, pos);
        SDL_RenderCopy(gRenderer, numf[b], nullptr, pos + 1);
        SDL_RenderCopy(gRenderer, numf[c], nullptr, pos + 2);
        SDL_RenderCopy(gRenderer, numf[d], nullptr, pos + 3);
    } else if (n > 99) {
        SDL_RenderCopy(gRenderer, numf[b], nullptr, pos);
        SDL_RenderCopy(gRenderer, numf[c], nullptr, pos + 1);
        SDL_RenderCopy(gRenderer, numf[d], nullptr, pos + 2);
    } else if (n > 9) {
        SDL_RenderCopy(gRenderer, numf[c], nullptr, pos);
        SDL_RenderCopy(gRenderer, numf[d], nullptr, pos + 1);
    } else {
        SDL_RenderCopy(gRenderer, numf[d], nullptr, pos);
    }
}

void wave(int m, int n)  //打印第几波
{
    SDL_RenderCopy(gRenderer, numf[m], nullptr, wavepos);
    SDL_RenderCopy(gRenderer, numf[n], nullptr, wavepos + 1);
}

void pWinorLose(SDL_Texture *pic)  //打印失败标志
{
    SDL_RenderCopy(gRenderer, pic, nullptr, resultpos);
    SDL_RenderCopy(gRenderer, again, nullptr, resultpos + 1);
    SDL_RenderCopy(gRenderer, quit, nullptr, resultpos + 2);
}

SDL_Rect relative_rect(int x, int y, SDL_Rect *inner_rect) {
    SDL_Rect return_rect = *inner_rect;
    return_rect.x += x;
    return_rect.y += y;
    return return_rect;
}