/*
*   Animator base class
*/

#include <stdlib.h>
#include <ncurses.h>
#include <thread>
#include "../include/stdscr.hpp"

class Animator {
    protected:
        std::thread animator;
        virtual WINDOW *setup() { return nullptr; };

    public:
        virtual void start(bool *return_signal) {};

        void end() {
            this->animator.join();
            scr_end();
        }

        Animator() {};
};
