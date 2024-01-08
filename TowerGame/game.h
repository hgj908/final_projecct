#pragma once
#include "global.h"
#include "player.h"

void game_init(Player &player);
void game_destroy();
int game_process(ALLEGRO_EVENT,Player &player);
void game_draw( Player &player);
void queens_process(int n);
void candy_process();
void score_draw(Player &player);
void heart_draw(Player &player);
void player_draw(Player &player);
void queen_clear();
void queen_draw();
void background_draw();
class object{
public:
    virtual void object_process(int n);
    virtual void object_process1();
    virtual void object_draw();
};

class Queen : public object{
public:
    virtual void object_process(int n) ;
    virtual void object_process1()override{};
    void object_clear() ;
    virtual void object_draw() ;

};
class Candy : public object{
public:
    virtual void object_process1() ;
    virtual void object_process(int n)override{};
    virtual void object_draw() ;

};
class GAME{
public:
    void State_init(Player &);
    void scene_draw(Player &);
    int State_process(ALLEGRO_EVENT,Player &);

};

