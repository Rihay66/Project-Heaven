#include "../inc/gameHandler.hpp"

Renderer* renderer;
Camera* camera;
Player* plr;

//constructor
gameHandler::gameHandler(unsigned int width, unsigned int height, GLFWwindow* handle) : Width(width), Height(height), window(handle) {}

//destructor
gameHandler::~gameHandler(){
    //delete any pointers and clear resources (eg ResourceManager)
    delete camera;
    delete renderer;
    delete plr;
    delete phys;
    ResourceManager::Clear();
    pObjects.clear();
}

void gameHandler::setGameState(int i){
    Game_State = (GAMESTATE)i;
}

void gameHandler::setControllerState(int i){
    Controller_State = (CONTROLSSTATE)i;
}

//TODO: Fix the rendering order for different object list and single objects
//TODO: Setup box 2d
//TODO: Setup sound system
//TODO: UI and text

void gameHandler::init(){
    //load all resources like shaders, textures
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

    //load textures
    ResourceManager::LoadTexture("textures/test.png", "test", true);
    ResourceManager::LoadTexture("textures/player.png", "player", true);
    ResourceManager::LoadTexture("textures/item.png", "item", true);
    ResourceManager::LoadTexture("textures/flower.png", "flower", true);
    ResourceManager::LoadTexture("textures/default.png", "default", true);
    ResourceManager::LoadTexture("textures/transparent.png", "transparent", true);

    //bind all the textures from first to last
    for(int i = 0; i < ResourceManager::texList.size(); i++){
        //call to bind texture
        glBindTextureUnit(i, ResourceManager::texList[i].ID);
    }

    //set up the renderer
    Shader spriteShader = ResourceManager::GetShader("sprite");

    renderer = new Renderer(spriteShader, smallModelSize);

    //* The order of the objects affects how they're layered
    //set up game objects and camera
    camera = new Camera(this->Width, this->Height, spriteShader, 150.0f, 5.0f);

    glm::vec2 pos = glm::vec2(0.0f, 0.0f);
    
    plr = new Player(pos, standardSpriteSize, ResourceManager::GetTextureIndex("pLayer"), PlayerSpeed);

    /*
    //Creates objects and stores them in to the pObjects vector
    for(int y = 0; y < 75; y++){
        for(int x = 0; x < 75; x++){
            pos = glm::vec2(x, y);
            GameObject* temp = new GameObject(pos, standardSpriteSize, ResourceManager::GetTextureIndex("item"));

            //add to list
            pObjects.push_back(temp);
        }
    }
    */

    pos = glm::vec2(-5.0f, -8.0f);

    physicsObject* temp = new physicsObject(pos, standardSpriteSize + glm::vec2(5.0f, 5.0f), ResourceManager::GetTextureIndex("transparent"), glm::vec3(0.6f, 0.0f, 0.3f));

    //Add to render objects
    pObjects.push_back(temp);
    pObjects.push_back(plr);

    phys = new Physics();

    //Add physics objtect to physics class, EXCEPT the player
    phys->pObjs.push_back(temp);


    std::cout << "object size: " << pObjects.size() << std::endl;
}

void gameHandler::update(float deltaTime){
    //update values and check for physics and other things

    if(Game_State == GAME_DEBUG){ //Check if the game state is active or on debug
        camera->camInput(deltaTime, this->window);    
    }else if(Game_State == GAME_ACTIVE){
        plr->playerInput(deltaTime, this->window, this->Controller_State, 0.2f);
        camera->follow(plr->position, smallModelSize);
    }

    //* Do physics here
    phys->CheckCollisions(*plr);
}

void gameHandler::render(){
    //render stuff depending on the state of the game state enum
    if(Game_State == GAME_ACTIVE || Game_State == GAME_DEBUG){
        renderer->Draw2D(pObjects);
    }
}