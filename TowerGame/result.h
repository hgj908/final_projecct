#pragma once
#include "global.h"
#include "resource.h"
void result_init();
void result_destroy();
int result_process(ALLEGRO_EVENT);
void result_draw();

class RESULT : public State{
public:
    virtual void State_init() ;

    /*virtual void Scene_state(int SCENE_RESULT) override {
        scene_state = SCENE_RESULT;
    }*/
    virtual int  State_process(ALLEGRO_EVENT);
    virtual void Scene_draw() ;
};
