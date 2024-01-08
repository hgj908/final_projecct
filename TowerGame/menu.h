#pragma once
#include "global.h"
#include "resource.h"
void menu_init();
void menu_destroy();
int menu_process(ALLEGRO_EVENT);
void menu_draw();


class MENU : public State{
public:
    virtual void State_init() ;
    virtual int  State_process(ALLEGRO_EVENT);
    /*virtual void Scene_state(int SCENE_RESULT) override {
        scene_state = SCENE_RESULT;
    }*/
    virtual void Scene_draw() ;
};
