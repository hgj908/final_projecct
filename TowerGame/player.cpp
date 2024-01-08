#include "resource.h"
#include "player.h"

int Player::player_die(){
    if (state == PLAYER_DIE) {
        return 1;
    }
    return 0;
}
int Player::player_go_die(){
     if (state != PLAYER_DIE && HP == 0) {
        state = PLAYER_DIE;
        return 1;
     }
     return 0;  //die_count_begin = al_get_time();
        //al_play_sample_instance(dead_sound_spi);
}
void Player::player_getcandy(){
    if(state == PLAYER_IDLE && board[x][y] < 0) {
        if (HP < 3)
            HP++;
        board[x][y] = 0;
        al_stop_sample_instance(get_candy_spi);
        al_play_sample_instance(get_candy_spi);
    }
}
void Player::player_roll(){
    if (x != ox || y != oy) {
            state = PLAYER_ROLL;
            frame = 0;
            if (x != ox) {
                dir = (x < ox) ? DIR_LEFT : DIR_RIGHT;
            }
            al_stop_sample_instance(jump_spi);
            al_play_sample_instance(jump_spi);
        }
}
void Player::player_change_frame(){
    frame++;
    if (state == PLAYER_ROLL && frame >= 21) {
        state = PLAYER_IDLE;
        frame = 0;
    }

}
void Player::player_hurt(){
    if (state == PLAYER_IDLE && board[x][y] >= 1) {
                HP--;
    } else if (state == PLAYER_ROLL) {
        if (frame < 21 / 2 && board[ox][oy] >= 1) {
            HP--;
        } else if (frame >= 21 / 2 && board[x][y] >= 1) {
            HP--;
        }
    }

}
int Player::player_draw(){
    if(state==PLAYER_IDLE) return 1;
    else if(state == PLAYER_ROLL) return 2;
    else if(state == PLAYER_DIE) return 3;
}
