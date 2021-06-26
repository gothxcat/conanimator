/*
*   Animator base class
*/

#include <stdlib.h>
#include <ncurses.h>
#include <thread>
#include <future>
#include "../include/stdscr.hpp"

class Animator {
    protected:
        std::thread animator;
        std::timed_mutex mtx;
        virtual WINDOW *setup() { return nullptr; };

    public:
        virtual void start(bool *return_signal) {};

        void end() {
            this->mtx.unlock();
            this->animator.join();
            scr_end();
        }

        Animator() {};
};
