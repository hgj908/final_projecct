#pragma once
#include "global.h"
#include"game.h"
enum {
    SCENE_MENU,
    SCENE_GAME,
    SCENE_RESULT,
    SCENE_SETTING,
    SCENE_ABOUT
};

void scene_init();
void scene_begin();
void scene_destroy();
int scene_run(Player &player);
int scene_process(ALLEGRO_EVENT,Player &player);
void scene_draw( Player &player);
// extern int msg;
