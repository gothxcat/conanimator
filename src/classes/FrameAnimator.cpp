/*
*   FrameAnimator
*/

#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <vector>
#include <thread>
#include <future>
#include <string>
#include "../include/clock.hpp"
#include "../include/animator.hpp"
#include "../include/maths.hpp"

void animate_frames(std::vector<const char *> frames, useconds_t interval, std::timed_mutex *mtx, bool *completed) {
    const char *current_frame;
    
    Point max_xy = { getmaxx(stdscr), getmaxy(stdscr) };
    Point last_xy = { max_xy.x-1, max_xy.y-1 };
    size_t frame_count = frames.size();
    size_t frame_size = max_xy.x * max_xy.y;
    float target_frametime = 1.0/60.0;

    hres_clock::time_point time, previous_time;
    duration_d time_span;
    double frametime;
    int framerate;
    int msg_x_space;
    useconds_t diff, delay;
    char *msg_frametime, *msg_framerate, *msg;
    std::string str_spacer;

    while (!*completed) {
        for (int i=0; i<frame_count; i++) {
            if (!*completed) {
                previous_time = hres_clock::now();

                current_frame = frames[i];
                mvaddstr(0, 0, current_frame);
                refresh();

                time = hres_clock::now();
                time_span = std::chrono::duration_cast<std::chrono::seconds>(time - previous_time);
                frametime = time_span.count();

                diff = floor(S_TO_USECONDS(target_frametime - frametime));
                delay = diff > 0 ? diff : 0;
                if (delay > 0) mtx->try_lock_for(std::chrono::microseconds(delay));

                time = hres_clock::now();
                time_span = std::chrono::duration_cast<duration_d>(time - previous_time);
                
                frametime = time_span.count();
                asprintf(&msg_frametime, "Frame %02d/%02d took %fs",
                    i, frame_count, frametime);

                framerate = round(1.0/frametime);
                asprintf(&msg_framerate, "%d fps", framerate);

                msg_x_space = max_xy.x - (strlen(msg_frametime) + strlen(msg_framerate));
                str_spacer = std::string(msg_x_space, ' ');
                const char *msg_spacer = str_spacer.c_str();

                asprintf(&msg, "%s%s%s", msg_frametime, msg_spacer, msg_framerate);
                mvaddstr(last_xy.y, 0, msg);
            }
        }
    }

    free(msg_frametime);
    free(msg_framerate);
    free(msg);
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
            this->animator = std::thread(animate_frames, this->frames, this->interval, &this->mtx, return_signal);
        }

        FrameAnimator(std::vector<const char *> frames, useconds_t interval) {
            this->setup(frames, interval);
        }

        FrameAnimator();
};
