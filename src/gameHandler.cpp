#include "../inc/gameHandler.h"

Renderer* renderer;
Camera* camera;
GameObject* obj1;
GameObject* obj2;
Player* plr;

//constructor
gameHandler::gameHandler(unsigned int width, unsigned int height, GLFWwindow* handle) : Width(width), Height(height), window(handle) {}

//destructor
gameHandler::~gameHandler(){
    //delete any pointers and clear resources (eg ResourceManager)
    delete camera;
    delete renderer;
    delete obj1;
    delete obj2;
    delete plr;
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
    //load textures
    ResourceManager::LoadTexture("textures/test.png", "test", true);
    ResourceManager::LoadTexture("textures/item.png", "item", true);
    ResourceManager::LoadTexture("textures/player.png", "player", true);

    //set up the renderer
    Shader spriteShader = ResourceManager::GetShader("sprite");
    renderer = new Renderer(spriteShader);

    //set up game objects and camera
    camera = new Camera(this->Width, this->Height, spriteShader, 150.0f);

    //set up a object
    glm::vec2 pos = glm::vec2(200.0f, 200.0f);
    obj1 = new GameObject(pos, glm::vec2(50.0f, 150.0f), ResourceManager::GetTexture("Test"), glm::vec2(0.0f));
    pos = glm::vec2(500.0f, 500.0f);
    obj2 = new GameObject(pos, glm::vec2(50.0f, 150.0f), ResourceManager::GetTexture("item"), glm::vec2(0.0f));
    pos = glm::vec2(400.0f, 40.0f);
    plr = new Player(pos, glm::vec2(50.0f, 150.0f), ResourceManager::GetTexture("pLayer"), glm::vec2(0.0f, 0.0f), 150.0f);
}

void gameHandler::update(float deltaTime){
    //update values and check for physics and other things

    if(State == GAME_DEBUG){ //Check if the game state is active or on debug
        camera->camInput(deltaTime, this->window);
    }else if(State == GAME_ACTIVE){
        //TODO: Make a moving player with input
        plr->playerInput(deltaTime, this->window);
        camera->follow(plr->position, plr->size);
    }
}

void gameHandler::render(){
    //render stuff regardless of state
    obj1->Draw2D(renderer);
    obj2->Draw2D(renderer);
    plr->Draw2D(renderer);
}