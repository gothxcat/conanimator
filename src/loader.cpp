/*
*   Visual animation loader
*/

#include <cstdlib>

// Program headers
#include <animator.hpp>
#include <fs.hpp>
#include <loader.hpp>

namespace kb_signal {
    enum SIGNALS {
        NONE = 0,
        DONE = 1,
        RESIZE = 2
    };
};

class Loader {
    protected:
        Animator *animator;
        bool *done;

        map_kb_func keys = {
            { 'q', &Loader::end },
            { KEY_RESIZE, &Loader::resize }
        };

        int end() {
            *(this->done) = true;
            return kb_signal::DONE;
        }

        int resize() {
            this->animator->update();
            return kb_signal::RESIZE;
        }

    public:
        Loader(Animator *animator, bool *done) {
            this->animator = animator;
            this->done = done;
        }

        int run_action(char key) {
            map_kb_func::iterator match = this->keys.find(key);
            if (match != this->keys.end())
                return this->keys[key](this);
            return kb_signal::NONE;
        }
};

/*  Start the animator's thread with a reference to the exit value
*   and run the ncurses input loop */
void start(Animator *animator) {
    bool done = false;
    Loader loader(animator, &done);

    int signal = 0;
    char key;
    animator->start(&done);
    while (!done) {
		key = tolower(getch());
        signal = loader.run_action(key);
	}

    animator->end();
}

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