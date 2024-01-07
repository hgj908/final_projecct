#include "global.h"
#include "scene.h"

int main(int argc, char **argv){
    scene_init();
    scene_begin();
    int msg;
    Player player;

    while ((msg = scene_run(player)) != MSG_TERMINATE ) {
        ;
    }
    scene_destroy();
    return 0;
}
