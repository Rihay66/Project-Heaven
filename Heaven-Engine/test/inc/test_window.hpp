#pragma  once

#ifndef TEST_WINDOW_HPP
#define TEST_WINDOW_HPP

#include <window/glfw_window.hpp>

#include <soundComponents/sound_source.hpp>

class TestWindow : public Window {
    private:
        SoundSource* source;

    public:
        TestWindow(int w, int h);
        ~TestWindow();

        void init() override;
        void input() override;
        void update() override;
        void stepUpdate(double ts) override;

        void render(double alpha) override;
};

#endif