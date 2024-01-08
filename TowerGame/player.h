#pragma once
#include "global.h"
enum { PLAYER_IDLE, PLAYER_ROLL, PLAYER_DIE };
enum { DIR_LEFT, DIR_RIGHT };

class Player{
public:
    void player_init(){
        x = y = frame = state = 0;
        dir = 1;
        HP = 3;
    }

    int player_die();
    void player_getcandy();
    void player_change_frame();
    void player_hurt();
    int player_draw();
    void player_roll();
    //void heart_draw();
    //void score_draw();
    int player_go_die();
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
    void x_eval(int u){
        x=u;
    }
    void y_eval(int u){
        y=u;
    }
    void ox_eval(int u){
        ox=u;
    }
    void oy_eval(int u){
        oy=u;
    }
    int HP_val() {
        return HP;
    }
    void HP_eval(int u){
        HP=u;
    }
    int dir_val() {
        return dir;
    }
    void dir_eval(int u){
        dir=u;
    }
    int state_val() {
        return state;
    }
    void state_eval(int u){
        state=u;
    }
    int frame_val() {
        return frame;
    }
    void frame_eval(int u){
        frame=u;
    }
private:
    int x ;
    int y ;
    int ox;
    int oy;
    int frame ;
    int state ;
    int dir ;
    int HP ;
    //Player(const int &_val): x(_val){}
    //Player(const int &__val): y(__val){}
};
