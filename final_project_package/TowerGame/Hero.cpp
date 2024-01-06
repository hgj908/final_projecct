#include "Hero.h"

int draw_frequency=10;
const char  direction_name[][10]={"left","right","front","back"};
void Hero::Init(){
     char buffer[50];
     imgCount[HeroState::LEFT]=2;
     imgCount[HeroState::RIGHT]=2;
     imgCount[HeroState::FRONT]=2;
     imgCount[HeroState::BACK]=2;

    for(int i=0; i < 4; i++)
    {
        for(int j=0; j<imgCount[static_cast<HeroState>(i)]; j++)
        {
            ALLEGRO_BITMAP *img;

            sprintf(buffer, "./Hero/dragonite_%s_%d.png", direction_name[i], j+1);
            img = al_load_bitmap(buffer);
            if(img)
                imgData[static_cast<HeroState>(i)].push_back(img);
        }
    }
    y=window_height/2;
    x=window_width/2;


}
void Hero::update(){
     //rintf("??");
    counter = (counter + 1) % draw_frequency;

    if(counter == 0)
        sprite_pos = (sprite_pos + 1) % imgCount[direction];

        //key
    if( key_state[ALLEGRO_KEY_W] ){
        y -= speed;
        //printf("??");
        direction = HeroState::BACK;
    }else if( key_state[ALLEGRO_KEY_A] ){
        x -= speed;
        direction = HeroState::LEFT;
    }else if( key_state[ALLEGRO_KEY_S] ){
        y += speed;
        direction = HeroState::FRONT;
    }else if( key_state[ALLEGRO_KEY_D] ){
        x += speed;
        direction = HeroState::RIGHT;
    }

}
void Hero::draw(){
    al_draw_bitmap(imgData[direction][sprite_pos],x,y,0);


}
