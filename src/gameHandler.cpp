#include "../inc/gameHandler.hpp"

//Create obj
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
    delete soundEng;
    ResourceManager::Clear();
    renderList.clear();
}

void gameHandler::setGameState(int i){
    Game_State = (GAMESTATE)i;
}

void gameHandler::setControllerState(int i){
    Controller_State = (CONTROLSSTATE)i;
}

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
    ResourceManager::LoadTexture("textures/crate.png", "crate",true);
    ResourceManager::LoadTexture("textures/porm.png", "porm", true);

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
    
    plr = new Player(window, pos, standardSpriteSize, ResourceManager::GetTexture("player"), PlayerSpeed, 0.2f);


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

    pos = glm::vec2(-1.1f, 2.0f);

    physicsObject* temp = new physicsObject(pos, standardSpriteSize, ResourceManager::GetTexture("test"));
    temp->rotation = 45.0f;

    pos = glm::vec2(1.0f);
    physicsObject* test = new physicsObject(pos, standardSpriteSize + glm::vec2(1.0f, 0.0f), ResourceManager::GetTexture("transparent"), glm::vec3(0.1f, 0.7f, 0.1f));

    pos = glm::vec2(-5.0f, -4.0f);
    physicsObject* ground = new physicsObject(pos, standardSpriteSize + glm::vec2(10.0f, 0.0f), ResourceManager::GetTexture("default"));

    pos = glm::vec2(-5.0f, 5.0f);
    physicsObject* roof = new physicsObject(pos, standardSpriteSize + glm::vec2(10.0f, 0.0f), ResourceManager::GetTexture("default"));

    pos = glm::vec2(5.0f, -3.0f);
    physicsObject* wall = new physicsObject(pos, standardSpriteSize + glm::vec2(0.0f, 8.0f), ResourceManager::GetTexture("default"));

    pos = glm::vec2(-2.5f, 0.0f);
    physicsObject* platform = new physicsObject(pos, standardSpriteSize + glm::vec2(1.0f, -0.5f), ResourceManager::GetTexture("default"));

    pos = glm::vec2(-2.5f, -2.0f);
    physicsObject* crate = new physicsObject(pos, standardSpriteSize, ResourceManager::GetTexture("crate"));

    //Change rb type
    ground->rb.Type = BodyType::Static;
    roof->rb.Type = BodyType::Static;
    wall->rb.Type = BodyType::Static;
    platform->rb.Type = BodyType::Static;

    //Change params of objs
    ground->collider.friction = 8.0f;
    crate->collider.density = 5.0f;

    //Add to render objects
    renderList.push_back(ground);
    renderList.push_back(platform);
    renderList.push_back(temp);
    renderList.push_back(test);
    renderList.push_back(roof);
    renderList.push_back(wall);
    renderList.push_back(crate);
    renderList.push_back(plr);

    phys = new Physics();

    //Add physics objtect to physics class
    phys->pObjs.push_back(temp);
    phys->pObjs.push_back(test);
    phys->pObjs.push_back(ground);
    phys->pObjs.push_back(roof);
    phys->pObjs.push_back(platform);
    phys->pObjs.push_back(wall);
    phys->pObjs.push_back(plr);
    phys->pObjs.push_back(crate);

    //Init the physics system
    phys->init(glm::vec2(0.0f, 0.0f));

    std::cout << "object size: " << renderList.size() << std::endl;
}

void gameHandler::update(float deltaTime){
    //update values and check for physics and other things

    //* Do physics here
    phys->CheckCollisions(deltaTime);

    if(Game_State == GAME_DEBUG){ //Check if the game state is active or on debug
        camera->camInput(deltaTime, this->window);    
        plr->isDebug = true;
    }else if(Game_State == GAME_ACTIVE){
        camera->follow(plr->position, smallModelSize);
        plr->isDebug = false;
    }

    //Check the controller state and change the player isDebug boolean
    if(Controller_State == CONTROLSSTATE::KEYBOARDMOUSE){
        plr->isController = false;
    }else if(Controller_State == CONTROLSSTATE::KMCONTROLLER){
        plr->isController = true;
    }

}

void gameHandler::render(){
    //render stuff depending on the state of the game state enum
    if(Game_State == GAME_ACTIVE || Game_State == GAME_DEBUG){
        renderer->Draw2D(renderList);
    }
}