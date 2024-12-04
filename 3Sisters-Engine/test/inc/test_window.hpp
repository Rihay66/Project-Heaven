#pragma  once

#ifndef TEST_WINDOW_HPP
#define TEST_WINDOW_HPP

#include <window/glfw_window.hpp>

class TestWindow : public Window {
    private:

    public:
        TestWindow();
        ~TestWindow();

        void init() override;
        void update() override;
        void stepUpdate(double ts) override;

        void render(double alpha) override;
};

#endif
