#pragma  once

#ifndef TEST_WINDOW_HPP
#define TEST_WINDOW_HPP

#include <window/sisters_sdl_window.hpp>
#include <cameras/ortho_camera.hpp>
#include <ecs/systems/ecs_sprite_renderer.hpp>

using namespace SDL;

class TestWindow : public Window {
    private:
        OrthoCamera camera;
        ECS_SpriteRendererPtr renderer;
    public:
        TestWindow();
        ~TestWindow();

        void init() override;
        void update() override;
        void stepUpdate(double ts) override;

        void render(double alpha) override;
};

#endif
