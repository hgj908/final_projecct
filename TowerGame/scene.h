#pragma once
#include "global.h"
#include "game.h"
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
int scene_run(Player cha);
int scene_process(ALLEGRO_EVENT,Player cha);
void scene_draw(Player cha);
// extern int msg;
