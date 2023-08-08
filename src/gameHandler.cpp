#include "../inc/gameHandler.hpp"

Renderer* renderer;
Camera* camera;
Player* plr;
GameObject* obj1;
GameObject* obj2;
GameObject* obj3;

//comparison 
static bool compareObjs(const GameObject* obj1, const GameObject* obj2){
    return obj1->sprite.ID == obj2->sprite.ID;
}

//constructor
gameHandler::gameHandler(unsigned int width, unsigned int height, GLFWwindow* handle) : Width(width), Height(height), window(handle) {}

//destructor
gameHandler::~gameHandler(){
    //delete any pointers and clear resources (eg ResourceManager)
    delete camera;
    delete renderer;
    delete plr;
    delete obj1;
    delete obj2;
    delete obj3;
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
    
    int samplers[32];

    //set up samplers array
    for(int i = 0; i < 32; i++){
        samplers[i] = i;
    }

    glUniform1iv(loc, 32, samplers);

    renderer = new Renderer(spriteShader);

    //set up game objects and camera
    camera = new Camera(this->Width, this->Height, spriteShader, 150.0f);

    //set up a object
    glm::vec2 pos = glm::vec2(0.0f, 0.0f);
    
    pos = glm::vec2(0.0f, 0.0f);
    plr = new Player(pos, defaultSize, ResourceManager::GetTexture("pLayer"), PlayerSpeed);
    obj1 = new GameObject(pos, defaultSize, ResourceManager::GetTexture("item"));
    pos = glm::vec2(1.0f, 1.0f);
    obj2 = new GameObject(pos, defaultSize, ResourceManager::GetTexture("test"));
    pos = glm:: vec2(2.0f, 2.0f);
    obj3 = new GameObject(pos, defaultSize, ResourceManager::GetTexture("player"));

    objects.push_back(plr);
    objects.push_back(obj1);
    objects.push_back(obj2);
    objects.push_back(obj3);
}

void gameHandler::update(float deltaTime){
    //update values and check for physics and other things

    if(Game_State == GAME_DEBUG){ //Check if the game state is active or on debug
        camera->camInput(deltaTime, this->window);
    }else if(Game_State == GAME_ACTIVE){
        camera->follow(plr->position, plr->size);
        plr->playerInput(deltaTime, this->window, this->Controller_State, 0.2f);
    }
}

void gameHandler::render(){
    //render stuff regardless of state

    //render all objs on the vector objects

    renderer->Draw2D(objects, defaultSize);
}