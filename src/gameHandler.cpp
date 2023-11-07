#include "../inc/gameHandler.hpp"

//Create game related objs
CameraController* camera;
Player* plr;
SoundSource* ss;
//Test objects
GameObject* render_test;
TestTriggerObject* trigger_test;

//constructor
gameHandler::gameHandler(unsigned int width, unsigned int height, GLFWwindow* handle) : Width(width), Height(height), window(handle) {}

//destructor
gameHandler::~gameHandler(){
    //delete any pointers and clear resources (eg ResourceManager)
    delete camera;
    delete renderer;
    delete plr;
    delete render_test;
    delete trigger_test;
    delete phys;
    //Set sound source to a null address
    ss = nullptr;
    delete ss;
    //Set sound engine to a null address
    soundEng = nullptr;
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

//TODO: UI and text

void gameHandler::init(){
    //load all resources like shaders, textures
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

    //load textures
    ResourceManager::LoadTexture("textures/default.png", "default", true);
    ResourceManager::LoadTexture("textures/test.png", "test", true);
    ResourceManager::LoadTexture("textures/player.png", "player", true);
    ResourceManager::LoadTexture("textures/item.png", "item", true);
    ResourceManager::LoadTexture("textures/flower.png", "flower", true);
    ResourceManager::LoadTexture("textures/transparent.png", "transparent", true);
    ResourceManager::LoadTexture("textures/crate.png", "crate",true);
    ResourceManager::LoadTexture("textures/porm.png", "porm", true);
    
    //Bind the textures that were loaded
    ResourceManager::BindTextures();

    //Init sound engine
    soundEng = new SoundEngine();
    //Load sound buffers
    soundEng->loadSoundBuffer("sounds/Vine-boom.wav", "sound");

    //Create a sound source for testing
    ss = new SoundSource();
    //load sound
    ss->loadSound(soundEng->getSoundBuffer("sound"), "test");

    //set up the renderer
    Shader spriteShader = ResourceManager::GetShader("sprite");
    renderer = new Renderer(spriteShader, smallModelSize);


    //* The order of the objects affects how they're layered
    //set up game objects and camera
    camera = new CameraController(this->Width, this->Height, this->window, spriteShader, 150.0f, 5.0f);

    glm::vec2 pos = glm::vec2(0.0f, 0.0f);
    
    plr = new Player(window, pos, standardSpriteSize, ResourceManager::GetTexture("player"), PlayerSpeed, 0.2f);

    pos = glm::vec2(-1.1f, 2.0f);

    PhysicsObject* temp = new PhysicsObject(pos, standardSpriteSize, ResourceManager::GetTexture("test"));
    temp->rotation = 45.0f;

    pos = glm::vec2(1.0f);
    PhysicsObject* test = new PhysicsObject(pos, standardSpriteSize + glm::vec2(1.0f, 0.0f), ResourceManager::GetTexture("transparent"), glm::vec4(1.0f, 1.0f, 0.5f, 1.0f));

    pos = glm::vec2(-4.0f, -4.0f);
    PhysicsObject* ground = new PhysicsObject(pos, standardSpriteSize + glm::vec2(12.0f, 0.0f), ResourceManager::GetTexture("default"));

    pos = glm::vec2(-4.0f, 5.0f);
    PhysicsObject* roof = new PhysicsObject(pos, standardSpriteSize + glm::vec2(12.0f, 0.0f), ResourceManager::GetTexture("default"));

    pos = glm::vec2(3.0f, 0.5f);
    PhysicsObject* wall = new PhysicsObject(pos, standardSpriteSize + glm::vec2(0.0f, 9.0f), ResourceManager::GetTexture("default"));

    pos = glm::vec2(-2.0f, 0.0f);
    PhysicsObject* platform = new PhysicsObject(pos, standardSpriteSize + glm::vec2(1.0f, -0.5f), ResourceManager::GetTexture("default"));

    pos = glm::vec2(-2.5f, -2.0f);
    PhysicsObject* crate = new PhysicsObject(pos, standardSpriteSize, ResourceManager::GetTexture("crate"));

    //Make a test object to draw seperately from the list
    pos = glm::vec2(-4.5f, 0.5f);
    render_test = new GameObject(pos, standardSpriteSize, ResourceManager::GetTexture("item"), glm::vec4(1.0f, 1.0f, 1.0f, 0.2f));

    //Make a trigger object
    pos = glm::vec2(-7.0f, 0.0f);
    trigger_test = new TestTriggerObject(pos, standardSpriteSize, ResourceManager::GetTexture("transparent"), glm::vec4(0.1f, 1.0f, 0.1f, 1.0f));
    //Change trigger type
    trigger_test->trigType = TriggerType::Exit;

    //Change default values
    trigger_test->maxTimeToTrigger = 50;

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
    renderList.push_back(render_test);
    renderList.push_back(trigger_test);
    renderList.push_back(plr);

    //Init physics system
    phys = new Physics();

    //Add physics object to physics class
    phys->rigidbodyObjs.push_back(temp);
    phys->rigidbodyObjs.push_back(test);
    phys->rigidbodyObjs.push_back(ground);
    phys->rigidbodyObjs.push_back(roof);
    phys->rigidbodyObjs.push_back(platform);
    phys->rigidbodyObjs.push_back(wall);
    phys->rigidbodyObjs.push_back(plr);
    phys->rigidbodyObjs.push_back(crate);

    //Add trigger object to physics class
    phys->triggerObjs.push_back(trigger_test);

    //Init the physics system
    phys->init(glm::vec2(0.0f, 0.0f));

    std::cout << "objects within tag system: " << TagSystem::getAmountOfObjects() << "\n";
    std::cout << "object size: " << renderList.size() << std::endl;
}

void gameHandler::update(float deltaTime){
    //update values and check for physics and other things

    //rotate the "render_test"
    render_test->rotation += 5.0f * deltaTime;

    //* Do physics here
    phys->CheckCollisions(deltaTime);

    if(Game_State == GAME_DEBUG){ //Check if the game state is active or on debug
        plr->isDebug = true;
    }else if(Game_State == GAME_ACTIVE){
        plr->isDebug = false;
    }

    if(glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS){
        ss->play("test");
    }

    //Check the controller state and change the player isDebug boolean
    if(Controller_State == CONTROLSSTATE::KEYBOARDMOUSE){
        plr->isController = false;
    }else if(Controller_State == CONTROLSSTATE::KMCONTROLLER){
        plr->isController = true;
    }

}

void gameHandler::render(float deltaTime){

    if(Game_State == GAME_DEBUG){ //Check if the game state is active or on debug
        camera->inputMovement(deltaTime);    
    }else if(Game_State == GAME_ACTIVE){
        camera->followPos(plr->position, smallModelSize);
    }

    //render stuff depending on the state of the game state enum
    if(Game_State == GAME_ACTIVE || Game_State == GAME_DEBUG){
        //Render a list of objects
        renderer->Draw2D(renderList);
        //Draw a single object
        renderer->Draw2D(render_test);
    }
}