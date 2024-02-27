#include <window/window.hpp>

#include <iostream>

// static vars for tracking input

static bool isDebug = false;
static bool pressed = false;
static bool controllerCheck = false;

// callback function to move the OpenGL viewport to the GLFW window's position
static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

// constructor, intializes GLFW and GLAD then creates a window with the passed parameters
Window::Window(int h, int w, const char* name) : App_State(ACTIVE), Input_State(KM), width(0), height(0){

    // set local vars of the window size
    width = w;
    height = h;

    // init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false); //disable resizing the screen

    // create the window and check for errors
    handle = glfwCreateWindow(h, w, name, NULL, NULL);
    if(!handle){
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    // create window
    glfwMakeContextCurrent((GLFWwindow*)handle);

    // load glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to init GLAD!" << std::endl;
        exit(-1);
    }

    // set up call back to update the opengl window
    glfwSetFramebufferSizeCallback((GLFWwindow*)handle, framebuffer_size_callback);
    // enable vsync
    glfwSwapInterval(1);
    // set openGL window size
    glViewport(0, 0, h, w);

    // set up rendering for 2D
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //TODO: Create debug options for the window class to display a console to show any errors or messages
    //std::cout << "MSG: Window successfully created" << std::endl;
}

// destructor
Window::~Window(){
    // delete any pointers
    glfwTerminate();
}

void Window::getInput(){

    // debug enabler button - toggle
    if(glfwGetKey((GLFWwindow*)handle, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS && !pressed){
        isDebug = !isDebug;
        // check the isDebug value and set the proper app state
        if(isDebug){
            App_State = DEBUG;
            std::cout << "MSG: DEBUG IS ENABLED!" << std::endl;
        }
        else{
            App_State = ACTIVE;
            std::cout << "MSG: DEBUG IS DISABLED!" << std::endl;
        }
        pressed = !pressed;
    }else if(glfwGetKey((GLFWwindow*)handle, GLFW_KEY_GRAVE_ACCENT) == GLFW_RELEASE && pressed){
        pressed = !pressed;
    }

    //TODO: this checking system for joystick may need to check if joystick is indeed a gamepad
    // check for the first joystick
    if(glfwJoystickPresent(GLFW_JOYSTICK_1) == GLFW_TRUE && !controllerCheck){
        // print out that the joystick is connected
        const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
        std::cout << "MSG: Controller is connected! ID: " << name << std::endl;
        std::cout << "MSG: Controller input is enabled!" << std::endl;
        Input_State = KMANDCONTROLLER;
        controllerCheck = !controllerCheck;
    }else if(glfwJoystickPresent(GLFW_JOYSTICK_1) == GLFW_FALSE && controllerCheck){
        std::cout << "MSG: Controller is disconnected!" << std::endl;
        std::cout << "MSG: Controller input is disabled!" << std::endl;
        Input_State = KM;
        controllerCheck = !controllerCheck;
    }

    // call additional input
    this->input();
}


float Window::getDeltaTime(){
    // calculate delta time
    currentFrame = glfwGetTime();
    this->DeltaTime = currentFrame - lastFrame;
    if(this->DeltaTime > 0.25)
        this->DeltaTime = 0.25;
    lastFrame = currentFrame;

    return this->DeltaTime;
}

// single threaded runtime of update(), stepUpdate() and render()
void Window::runtime(){
    while(!glfwWindowShouldClose((GLFWwindow*)this->handle)){
        // get Deltatime
        this->getDeltaTime();

        // check for glfw events
        glfwPollEvents();

        // check for main window input
        getInput();

        //  accumulate time and do stepUpdate()
        this->accumulator += this->DeltaTime;
        while(this->accumulator >= fixedTimeStep){
            // update with fixed time step
            stepUpdate(this->fixedTimeStep);
            accumulator -= fixedTimeStep;
        } 
        // calculate alpha for linear interpolation
        this->alpha = accumulator / this->fixedTimeStep;

        // update any input, values, objects, loading etc..
        update();

        // render background
        glClear(GL_COLOR_BUFFER_BIT);

        // draw or render
        render(alpha);

        // swap buffers
        glfwSwapBuffers((GLFWwindow*)this->handle);
    }
}

// handle main window input function
void Window::input(){
    // here goes additional input that is within SDL event handling and getEvent() loop
    // can be overwritten 
}

// initialization
void Window::init(){
    // here goes the initial processing of shaders, textues, and objects
}

//updating
void Window::update(){
    // update any variables like moving objects or updating input
    //* NOTE: that any object that needs input will need to have reference to the window handles a parameter to be passed down
}

// update physics or ticks
void Window::stepUpdate(double ts){
    // used to update physics, ticks, or other with a fixed time step 
}

// rendering
void Window::render(double alpha){
    // here update visually the objects, shaders, textures, etc
}