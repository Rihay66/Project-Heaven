#pragma  once

#ifndef TEST_WINDOW_HPP
#define TEST_WINDOW_HPP

#include <window/glfw_window.hpp>

#include <soundComponents/sound_source.hpp>
#include <cameras/ortho_camera.hpp>
#include <engine/text_renderer.hpp>

class TestWindow : public Window {
    private:
        OrthoCamera* cam;
        SoundSource* source;
        TextRenderer* text;

        //vars used for frame profiling
        double prevTime = 0.0;
        double currentTime = 0.0;
        double timeDiff;
        unsigned int counter = 0;

        std::string frame;

        const glm::vec4 customQuadVertexPositions[4] = {
            {0.5f, 0.5f, 0.0f, 1.0f},
            {-0.5f, 1.5f, 0.0f, 1.0f},
            {1.5f, -0.5f, 0.0f, 1.0f},
            {-0.5f, -0.5f, 0.0f, 1.0f}};
        

      public:
        TestWindow(int w, int h);
        ~TestWindow();

        std::string GetFrameTime();

        void init() override;
        void input() override;
        void update() override;
        void stepUpdate(double ts) override;

        void render(double alpha) override;
};

#endif