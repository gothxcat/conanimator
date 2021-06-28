/*
*   FrameAnimator
*/

#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <vector>
#include <thread>
#include <future>
#include <string>

#include <clock.hpp>
#include <animator.hpp>
#include <maths.hpp>
#include <animations.hpp>

struct FrameDebug {
    char **msg;
    char **msg_frametime;
    char **msg_framerate;
    std::string *spacer;
    int current_frame;
    int frame_count;
    double frametime;
    int framerate;
    Point max_xy;
};

class FrameAnimator: public Animator {
    private:
        std::vector<const char*> frames;
        unsigned int target_framerate;
        
        WINDOW *setup(std::vector<const char *> frames, unsigned int target_framerate) {
            WINDOW *ret = scr_setup();
            this->frames = frames;
            this->target_framerate = target_framerate;

            return ret;
        }
    
        static int asprintf_debug(FrameDebug info) {
            asprintf(info.msg_frametime, "Frame %02d/%02d took %fs",
                info.current_frame, info.frame_count, info.frametime);

            info.framerate = FRAMERATE(info.frametime);
            asprintf(info.msg_framerate, "%d fps", info.framerate);

            int space = info.max_xy.x - (strlen(*info.msg_frametime) + strlen(*info.msg_framerate));
            info.spacer->assign(space, ' ');
            const char *msg_spacer = info.spacer->c_str();

            return asprintf(info.msg, "%s%s%s",
                *info.msg_frametime, msg_spacer, *info.msg_framerate);
        }

        static void animate_frames(std::vector<const char*> frames, unsigned int target_framerate,
                std::timed_mutex *mtx, bool *completed) {
            const char *current_frame;
            
            Point max_xy = {
                getmaxx(stdscr),
                getmaxy(stdscr)
            };

            Point last_xy = {
                max_xy.x-1,
                max_xy.y-1
            };

            int frame_count = frames.size();
            
            float target_frametime = 1.0 / (target_framerate > 0 ? target_framerate
                : DEFAULT_FPS);

            hres_clock::time_point time;
            hres_clock::time_point previous_time;
            duration_d time_span;

            double frametime;
            int framerate;
            int msg_x_space;
            useconds_t delay;

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

                        delay = get_delay(frametime, target_frametime);
                        if (delay > 0) mtx->try_lock_for(std::chrono::microseconds(delay));

                        time = hres_clock::now();
                        time_span = std::chrono::duration_cast<duration_d>(time - previous_time);
                        frametime = time_span.count();
                        
                        asprintf_debug({&msg, &msg_frametime, &msg_framerate, &str_spacer,
                            i, frame_count, frametime, framerate, max_xy});
                        mvaddstr(last_xy.y, 0, msg);
                    }
                }
            }

            free(msg_frametime);
            free(msg_framerate);
            free(msg);
        }
    public:
        void start(bool *return_signal) {
            this->animator = std::thread(animate_frames,
                this->frames, this->target_framerate, &this->mtx, return_signal);
        }

        FrameAnimator(Animation animation) {
            this->setup(animation.frames, animation.framerate);
        }

        FrameAnimator();
};
