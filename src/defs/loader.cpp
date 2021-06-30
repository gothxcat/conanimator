/*
*   Filesystem animation loader
*/

#include <stdlib.h>

// Program headers
#include <animations.hpp>
#include <animators.hpp>
#include <fs.hpp>
#include <proc.hpp>

// Instantiate FrameAnimator from loaded anim and start the animator UI 
int run_anim(const char *path) {
    Animation anim;
    char *data;
    if (read_file(&data, path) == 0) {
        anim = load_animation(data);
    } else {
        return EXIT_FAILURE;
    }

    FrameAnimator animator = FrameAnimator(anim);
    start(&animator);
    return EXIT_SUCCESS;
}