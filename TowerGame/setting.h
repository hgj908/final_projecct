#pragma once
#include "global.h"
#include "resource.h"
#include "scene.h"
void setting_init();
void setting_destroy();
int setting_process(ALLEGRO_EVENT);
void setting_draw();
class SETTING : public State{
public:
    virtual void State_init() ;
    virtual int State_process(ALLEGRO_EVENT);

    virtual void Scene_draw() ;

};
