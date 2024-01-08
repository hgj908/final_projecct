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
    int get_x(){
        return x;
    }
    int get_y(){
        return y;
    }
    int get_ox(){
        return ox;
    }
    int get_oy(){
        return oy;
    }
    void set_x(int u){
        x=u;
    }
    void set_y(int u){
        y=u;
    }
    void set_ox(int u){
        ox=u;
    }
    void set_oy(int u){
        oy=u;
    }
    int get_HP() {
        return HP;
    }
    void set_HP(int u){
        HP=u;
    }
    int get_dir() {
        return dir;
    }
    void set_dir(int u){
        dir=u;
    }
    int get_state() {
        return state;
    }
    void set_state(int u){
        state=u;
    }
    int get_frame() {
        return frame;
    }
    void set_frame(int u){
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
