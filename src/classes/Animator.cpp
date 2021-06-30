/*
*   Animator
*   Visual animator base class
*/

#include <stdlib.h>
#include <ncurses.h>
#include <thread>
#include <future>

// Program headers
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

        void end() {
            // Interrupt mutex timers, merge the threads and restore the ncurses screen 
            this->mtx.unlock();
            this->animator.join();
            scr_end();
        }

        Animator() {};
};