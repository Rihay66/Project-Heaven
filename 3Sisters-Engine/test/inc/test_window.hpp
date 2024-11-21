#pragma  once

#ifndef TEST_WINDOW_HPP
#define TEST_WINDOW_HPP

#include <window/glfw_window.hpp>
#include <ecs/systems/ecs_sprite_renderer.hpp>
#include <cameras/ortho_camera.hpp>

class TestWindow : public Window {
    private:
        ECS_2DRenderer renderer;
        OrthoCamera camera;
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
