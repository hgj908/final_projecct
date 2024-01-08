#pragma once
#include "global.h"
#include "resource.h"
void about_init();
void about_destroy();
int about_process(ALLEGRO_EVENT);
void about_draw();
class ABOUT : public State{
public:
    virtual void State_init() ;

    /*virtual void Scene_state(int SCENE_ABOUT) override {
        scene_state = SCENE_ABOUT;
    }*/
    virtual int  State_process(ALLEGRO_EVENT);
    virtual void Scene_draw() ;
};
