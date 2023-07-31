#include "../inc/gameHandler.h"

#include <iostream>

Renderer* renderer;
Camera* camera;

//constructor
gameHandler::gameHandler(unsigned int width, unsigned int height, GLFWwindow* handle) : Width(width), Height(height), window(handle) {}

//destructor
gameHandler::~gameHandler(){
    //delete any pointers and clear resources (eg ResourceManager)
    delete camera;
    delete renderer;
    ResourceManager::Clear();
}

void gameHandler::setGameState(int i){
    State = (GAMESTATE)i;
}

void gameHandler::init(){
    //load all resources like shaders, textures
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    //set up projection
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    ResourceManager::LoadTexture("textures/test.png", "test", true);

    //set up the renderer
    Shader spriteShader = ResourceManager::GetShader("sprite");
    renderer = new Renderer(spriteShader);

    //set up game objects and camera
    camera = new Camera(Width, Height, spriteShader, 150.0f);

}

void gameHandler::update(float deltaTime){
    //update values and check for physics and other things

    if(State == GAME_DEBUG){ //Check if the game state is active or on debug
        camera->camInput(deltaTime, window);
    }
}

void gameHandler::render(){
    //render stuff regardless of state
    Texture2D tex = ResourceManager::GetTexture("Test");
    renderer->Draw2D(tex, glm::vec2(200.0f, 200.0f), glm::vec2(50.0f, 150.0f), 0.0f);
}