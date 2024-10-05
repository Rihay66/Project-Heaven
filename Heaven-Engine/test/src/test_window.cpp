#include "../inc/test_window.hpp"
#include <ecs/default_components.hpp>
#include "engine/text_renderer.hpp"
#include "input/glfw_keyboard.hpp"
#include "resourceSystems/managers/resource_manager.hpp"
#include <engine/sprite_renderer.hpp>
#include <resourceSystems/managers/sound_manager.hpp>
#include <engine/physics.hpp>
#include <input/glfw_gamepad_manager.hpp>
#include <input/glfw_keyboard_manager.hpp>

TestWindow::TestWindow(int w, int h) : Window(w, h){
    setFixedTimeStep(1.0/60.0f);
    setTargetTimeStep(1.0f/60.0f);
}

TestWindow::~TestWindow() {}

std::string TestWindow::GetFrameTime(){
    this->currentTime = glfwGetTime();
    this->timeDiff = this->currentTime - this->prevTime;
    this->counter++;
    if(this->timeDiff >= 1.0 / 30.0){
        //display frame per second & frame time
        std::string FPS = "" + std::to_string((1.0 / this->timeDiff) * this->counter);
        FPS = FPS.substr(0, FPS.find("."));
        this->prevTime = this->currentTime;
        this->counter = 0;
        //Return text
        frame = FPS;
    }
    return frame;
}

void TestWindow::init(){
    // init ECS
    ECS::Init('r');

    // register components
    ECS::RegisterComponent<Transform2D>();
    ECS::RegisterComponent<Texture2D>();
    ECS::RegisterComponent<Renderer2D>();
    ECS::RegisterComponent<Rigidbody2D>();
    ECS::RegisterComponent<BoxCollider2D>();
    ECS::RegisterComponent<Gamepad>();

    // initialize ECS renderer
    renderer = ECS::RegisterSystem<ECS_SpriteRenderer>();

    // initialize ECS Physics
    physics = ECS::RegisterSystem<ECS_Physics>();

    // register signature to render system
    ECS::SetSystemSignature<ECS_SpriteRenderer>(ECS::GetComponentType<Transform2D>(), 
        ECS::GetComponentType<Texture2D>(), ECS::GetComponentType<Renderer2D>());

    ECS::SetSystemSignature<ECS_Physics>(ECS::GetComponentType<Transform2D>(), 
        ECS::GetComponentType<Rigidbody2D>(), ECS::GetComponentType<BoxCollider2D>());

    // Load a shader
    ResourceManager::LoadShader("shaders/quad.vs", "shaders/quad.frag", nullptr, "sprite");
    ResourceManager::LoadShader("shaders/text.vs", "shaders/text.frag", nullptr, "text");
    ResourceManager::LoadShader("shaders/line.vs", "shaders/line.frag", nullptr, "line");

    // set the camera dimensions
    cam.setDimensions(getWidth(), getHeight());
    // calculate the projection for each shader
    cam.calculateProjectionView(ResourceManager::GetShader("sprite"));
    cam.calculateProjectionView(ResourceManager::GetShader("line"));

    // Load a texture
    ResourceManager::LoadTexture("textures/default.png", "test", true);
    ResourceManager::LoadTexture("textures/sheet.png", "sheet", true);

    // create a sub texture
    ResourceManager::LoadSubTexture("test", ResourceManager::GetTexture("sheet"), {9,3}, {128, 128});

    // Load a font
    ResourceManager::LoadFontTexture("fonts/Arcade.ttf", 36, "arcade", false);

    // init the sprite renderer
    SpriteRenderer::Init(ResourceManager::GetShader("sprite"), ResourceManager::GetShader("line"), glm::vec2(30.0f));

    // init the text renderer
    TextRenderer::Init(getWidth(), getHeight(), ResourceManager::GetShader("text"));

    // Load a sound
    SoundManager::CreateSoundCollection("test", "lofi", "sounds/lofi.wav");
    // Load another sound
    SoundManager::AddSoundToBuffer("test", "music", "sounds/music.wav");

    source.setBuffer(SoundManager::GetSoundFromBufferInColleciton("test", "lofi"));
    
    // init physics
    Physics::Init();

    // create 100 entities
    for(int i = 0; i < 4; i++){
        // create entity
        Entity entity = ECS::CreateEntity();

        ECS::AddComponent(entity, Transform2D{
            .position = glm::vec2(20, (i * 3) + 10),
            .rotation = 0.0f,
            .size = glm::vec2(1.0f)
        });

        ECS::AddComponent(entity, Renderer2D{
            .color = glm::vec4(1.0f)
        });

        ECS::AddComponent(entity, Rigidbody2D{
            
        });

        ECS::AddComponent(entity, BoxCollider2D{});

        // store entity
        entities.push_back(entity);
    }

    ECS::AddComponent(entities[0], Texture2D{
        .texIndex = ResourceManager::GetTextureIndex("test")
    });

    ECS::AddComponent(entities[2], Texture2D{
        .texIndex = ResourceManager::GetTextureIndex("test")
    });

    ECS::GetComponent<Renderer2D>(entities[2]).color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

    ECS::AddComponent(entities[3], Texture2D{
        .texIndex = ResourceManager::GetTextureIndex("test")
    });

    ECS::GetComponent<Renderer2D>(entities[3]).color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

    ECS::GetComponent<Transform2D>(entities[0]).size = glm::vec2 (10.0f, 1.0f);

    ECS::AddComponent(entities[1], Texture2D{
        .texIndex = ResourceManager::GetTextureIndex("test")
    });

    ECS::GetComponent<Rigidbody2D>(entities[1]).Type = BodyType::Dynamic;

    ECS::GetComponent<Transform2D>(entities[1]).rotation = 0.5f;

    ECS::GetComponent<BoxCollider2D>(entities[1]).size = glm::vec2(0.75f);

    ECS::GetComponent<Rigidbody2D>(entities[2]).Type = BodyType::Dynamic;
    ECS::GetComponent<Rigidbody2D>(entities[2]).fixedRotation = true;

    ECS::GetComponent<Rigidbody2D>(entities[3]).Type = BodyType::Dynamic;
    ECS::GetComponent<Rigidbody2D>(entities[3]).fixedRotation = true;

    auto& transform = ECS::GetComponent<Transform2D>(entities[1]);
    transform.size = glm::vec2(2.0f);

    // initialize all rigidbodies
    for(auto const& i : entities){
        physics->registerEntity(i);
    }

    // set up gamepad query
    GamepadManager::InitializeQuery();

    // give entity 4 the gamepad
    ECS::AddComponent(entities[2], Gamepad{});
    // give entity 3 a gamepad
    ECS::AddComponent(entities[3], Gamepad{});

    auto& gamepad0 = ECS::GetComponent<Gamepad>(entities[2]);
    auto& gamepad1 = ECS::GetComponent<Gamepad>(entities[3]);

    // set the entity's gamepad into the manager to be set
    GamepadManager::SetGamepad(gamepad0, 0);

    // set the entity's gamepad into the manager to be set
    GamepadManager::SetGamepad(gamepad1, 1);

    // set the keyboard
    KeyboardManager::SetWindowHandle(getWindowHandle());
}

void TestWindow::input(){
    // poll inputs from gamepads
    GamepadManager::PollInputs();

    // check for escape key to exit window
    if(glfwGetKey(this->getWindowHandle(), GLFW_KEY_ESCAPE) == GLFW_PRESS){
        // exit window
        glfwSetWindowShouldClose(this->getWindowHandle(), true);
    }
}

void TestWindow::update(){

}

void TestWindow::stepUpdate(double ts){
    // play sound
    //source.play(true);

    // update physics
    Physics::UpdateWorld(ts);
    physics->update();

    //?Input for player 1

    // check for input from controller
    if(getKeyInput(GLFW_KEY_A)){
        // move left
        b2Body_ApplyForce(ECS::GetComponent<Rigidbody2D>(entities[2]).runtimeBody, {-15, 0}, 
            b2Body_GetWorldPoint(ECS::GetComponent<Rigidbody2D>(entities[2]).runtimeBody, {ECS::GetComponent<Transform2D>(entities[2]).position.x, ECS::GetComponent<Transform2D>(entities[2]).position.y}), true);
    }

    if(getKeyInput(GLFW_KEY_D)){
        // move right
        b2Body_ApplyForce(ECS::GetComponent<Rigidbody2D>(entities[2]).runtimeBody, {15, 0}, 
            b2Body_GetWorldPoint(ECS::GetComponent<Rigidbody2D>(entities[2]).runtimeBody, {ECS::GetComponent<Transform2D>(entities[2]).position.x, ECS::GetComponent<Transform2D>(entities[2]).position.y}), true);
    }

    //? Input for player 2

    // check for input from controller
    if(getButtonInput(ECS::GetComponent<Gamepad>(entities[3]), PLAYSTATION_BUTTON_DPAD_LEFT)){
        // move left
        b2Body_ApplyForce(ECS::GetComponent<Rigidbody2D>(entities[3]).runtimeBody, {-15, 0}, 
            b2Body_GetWorldPoint(ECS::GetComponent<Rigidbody2D>(entities[3]).runtimeBody, {ECS::GetComponent<Transform2D>(entities[3]).position.x, ECS::GetComponent<Transform2D>(entities[3]).position.y}), true);
    }

    if(getButtonInput(ECS::GetComponent<Gamepad>(entities[3]), PLAYSTATION_BUTTON_DPAD_RIGHT)){
        // move left
        b2Body_ApplyForce(ECS::GetComponent<Rigidbody2D>(entities[3]).runtimeBody, {15, 0}, 
            b2Body_GetWorldPoint(ECS::GetComponent<Rigidbody2D>(entities[3]).runtimeBody, {ECS::GetComponent<Transform2D>(entities[3]).position.x, ECS::GetComponent<Transform2D>(entities[3]).position.y}), true);
    }
}

void TestWindow::render(double alpha){
    //! No need to recalculate projection if camera doesn't move

    //render background
    glClearColor(0.35f, 0.35f, 0.35f, 1.0f);

    // render all entities
    renderer->render(alpha);

    // init the text renderer
    TextRenderer::DisplayText(ResourceManager::GetFontTexture("arcade"), this->GetFrameTime(), glm::vec2(getWidth() / 2.3f, getHeight() / 2.3f), glm::vec2(1.0f), glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
    
    //? draw a line
    physics->renderAllBoxColliders();
    
    //std::cout << "Quad Count: " << SpriteRenderer::stats.quadCount << "\n";
    //std::cout << "Draw Count: " << SpriteRenderer::stats.drawCount << "\n";
}