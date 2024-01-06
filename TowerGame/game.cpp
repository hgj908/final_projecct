#include "game.h"
#include "resource.h"

enum { PLAYER_IDLE, PLAYER_ROLL, PLAYER_DIE };
enum { DIR_LEFT, DIR_RIGHT };
/*
struct {
    int x;
    int y;
    int ox;
    int oy;
    int frame;
    int state;
    int dir;
    int HP;
} player;
*/
/*class Monster: public Object {
public:
    Monster(std::vector<int> path);
    virtual ~Monster();

    // Draw image per frame
    // override virtual function "Object::Draw"
    void Draw();
    // Load bitmaps of animation image into container "moveImg"
    void Load_Move();

    // Update monster position per frame
    // And detect if it reaches end point but not destroyed
    bool Move();

    // functions that return informations of monster
    int getDir() { return direction; }
    int getWorth() { return worth; }
    int getScore() { return score; }

    bool Subtract_HP(int);

protected:
    int direction_count[4];
    int HealthPoint = 20;
    int speed = 1;
    int worth = 10;
    int score = 100;
    char class_name[20];
private:
    // direction and index for "path"
    unsigned int step;
    int direction;
    // end point
    int end_x, end_y;
    // animation counter
    int counter;
    // animation image of current direction
    int sprite_pos;

    // set of animation images
    std::vector<ALLEGRO_BITMAP*> moveImg;
    // path on map
    std::vector<int> path;

};
class Queen{
public:
     void qreen_process();
     void queen_init(){
        queens_num=1;
     }





    int queen_num;
};*/
/*class Player{
public:
    void player_init(){
        x = y = frame = 0;
        state = PLAYER_IDLE;
        dir = DIR_RIGHT;
        HP = 3;
    }
    int player_die();
    void player_process();
    void player_frame();
    void queen_process1();
    void player_hurt();
    void heart_draw();
    void score_draw();
    void player_draw();

private:
   int x;
    int y;
    int ox;
    int oy;
    int frame;
    int state;
    int dir;
    int HP;

};*/
// by art
double j_idle_begin_time;
double game_begin_time;
float die_count_begin;
int gif_count = 0;

// by player
int generator_speed = 180;//生成速度，180楨刷新一波
int counter;
int queens_num;

void game_init(Player cha) {
    // by art
    j_idle_begin_time = al_get_time();
    game_begin_time = al_get_time();

    cha.player_init();
    // by player
    //player.x = player.y = player.frame = 0;
    //player.state = PLAYER_IDLE;
    //player.dir = DIR_RIGHT;
    //player.HP = 3;

    printf("\nx:%d\n",cha.state_val());
    counter = generator_speed;
    queens_num = 1;
}
int Player::player_die(){
    if (state == PLAYER_DIE) {

        return 1;

    }
    return 0;
}
void Player::player_getcandy(){

    if(state == PLAYER_IDLE && board[x][y] < 0) {
        if (HP < 3)
            HP++;
        board[x][y] = 0;
        al_stop_sample_instance(get_candy_spi);
        al_play_sample_instance(get_candy_spi);
    }

    // player idle
}
void Player::player_jump(){
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
void Player::player_frame(){
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
    if (state != PLAYER_DIE && HP == 0) {
        state = PLAYER_DIE;
        die_count_begin = al_get_time();
        al_play_sample_instance(dead_sound_spi);
    }

}
void game_destroy() {}

void queens_process(int n) {
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

void candy_process(){
    int candy=rand()%64;
    if(board[candy%8][candy/8]==0)
        board[candy%8][candy/8]=-100;
}
/*Player::queen_process1(){
     if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == scene_timer) {
        player.frame++;
        if (player.state == PLAYER_ROLL && player.frame >= 21) {
            player.state = PLAYER_IDLE;
            player.frame = 0;
        }

        gif_count++;

        counter--;
        if (counter == 150) {
            //生成皇后
            //變數可以調整，要隨著時間調整也行
            queens_process(1 + queens_num / 8);
            //candy
            //if(number%5==0)
            candy_process();
        } else if (counter == 20) {
            al_stop_sample_instance(lightning_spi);
            al_play_sample_instance(lightning_spi);
        } else if (counter == 0) {
            //判斷扣血
            if (player.state == PLAYER_IDLE && board[player.x][player.y] >= 1) {
                player.HP--;
            } else if (player.state == PLAYER_ROLL) {
                if (player.frame < 21 / 2 && board[player.ox][player.oy] >= 1) {
                    player.HP--;
                } else if (player.frame >= 21 / 2 && board[player.x][player.y] >= 1) {
                    player.HP--;
                }
            }

            if (player.state != PLAYER_DIE && player.HP == 0) {
                player.state = PLAYER_DIE;
                die_count_begin = al_get_time();
                al_play_sample_instance(dead_sound_spi);
            }

            //清空皇后
            for(int i=0; i<8; i++){
                for(int j=0; j<8; j++){
                    board[i][j] = 0;
                }
            }
            queens_num++;
            counter = generator_speed; //counter重製
        }
    }

}*/
void queen_clear(){
     for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            board[i][j] = 0;
            }
    }
}
int game_process(ALLEGRO_EVENT event,Player cha ) {
    //Player cha;
    int k=cha.player_die();
    if (k==1) {
        if (al_get_time() - die_count_begin >= 2) {
            return MSG_GAME_OVER;
        }
        return MSG_NOPE;
    }

    // 測試血量顯示
    if (event.type == ALLEGRO_KEY_DOWN &&
        event.keyboard.keycode == ALLEGRO_KEY_W &&
        cha.HP_val() > 0) {
        cha.HP_eval( cha.HP_val()-1 );
    }
    cha.player_getcandy();
    /*if(player.state == PLAYER_IDLE && board[player.x][player.y] < 0) {
        if (player.HP < 3)
            player.HP++;
        board[player.x][player.y] = 0;
        al_stop_sample_instance(get_candy_spi);
        al_play_sample_instance(get_candy_spi);
    }*/

    // player idle
    if (event.type == ALLEGRO_EVENT_KEY_DOWN && cha.state_val() == PLAYER_IDLE) {
        cha.ox_eval (cha.x_val());
        cha.oy_eval (cha.y_val());
        //player.ox=player.x;
        //player.oy = player.y;

        if (event.keyboard.keycode == key_left && cha.x_val() > 0) {
            //--player.x;
            cha.x_eval(cha.x_val()-1);
        } else if (event.keyboard.keycode == key_right && cha.x_val() < 7) {
            //++player.x;
            cha.x_eval(cha.x_val()+1);
        } else if (event.keyboard.keycode == key_up && cha.y_val() > 0) {
            //--player.y;
            cha.y_eval(cha.y_val()-1);
            printf("??");
        } else if (event.keyboard.keycode == key_down && cha.y_val() < 7) {
            //++player.y;
            cha.y_eval(cha.y_val()+1);
        }
        cha.player_jump();
        /*if (player.x != player.ox || player.y != player.oy) {
            player.state = PLAYER_ROLL;
            player.frame = 0;
            if (player.x != player.ox) {
                player.dir = (player.x < player.ox) ? DIR_LEFT : DIR_RIGHT;
            }
            al_stop_sample_instance(jump_spi);
            al_play_sample_instance(jump_spi);
        }*/
    }

    // only update frame count when the event is from the scene timer
    // don't update for keyboard event
    //cha.player_process();
    if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == scene_timer) {
        /*player.frame++;
        if (player.state == PLAYER_ROLL && player.frame >= 21) {
            player.state = PLAYER_IDLE;
            player.frame = 0;
        }*/
        cha.player_frame();
        gif_count++;

        counter--;
        if (counter == 150) {
            //生成皇后
            //變數可以調整，要隨著時間調整也行
            queens_process(1 + queens_num / 8);
            //candy
            //if(number%5==0)
            candy_process();
        } else if (counter == 20) {
            al_stop_sample_instance(lightning_spi);
            al_play_sample_instance(lightning_spi);
        } else if (counter == 0) {
            //判斷扣血
            /*if (player.state == PLAYER_IDLE && board[player.x][player.y] >= 1) {
                player.HP--;
            } else if (player.state == PLAYER_ROLL) {
                if (player.frame < 21 / 2 && board[player.ox][player.oy] >= 1) {
                    player.HP--;
                } else if (player.frame >= 21 / 2 && board[player.x][player.y] >= 1) {
                    player.HP--;
                }
            }

            if (player.state != PLAYER_DIE && player.HP == 0) {
                player.state = PLAYER_DIE;
                die_count_begin = al_get_time();
                al_play_sample_instance(dead_sound_spi);
            }*/
            cha.player_hurt();
            //清空皇后
            queen_clear();
            /*for(int i=0; i<8; i++){
                for(int j=0; j<8; j++){
                    board[i][j] = 0;
                }
            }*/
            queens_num++;
            counter = generator_speed; //counter重製
        }
    }

    return MSG_NOPE;
}

void Player::heart_draw() {
    const int heart_size = 60;
    if (HP >= 1)
        al_draw_scaled_bitmap(heart, 0, 0, 22, 23, 50, 50, heart_size, heart_size, 0);
    if (HP >= 2)
        al_draw_scaled_bitmap(heart, 0,0 , 22, 23, 120, 50, heart_size, heart_size, 0);
    if (HP >= 3)
        al_draw_scaled_bitmap(heart, 0,0 , 22, 23, 190, 50, heart_size, heart_size, 0);
}

void Player::score_draw() {
    if (HP > 0) {
        number = al_get_time() - game_begin_time;
        if(!easter_egg_mode){
            number = (al_get_time() - game_begin_time)*3;
        }
    }

    al_draw_textf(score, al_map_rgb(255,255,255), 400, 55, ALLEGRO_ALIGN_LEFT,  "Score: %3d", number);
}
void queen_draw(){
    const float unit = 86;
    const float dx = 33;
    const float dy = 241;

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
void candy_draw(){
    const float unit = 86;
    const float dx = 33;
    const float dy = 241;
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
void Player::player_draw(){
    const float unit = 86;
    const float dx = 33;
    const float dy = 241;
    printf("%d\n",x);

     if (state == PLAYER_IDLE) {
        printf("idle\n");
        al_draw_bitmap(
            algif_get_bitmap(JI_gif, al_get_time()),
            dx + x*unit,
            dy + y*unit,
            dir == DIR_LEFT ? ALLEGRO_FLIP_HORIZONTAL : 0);
    } else if(state == PLAYER_ROLL){
        printf("roll\n");
        al_draw_bitmap(
            algif_get_bitmap(JJ_gif, frame/21.0*0.84),
            dx + (x*(frame/21.0)+ox*(1-frame/21.0))*unit,
            dy + (y*(frame/21.0)+oy*(1-frame/21.0))*unit,
            dir == DIR_LEFT ? ALLEGRO_FLIP_HORIZONTAL : 0);
    } else if(state == PLAYER_DIE) {
        printf("die\n");
        if (al_get_time() - die_count_begin <= 0.5){
            al_draw_bitmap(
                algif_get_bitmap(JD_gif, al_get_time() - die_count_begin),
                dx + x*unit,
                dy + y*unit,
                dir == DIR_LEFT ? ALLEGRO_FLIP_HORIZONTAL : 0);
        } else {
            al_draw_bitmap(
                JD_stop,
                dx + x*unit,
                dy + y*unit,
                dir == DIR_LEFT ? ALLEGRO_FLIP_HORIZONTAL : 0);
        }
    }

}
void game_draw(Player cha) {
    //Player cha;
    const float unit = 86;
    const float dx = 33;
    const float dy = 241;
    al_draw_bitmap(GBI, 0, 0, 0); // 這個是背景buffer
    queen_draw();
    candy_draw();
    cha.player_draw();
    cha.heart_draw();
    cha.score_draw();
}

