#include "about.h"
#include "resource.h"

void ABOUT::State_init() {}

void about_destroy() {}

int ABOUT::State_process(ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_KEY_DOWN &&
        (event.keyboard.keycode == ALLEGRO_KEY_ENTER ||
        event.keyboard.keycode == ALLEGRO_KEY_E)) {
        return MSG_BACK_TO_MENU;
    }
    return MSG_NOPE;
}

void ABOUT::Scene_draw() {
    al_draw_scaled_bitmap(about, 0, 0, 1563, 1980, 0, 0, 760, 950, 0);
}
