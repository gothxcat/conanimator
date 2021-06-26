/*
*   StringAnimator
*/

#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <thread>

#include "../include/stdscr.hpp"
#include "../include/str.hpp"
#include "../include/animator.hpp"

void animate_string(PortableString p_str, useconds_t interval, bool *completed) {
    char current_ch;
    while (!*completed) {
        clear();
        for (int i=0; i<p_str.len; i++) {
            current_ch = p_str.str[i];
            addch(current_ch);
            refresh();
            usleep(interval);
        }
    }
}

class StringAnimator: public Animator {
    private:
        PortableString p_str;
        useconds_t interval;
        
        WINDOW *setup(const char *str, useconds_t interval) {
            WINDOW *ret = scr_setup();
            this->p_str = {str, strlen(str)};
            this->interval = interval;

            return ret;
        }
    
    public:
        void start(bool *return_signal) {
            this->animator = std::thread(animate_string, this->p_str, this->interval, return_signal);
        }

        StringAnimator(const char *str, useconds_t interval) {
            this->setup(str, interval);
        }

        StringAnimator();
};
