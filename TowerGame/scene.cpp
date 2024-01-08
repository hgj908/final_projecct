#include "scene.h"
#include "menu.h"
#include "game.h"
#include "result.h"
#include "resource.h"
#include "setting.h"
#include "about.h"
#include "player.h"
int scene_state;

void Scene::scene_init() {
    al_init();
    // keyboard
    al_install_keyboard();
    // mouse
    al_install_mouse();
    // audio
    al_install_audio();
    al_init_acodec_addon();
    al_restore_default_mixer();
    // primitives
    al_init_primitives_addon();
    // image & text
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    scene_queue = al_create_event_queue();
    scene_display = al_create_display(WIDTH, HEIGHT);
    scene_timer = al_create_timer(1.0 / FPS);

    al_set_window_title(scene_display, "8_queens");
    al_set_window_position(scene_display, 500, 0);

    al_register_event_source(scene_queue, al_get_display_event_source(scene_display));
    al_register_event_source(scene_queue, al_get_timer_event_source(scene_timer));
    al_register_event_source(scene_queue, al_get_keyboard_event_source());
    al_register_event_source(scene_queue, al_get_mouse_event_source());

    load_resource();
    srand(time(NULL));
}
// class
// input(int msg)
// function:
// 1. menu_destroy
// 2. virtural �n override ��@init
// 3. ��쨺�ӹϪ��Y�@�Ӯy�СA�i�H�ǥѳo�Ӯy�СA�h��b�Y
// 4. virtural �n override ��@�\��b�Y

void Scene::scene_begin() {
    scene_state = SCENE_MENU;
    MENU ori;
    ori.State_init();
    al_start_timer(scene_timer);
    al_play_sample_instance(eight_queens_bgm_spi);
}

void Scene::scene_destroy() {
    al_destroy_event_queue(scene_queue);
    al_destroy_display(scene_display);
    al_destroy_timer(scene_timer);
    destroy_resource();
}

int Scene::scene_run() {
    ALLEGRO_EVENT event;
    Player player;

    al_wait_for_event(scene_queue, &event);
    // if the window was closed, then terminate the program
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE && event.display.source == scene_display) {
        return MSG_TERMINATE;
    }

    if (scene_process(event, player) == MSG_TERMINATE) {
        return MSG_TERMINATE;
    }

    if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == scene_timer) {
        scene_draw( player);
    }
    return MSG_NOPE;

}

int Scene::scene_process(ALLEGRO_EVENT event,Player &player) {
    int msg;

    if (scene_state == SCENE_MENU) {
        MENU now_state;
        msg = now_state.State_process(event);
        // printf("final\n");
        if (msg == MSG_GAME_START) {
             GAME now_state;
             menu_destroy();
             scene_state = SCENE_GAME;
             now_state.State_init(player);
        } else if (msg == MSG_CHANGE_SETTING) {
            SETTING now_state;
            scene_state = SCENE_SETTING;
            now_state.State_init();
            // menu_destroy();
        } else if (msg == MSG_TERMINATE) {
            return MSG_TERMINATE;
        } else if (msg == MSG_ABOUT) {
            ABOUT now_state;
            //now_state.Scene_state(SCENE_ABOUT);
            scene_state = SCENE_ABOUT;
            now_state.State_init();
            // menu_destroy();
        }
    } else if (scene_state == SCENE_GAME) {
        GAME now_state;
        msg = now_state.State_process(event,player);
        if (msg == MSG_GAME_OVER) {
            RESULT next_state;
            game_destroy();
            //now_state.Scene_state(SCENE_RESULT);
            scene_state = SCENE_RESULT;
            next_state.State_init();
            //scene_state = SCENE_RESULT;
            //result_init();
        }
    } else if (scene_state == SCENE_RESULT) {
        RESULT now_state;

        msg = now_state.State_process(event);
        if (msg == MSG_GAME_RESTART) {
            GAME now_state;
            result_destroy();
            scene_state = SCENE_GAME;
            now_state.State_init(player);
        } else if (msg == MSG_BACK_TO_MENU) {
            MENU next_state;
            result_destroy();
            scene_state = SCENE_MENU;
            next_state.State_init();
        } else if (msg == MSG_TERMINATE) {
            return MSG_TERMINATE;
        }
    } else if (scene_state == SCENE_SETTING) {
        SETTING now_state;
        msg = now_state.State_process(event);
        if (msg == MSG_BACK_TO_MENU) {
            MENU next_state;
            setting_destroy();
            scene_state = SCENE_MENU;
            next_state.State_init();
        }
    } else if (scene_state == SCENE_ABOUT) {
        ABOUT now_state;
        msg = now_state.State_process(event);
        if (msg == MSG_BACK_TO_MENU) {
            MENU next_state;
            about_destroy();
            scene_state = SCENE_MENU;
            next_state.State_init();
        }
    }
    return MSG_NOPE;
}

void Scene::scene_draw( Player &player) {
    //printf("%d\n",player.x_val());
    if (scene_state == SCENE_MENU) {
        MENU now_state;
        now_state.Scene_draw();
    } else if (scene_state == SCENE_GAME) {
        GAME now_state;
        now_state.scene_draw(player);
    } else if (scene_state == SCENE_RESULT) {
        RESULT now_state;
        now_state.Scene_draw();
    } else if (scene_state == SCENE_SETTING) {
        SETTING now_state;
        now_state.Scene_draw();
    } else if (scene_state == SCENE_ABOUT) {
        ABOUT now_state;
        now_state.Scene_draw();
    }
    al_flip_display();
}
