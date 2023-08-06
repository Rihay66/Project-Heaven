#include "../inc/gameHandler.hpp"

Renderer* renderer;
Camera* camera;
Player* plr;
GameObject* obj1;

//constructor
gameHandler::gameHandler(unsigned int width, unsigned int height, GLFWwindow* handle) : Width(width), Height(height), window(handle) {}

//destructor
gameHandler::~gameHandler(){
    //delete any pointers and clear resources (eg ResourceManager)
    delete camera;
    delete renderer;
    delete plr;
    delete obj1;
    ResourceManager::Clear();
}

void gameHandler::setGameState(int i){
    Game_State = (GAMESTATE)i;
}

void gameHandler::setControllerState(int i){
    Controller_State = (CONTROLSSTATE)i;
}

//TODO: Setup 2d physics
//TODO: Instanced rendering

void gameHandler::init(){
    //load all resources like shaders, textures
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

    //load textures
    ResourceManager::LoadTexture("textures/test.png", "test", true);
    ResourceManager::LoadTexture("textures/item.png", "item", true);
    ResourceManager::LoadTexture("textures/player.png", "player", true);

    //set up the renderer
    Shader spriteShader = ResourceManager::GetShader("sprite");
    spriteShader.Use();
    auto loc = glGetUniformLocation(spriteShader.ID, "image");
    int samplers[2] = {0, 1};
    glUniform1iv(loc, 2, samplers);

    renderer = new Renderer(spriteShader);

    //set up game objects and camera
    camera = new Camera(this->Width, this->Height, spriteShader, 150.0f);

    //set up a object
    glm::vec2 pos = glm::vec2(0.0f, 0.0f);
    
    pos = glm::vec2(0.0f, 0.0f);
    plr = new Player(pos, defaultSize, ResourceManager::GetTexture("pLayer"), PlayerSpeed);
    obj1 = new GameObject(pos, defaultSize, ResourceManager::GetTexture("item"));
}

void gameHandler::update(float deltaTime){
    //update values and check for physics and other things

    if(Game_State == GAME_DEBUG){ //Check if the game state is active or on debug
        camera->camInput(deltaTime, this->window);
    }else if(Game_State == GAME_ACTIVE){
        plr->playerInput(deltaTime, this->window, this->Controller_State, 0.2f);
        camera->follow(plr->position, plr->size);
    }
}

void gameHandler::render(){
    //render stuff regardless of state

    //render all objs on the vector objects

    renderer->Draw2D(plr, obj1, defaultSize);
}