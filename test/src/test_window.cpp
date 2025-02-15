#include "../inc/test_window.hpp"
#include <resourceSystems/managers/resource_manager.hpp>
#include <engine/sprite_renderer.hpp>
#include <engine/text_renderer.hpp>

TestWindow::TestWindow() : Window(){

}

TestWindow::~TestWindow() {
    
}

void TestWindow::init(){  
    // load a quad shader
    ResourceManager::LoadShader("shaders/quad_es.vs", "shaders/quad_es.frag", nullptr, "quad");
    // load a line shader
    ResourceManager::LoadShader("shaders/line_es.vs", "shaders/line_es.frag", nullptr, "line");
    // load a text shader
    ResourceManager::LoadShader("shaders/text_es.vs", "shaders/text_es.frag", nullptr, "text");
    
    // generate white texture
    ResourceManager::GenerateWhiteTexture();
    // load a texture
    ResourceManager::LoadTexture("textures/sisters.png", "sisters");
    // load a font
    ResourceManager::LoadFontTexture("fonts/November.ttf", 36, "font");
    
    // set up camera
    camera.setDimensions(getWidth(), getHeight());
    camera.calculateProjectionView(ResourceManager::GetShader("quad"));
    camera.calculateProjectionView(ResourceManager::GetShader("line"));
    camera.calculateProjectionView(ResourceManager::GetShader("text"));

    // set up renderers
    SpriteRenderer::Init(ResourceManager::GetShader("quad"), ResourceManager::GetShader("line"), glm::vec2(15.0f), glm::vec2(15.0f));
    TextRenderer::Init(ResourceManager::GetShader("text"));
}

void TestWindow::stepUpdate(double ts){

}

void TestWindow::update(){

}

void TestWindow::render(double alpha){
    // render background
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    // test quad renderer
    SpriteRenderer::StackQuad(ResourceManager::GetTextureIndex("default"), glm::vec2(15.0f), glm::vec2(2.0f), 0.0f, glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
    SpriteRenderer::StackQuad(ResourceManager::GetTextureIndex("sisters"), glm::vec2(5.0f), glm::vec2(5.0f), 45.0f);

    SpriteRenderer::FlushQuads();

    SpriteRenderer::DrawQuad(ResourceManager::GetTextureIndex("default"), glm::vec2(40.0f, 20.0f), glm::vec2(10.0f), 0.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    // test line renderer
    SpriteRenderer::DrawLine(glm::vec2(1.0f), glm::vec2(10.0f));

    // render text
    TextRenderer::DrawText(ResourceManager::GetFontTexture("font"), "HELLO world!", glm::vec2(100.0f, 200.0f), glm::vec2(1.0f));
}
