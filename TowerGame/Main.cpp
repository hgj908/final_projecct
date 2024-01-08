#include "global.h"
#include "scene.h"

int main(int argc, char **argv){
    Scene s;
    s.scene_init();
    s.scene_begin();
    int msg;

    while ((msg = s.scene_run()) != MSG_TERMINATE ) {
        ;
    }
    s.scene_destroy();
    return 0;
}
