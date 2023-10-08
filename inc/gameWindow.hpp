#pragma once

#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include <window/window.hpp>
#include "../inc/gameHandler.hpp"


class GameWindow : public Window{
    public:
        gameHandler* game;

        //Constructor/Destructor
        GameWindow(int w, int h, const char* name);
        ~GameWindow();

        void init() override;
        void input(SDL_Event handle) override;
        void update() override;
        void render() override;
};

#endif