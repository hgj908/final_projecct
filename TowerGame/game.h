#pragma once
#include "global.h"
//enum { PLAYER_IDLE, PLAYER_ROLL, PLAYER_DIE };
//enum { DIR_LEFT, DIR_RIGHT };
class Player{
public:
    void player_init(){
        x = y = frame = 0;
        state = 0;
        dir = 1;
        HP = 3;
        printf("%d\n",state);
        printf("playerinit");
    }
    int player_die();
    void player_getcandy();
    void player_frame();
    void queen_process1();
    void player_hurt();
    void heart_draw();
    void score_draw();
    void player_draw();
    void player_jump();
    int x_val(){
        return x;
    }
    int y_val(){
        return y;
    }
    int ox_val(){
        return ox;
    }
    int oy_val(){
        return oy;
    }
    int x_eval(int u){
        x=u;
    }
    int y_eval(int u){
        y=u;
    }
    int ox_eval(int u){
        ox=u;
    }
    int oy_eval(int u){
        oy=u;
    }
    int HP_val() {
        return HP;
    }
    int HP_eval(int u){
        HP=u;
    }
    int dir_val() {
        return dir;
    }
    int dir_eval(int u){
        dir=u;
    }
    int state_val() {
        return state;
    }
    int state_eval(int u){
        state=u;
    }
    int frame_val() {
        return frame;
    }
    int frame_eval(int u){
        frame=u;
    }
private:
   int x;
    int y;
    int ox;
    int oy;
    int frame;
    int state;
    int dir;
    int HP;
    //Player(const int &_val): x(_val){}
    //Player(const int &__val): y(__val){}
};
void game_init(Player cha);
void game_destroy();
int game_process(ALLEGRO_EVENT,Player cha);
void game_draw(Player cha);
void heart_draw(Player cha);
void score_draw(Player cha);
void queens_process(int n);
void candy_process();
