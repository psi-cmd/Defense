
//游戏整体逻辑都在这里

void loadSingle() {
    map = loadTexture(mapfile);
    if (map == nullptr) {
        std::cout << "Unable to load image %s! SDL Error: " << "image\\map_demo.png" << SDL_GetError();
    }

    TowerStaticTexture[0] = loadTexture(towergroundfile);
    if (TowerStaticTexture[0] == nullptr) {
        std::cout << "Unable to load image %s! SDL Error: " << "image\\raw.png" << SDL_GetError();
    }

    MBullet_Texture = loadTexture(MBullet_Pic);
    if (MBullet_Texture == nullptr) {
        std::cout << "Unable to load image %s! SDL Error: " << "image\\bullet.png" << SDL_GetError();
    }
}

void refresh() {
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, map, nullptr, nullptr);  //渲染器加载地图
    game->Enemy_Wave();
    game->Detect();
    game->Render();
    SDL_RenderPresent(gRenderer);
    SDL_Delay(50);
}
