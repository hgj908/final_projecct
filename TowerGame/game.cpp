#include "game.h"
#include "resource.h"
#include "player.h"
// by art
double j_idle_begin_time;
double game_begin_time;
float die_count_begin;
int gif_count = 0;
// by player
int generator_speed = 180;//生成速度，180楨刷新一波
int counter;
int queens_num;
const float unit = 86;
const float dx = 33;
const float dy = 241;


void GAME::State_init(Player &cha) {
    // by art
    j_idle_begin_time = al_get_time();
    game_begin_time = al_get_time();
    cha.player_init();
    //cha.x_eval(0);
    //cha.y_eval(0);
    //cha.frame_eval(0);
    //cha.state_eval(PLAYER_IDLE);
    //cha.dir_eval(DIR_RIGHT);
    //cha.HP_eval(3);
    counter = generator_speed;
    queens_num = 1;
}

void game_destroy() {}
void Queen::object_process(int n) {
    int x, y, num;
    for(int i=0; i<n; i++){
        num = rand() % 64;
        x = num / 8;
        y = num % 8;
        for(int col=0;col<8;col++){
            board[y][col]++;
        }
        for(int row=0;row<8;row++){
            board[row][x]++;
            for(int col=0;col<8;col++){
                if(row+col==x+y||row-col==y-x){
                    board[row][col]++;
                }
            }
        }//只要有攻擊到就+1
        board[y][x]=100;//rand之後把有皇后的點的值改為30
    }
}

void Candy::object_process1(){
    int candy=rand()%64;
    if(board[candy%8][candy/8]==0)
        board[candy%8][candy/8]=-100;
}

int GAME::State_process(ALLEGRO_EVENT event,Player &player) {
    Queen q;
    if (player.player_die()==1) {
        if (al_get_time() - die_count_begin >= 2) {
            return MSG_GAME_OVER;
        }
        return MSG_NOPE;
    }
    // 測試血量顯示
    if (event.type == ALLEGRO_EVENT_KEY_DOWN &&
        event.keyboard.keycode == ALLEGRO_KEY_Q &&
        player.HP_val() > 0) {
        player.HP_eval(player.HP_val()-1);
    }
    player.player_getcandy();
    // player idle
    if (event.type == ALLEGRO_EVENT_KEY_DOWN && player.state_val() == PLAYER_IDLE) {
        player.ox_eval( player.x_val());
        player.oy_eval( player.y_val());

        if ((event.keyboard.keycode == key_left || event.keyboard.keycode == ALLEGRO_KEY_A )&& player.x_val() > 0) {
            player.x_eval(player.x_val()-1);
        } else if ((event.keyboard.keycode == key_right || event.keyboard.keycode == ALLEGRO_KEY_D ) && player.x_val() < 7) {
            player.x_eval(player.x_val()+1);
        } else if ((event.keyboard.keycode == key_up || event.keyboard.keycode == ALLEGRO_KEY_W ) && player.y_val() > 0) {
           player.y_eval(player.y_val()-1);
            //printf("??");
        } else if ((event.keyboard.keycode == key_down || event.keyboard.keycode == ALLEGRO_KEY_S ) && player.y_val() < 7) {
            player.y_eval(player.y_val()+1);
        }
        player.player_roll();
    }

    // only update frame count when the event is from the scene timer
    // don't update for keyboard event
    if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == scene_timer) {
        player.player_change_frame();
        gif_count++;
        counter--;
        if (counter == 150) {
            //生成皇后
            //變數可以調整，要隨著時間調整也行
            q.object_process(1 + queens_num / 8);
            //candy
            //if(number%5==0)
            Candy c;
            c.object_process1();
        } else if (counter == 20) {
            al_stop_sample_instance(lightning_spi);
            al_play_sample_instance(lightning_spi);
        } else if (counter == 0) {
            //判斷扣血
            player.player_hurt();
            if (player.player_go_die()==1) {
                die_count_begin = al_get_time();
                al_play_sample_instance(dead_sound_spi);
            }
            //清空皇后
            q.object_clear();
            queens_num++;
            counter = generator_speed; //counter重製
        }
    }

    return MSG_NOPE;
}
void Queen::object_clear() {
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            board[i][j] = 0;
            }
    }
}
void heart_draw(Player &player) {
    const int heart_size = 60;
    if (player.HP_val() >= 1)
        al_draw_scaled_bitmap(heart, 0, 0, 22, 23, 50, 50, heart_size, heart_size, 0);
    if (player.HP_val() >= 2)
        al_draw_scaled_bitmap(heart, 0,0 , 22, 23, 120, 50, heart_size, heart_size, 0);
    if (player.HP_val() >= 3)
        al_draw_scaled_bitmap(heart, 0,0 , 22, 23, 190, 50, heart_size, heart_size, 0);
}

void score_draw(Player &player) {
    if (player.HP_val() > 0) {
        number = al_get_time() - game_begin_time;
        if(!easter_egg_mode){
            number = (al_get_time() - game_begin_time)*3;
        }
    }

    al_draw_textf(score, al_map_rgb(255,255,255), 400, 55, ALLEGRO_ALIGN_LEFT,  "Score: %3d", number);
    al_draw_textf(score, al_map_rgb(255,255,255), 270, 140, ALLEGRO_ALIGN_LEFT,  "MaxScore: %3d", maxx);
}

void Queen::object_draw(){
    for (int i=0; i<8; ++i) {
        for (int j=0; j<8; ++j) {
            if(board[i][j] >=1 && board[i][j] < 20) {
                if (counter < 21) {
                    al_draw_bitmap(
                        algif_get_bitmap(Lightening_gif, al_get_time()),
                        dx + i*unit,
                        dy + j*unit,
                        0
                    );
                }

                else if (counter <= 150) {
                    const int upper_bound = unit / 2 - 3;
                    const int lower_bound = unit / 2 - 10;
                    float a = (sin(al_get_time() * 8) + 1) / 2;
                    float r = lower_bound + (upper_bound - lower_bound) * a;

                    //mode
                    if(easter_egg_mode){
                        /*
                        al_draw_filled_rectangle(
                            dx + (i+0.5)*unit - r,
                            dy + (j+0.5)*unit - r,
                            dx + (i+0.5)*unit + r,
                            dy + (j+0.5)*unit + r,
                            al_map_rgba(255, 0, 0, 200)
                        );*/
                        al_draw_scaled_bitmap(
                            algif_get_frame_bitmap(
                                warn_gif,
                                gif_count / 6 % warn_gif->frames_count),
                            200,
                            203,
                            94,
                            94,
                            dx + i*unit,
                            dy + j*unit,
                            unit,
                            unit,
                            0
                        );
                    }
                }
            }
            if (board[i][j] >= 90) {
                al_draw_scaled_bitmap(
                    algif_get_bitmap(Queen_gif, al_get_time()),
                    0,
                    0,
                    480,
                    480,
                    dx + i*unit,
                    dy + j*unit,
                    unit,
                    unit,
                    0
                );
            }
        }
    }

}
void Candy::object_draw(){
    for (int i=0; i<8; ++i) {
        for (int j=0; j<8; ++j) {
                if (board[i][j] < 0) {
                al_draw_scaled_bitmap(
                    algif_get_frame_bitmap(
                        candy_gif, gif_count / 6 % candy_gif->frames_count),
                    175,
                    211,
                    140,
                    140,
                    dx + i*unit,
                    dy + j*unit,
                    unit,
                    unit,
                    0
                );
            }
        }
    }
}
void player_draw(Player &player){
    const float unit = 86;
    const float dx = 33;
    const float dy = 241;

    if (player.player_draw()==1) {
        al_draw_bitmap(
            algif_get_bitmap(JI_gif, al_get_time()),
            dx + player.x_val()*unit,
            dy + player.y_val()*unit,
            player.dir_val() == DIR_LEFT ? ALLEGRO_FLIP_HORIZONTAL : 0);
    } else if(player.player_draw()==2){
        al_draw_bitmap(
            algif_get_bitmap(JJ_gif, player.frame_val()/21.0*0.84),
            dx + (player.x_val()*(player.frame_val()/21.0)+player.ox_val()*(1-player.frame_val()/21.0))*unit,
            dy + (player.y_val()*(player.frame_val()/21.0)+player.oy_val()*(1-player.frame_val()/21.0))*unit,
            player.dir_val() == DIR_LEFT ? ALLEGRO_FLIP_HORIZONTAL : 0);
    } else if(player.player_draw()==3) {
        if (al_get_time() - die_count_begin <= 0.5){
            al_draw_bitmap(
                algif_get_bitmap(JD_gif, al_get_time() - die_count_begin),
                dx + player.x_val()*unit,
                dy + player.y_val()*unit,
                player.dir_val() == DIR_LEFT ? ALLEGRO_FLIP_HORIZONTAL : 0);
        } else {
            al_draw_bitmap(
                JD_stop,
                dx + player.x_val()*unit,
                dy + player.y_val()*unit,
                player.dir_val() == DIR_LEFT ? ALLEGRO_FLIP_HORIZONTAL : 0);
        }
    }

}
void background_draw(){
    al_draw_bitmap(GBI, 0, 0, 0);
}
void GAME::scene_draw(Player &player) {
    Queen q;
    Candy c;
    background_draw();
    q.object_draw();
    c.object_draw();
    player_draw(player);
    score_draw(player);
    heart_draw(player);

}
