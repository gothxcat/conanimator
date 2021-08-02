/*
*   Visual animator base classes
*/

#include <cstdlib>
#include <curses.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <thread>
#include <future>
#include <string>

// Program headers
#include <animator.hpp>
#include <clock.hpp>
#include <maths.hpp>
#include <stdscr.hpp>

// Base animator provides virtual framework 
class Animator {
    protected:
        // Internal properties for subclasses 
        std::thread animator;
        std::timed_mutex mtx;
        virtual WINDOW *setup() { return nullptr; };

    public:
        virtual void start(bool *return_signal) {};
        virtual void update() {};

        void end() {
            // Interrupt mutex timers, merge the threads and restore the ncurses screen 
            this->mtx.unlock();
            this->animator.join();
            scr_end();
        }

        Animator() {};
};

struct FrameDebug {
    /* Debug properties and pointers */

    // Must be accessible by FrameAnimator::asprintf_debug
    char **msg;
    char **msg_frametime;
    char **msg_framerate;
    std::string *spacer;
    int *framerate;
    
    // Must be set
    int human_index;
    int frame_count;
    double frametime;
    Point max_xy;
};

// Frame-by-frame animator 
class FrameAnimator: public Animator {
    private:
        std::vector<const char*> frames;
        unsigned int target_framerate;
        Point max_xy;
        
        // Initialise stdscr and animation props 
        WINDOW *setup(std::vector<const char *> frames, unsigned int target_framerate) {
            // Set private animation properties 
            WINDOW *ret = scr_setup();
            this->frames = frames;
            this->target_framerate = target_framerate;

            return ret;
        }

        // Generate debug string 
        static int asprintf_debug(FrameDebug info) {
            // Write debug string to memory reference 
            asprintf(info.msg_frametime, "Frame %02d/%02d took %fs",
                info.human_index, info.frame_count, info.frametime);

            *info.framerate = FRAMERATE(info.frametime);
            asprintf(info.msg_framerate, "%d fps", *info.framerate);
            
            // Concatenate padding space to align debug to left and right 
            int space = info.max_xy.x - (strlen(*info.msg_frametime) + strlen(*info.msg_framerate));
            const char *msg_spacer;
            if (space > 0) {
                info.spacer->assign(space, ' ');
                msg_spacer = info.spacer->c_str();
            } else {
                msg_spacer = "";
            }

            // Write final message 
            return asprintf(info.msg, "%s%s%s",
                *info.msg_frametime, msg_spacer, *info.msg_framerate);
        }

        // Renderer loop to run on thread 
        static void animate_frames(std::vector<const char*> frames, unsigned int target_framerate,
                Point *max_xy,
                std::timed_mutex *mtx, bool *completed) {
            char *current_frame;
            char *segment;
            int segment_index;

            int frame_count = frames.size();
            
            // Get target frametime in seconds from reciprocal of target framerate, prevent zero division 
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

            // Ensure clean stdscr buffer before render loop
            refresh();
            while (!*completed) {
                for (int i=0; i<frame_count; i++) {
                    // Interrupt if the boolean at the reference is completed
                    if (!*completed) {
                        // Get times to compare and calculate duration for frametimes
                        previous_time = hres_clock::now();

                        // Allocate new frame copy to scan
                        current_frame = (char*)malloc(strlen(frames[i]) * SIZE_CHAR);
                        strcpy(current_frame, frames[i]);

                        // Process lines to split for each row and print frame at stdscr start
                        segment = strtok(current_frame, "\n");
                        if (segment != NULL) {
                            segment_index = 0;
                            while (segment != NULL) {
                                mvaddstr(segment_index, 0, segment);
                                segment = strtok(NULL, "\n");
                                segment_index++;
                            }
                        } else {
                            mvaddstr(0, 0, current_frame);
                        }

                        time = hres_clock::now();
                        time_span = std::chrono::duration_cast<std::chrono::seconds>(time - previous_time);
                        frametime = time_span.count(); // (s)

                        // Sleep thread via mutex
                        delay = get_delay(frametime, target_frametime);
                        if (delay > 0) mtx->try_lock_for(std::chrono::microseconds(delay));

                        // Calculate frametime from duration
                        time = hres_clock::now();
                        time_span = std::chrono::duration_cast<duration_d>(time - previous_time);
                        frametime = time_span.count();
                        
                        // Print the debug string to the bottom of the screen
                        asprintf_debug({&msg, &msg_frametime, &msg_framerate, &str_spacer,
                            &framerate, i+1, frame_count, frametime, *max_xy});
                        mvaddstr(max_xy->y-1, 0, msg);

                        // Update the screen every frame
                        refresh();
                    }
                }
            }

            // Free asprintf memory 
            free(msg_frametime);
            free(msg_framerate);
            free(msg);
        }
    public:
        // Start the animation thread 
        void start(bool *return_signal) {
            this->animator = std::thread(animate_frames,
                this->frames,
                this->target_framerate,
                &this->max_xy,
                &this->mtx,
                return_signal);
        }

        void update() {
            this->max_xy = {
                getmaxx(stdscr),
                getmaxy(stdscr)
            };

            clear();
        }

        FrameAnimator(Animation animation) {
            this->setup(animation.frames, animation.framerate);
            this->update();
        }

        FrameAnimator();
};

struct PortableString {
    const char *str;
    size_t len;
};

/*  Deprecated: see FrameAnimator
    Basic string reveal example subclass */
class StringAnimator: public Animator {
    private:
        PortableString p_str;
        useconds_t interval;
        
        // Initialise stdscr and properties 
        WINDOW *setup(const char *str, useconds_t interval) {
            WINDOW *ret = scr_setup();
            this->p_str = {str, strlen(str)};
            this->interval = interval;

            return ret;
        }

        // Render loop for thread 
        static void animate_string(PortableString p_str, useconds_t interval, std::timed_mutex *mtx, bool *completed) {
            char current_ch;
            while (!*completed) {
                clear();
                /* Print each char with a mutex delay/lock */
                for (int i=0; i<p_str.len; i++) {
                    if (!*completed) {
                        current_ch = p_str.str[i];
                        addch(current_ch);
                        refresh();
                        mtx->try_lock_for(std::chrono::microseconds(interval));
                    }
                }
            }
        }
    public:
        void start(bool *return_signal) {
            this->animator = std::thread(animate_string, this->p_str, this->interval, &this->mtx, return_signal);
        }

        StringAnimator(const char *str, useconds_t interval) {
            this->setup(str, interval);
        }

        StringAnimator();
};