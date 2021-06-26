/*
*   FrameAnimator
*/

#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <vector>
#include <thread>
#include "../include/animator.hpp"

void animate_frames(std::vector<const char *> frames, useconds_t interval, bool *completed) {
    const char *current_frame;
    size_t frame_count = frames.size();
    size_t frame_size = getmaxy(stdscr) * getmaxx(stdscr);
    while (!*completed) {
        for (int i=0; i<frame_count; i++) {
            current_frame = frames[i];
            mvaddstr(0, 0, current_frame);
            refresh();
            usleep(interval);
        }
    }
}

class FrameAnimator: public Animator {
    private:
        std::vector<const char *> frames;
        useconds_t interval;
        
        WINDOW *setup(std::vector<const char *> frames, useconds_t interval) {
            WINDOW *ret = scr_setup();
            this->frames = frames;
            this->interval = interval;

            return ret;
        }
    
    public:
        void start(bool *return_signal) {
            this->animator = std::thread(animate_frames, this->frames, this->interval, return_signal);
        }

        FrameAnimator(std::vector<const char *> frames, useconds_t interval) {
            this->setup(frames, interval);
        }

        FrameAnimator();
};
