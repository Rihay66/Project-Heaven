#include "../inc/gameHandler.hpp"

Renderer* renderer;
Camera* camera;
Player* plr;
GameObject* obj1;
GameObject* obj2;
GameObject* obj3;

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
    pObjects.clear();
}

void gameHandler::setGameState(int i){
    Game_State = (GAMESTATE)i;
}

void gameHandler::setControllerState(int i){
    Controller_State = (CONTROLSSTATE)i;
}

//TODO: Setup own 2D hysucs using BSP and AABB
//TODO: Setup sound system
//TODO: Make texture's ID overwrittable to be able to organize the texture IDs
//TODO: UI and text

void gameHandler::init(){
    //load all resources like shaders, textures
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

    //load textures
    //* NOTE: The order of how the textures are load also affects the rendering of objects being either on top or below
    ResourceManager::LoadTexture("textures/test.png", "test", true);
    ResourceManager::LoadTexture("textures/player.png", "player", true);
    ResourceManager::LoadTexture("textures/item.png", "item", true);
    ResourceManager::LoadTexture("textures/flower.png", "flower", true);

    //bind all the textures from first to last
    for(int i = 0; i < ResourceManager::texList.size(); i++){
        //call to bind texture
        std::cout << ResourceManager::texList[i].ID << std::endl;
        glBindTextureUnit(i, ResourceManager::texList[i].ID);
    }

    //set up the renderer
    Shader spriteShader = ResourceManager::GetShader("sprite");

    renderer = new Renderer(spriteShader, smallModelSize);

    //set up game objects and camera
    camera = new Camera(this->Width, this->Height, spriteShader, 150.0f, 2.0f);

    glm::vec2 pos = glm::vec2(0.0f, 0.0f);
    
    plr = new Player(pos, standardSpriteSize, ResourceManager::GetTextureIndex("pLayer"), PlayerSpeed);
    
    //set the player to be collidable
    plr->collidable = true;
    
    pos = glm::vec2(-1.0f, -1.0f);
    obj1 = new GameObject(pos, standardSpriteSize, ResourceManager::GetTextureIndex("item"));
    pos = glm::vec2(-2.0f, -2.0f);
    obj2 = new GameObject(pos, standardSpriteSize, ResourceManager::GetTextureIndex("test"));
    pos = glm:: vec2(-3.0f, 0.0f);
    obj3 = new GameObject(pos, standardSpriteSize, ResourceManager::GetTextureIndex("flower"));

    pObjects.push_back(obj1);
    pObjects.push_back(obj2);
    pObjects.push_back(obj3);
    pObjects.push_back(plr);
}

void gameHandler::update(float deltaTime){
    //update values and check for physics and other things

    if(Game_State == GAME_DEBUG){ //Check if the game state is active or on debug
        camera->camInput(deltaTime, this->window);    
    }else if(Game_State == GAME_ACTIVE){
        plr->playerInput(deltaTime, this->window, this->Controller_State, 0.2f);
        camera->follow(plr->position, smallModelSize);
    }
}

void gameHandler::render(){
    //render stuff depending on the state of the game state enum
    if(Game_State == GAME_ACTIVE || Game_State == GAME_DEBUG){
        renderer->Draw2D(pObjects);
    }
}