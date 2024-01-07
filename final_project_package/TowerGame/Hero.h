#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED
#include <map>
#include <vector>
#include <allegro5/allegro.h>
#include "global.h"
#include <stdio.h>
#include <string.h>

#include <allegro5/allegro_primitives.h>
enum class HeroState{LEFT,RIGHT,FRONT,BACK,ATTACK};
class Hero
{
public:
    void Init();
    void update();
    void draw();
private:
    int x,y,counter=0,sprite_pos=0;
    int speed=5;
    HeroState direction =HeroState::FRONT;
    std::map<HeroState,std::vector<ALLEGRO_BITMAP*>  > imgData;
    std::map<HeroState,int > imgCount;


};







#endif // HERO_H_INCLUDED
