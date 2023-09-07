#include "../inc/window.hpp"

#include "../inc/gameHandler.hpp"

//Callback func
static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

//static vars
static bool isDebug = false;
static bool pressed = false;
static bool controllerCheck = false;
static bool controllerEnable = false;
static bool inputSwitch = false;
static bool vSyncSwitch = false;
static bool vSyncState = false;

//Instantiate gameHandler object
gameHandler* game;

//Window constructor, intializes GLFW and GLAD then creates a window with the passed parameters
Window::Window(int h, int w, const char* name) : DeltaTime(0), App_State(ACTIVE), Input_State(KM), width(0), height(0){

    //set local vars
    width = w;
    height = h;

    //init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false); //disable resizing the screen

    //create the window and check for errors
    handle = glfwCreateWindow(h, w, name, NULL, NULL);
    if(!handle){
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    //create window
    glfwMakeContextCurrent(handle);

    //load glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to init GLAD!" << std::endl;
        exit(-1);
    }

    //set up call back to update the opengl window
    glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);
    //enable vsync
    glfwSwapInterval(1);
    //set openGL window size
    glViewport(0, 0, h, w);

    //set up rendering for 2D
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "window successfully created" << std::endl;
}

//Destructor
Window::~Window(){
    //delete any pointers
    delete game;

    glfwTerminate();
}

//Handle main window input function
void Window::window_input(){
    //TODO: When a menu is created for entering and exiting the game this can be deprecated
    //Check if escape key being pressed to exit - button
    if(glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        //set window to close
        glfwSetWindowShouldClose(handle, true);
    }

    //debug enabler button - toggle
    if(glfwGetKey(handle, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS && !pressed){
        isDebug = !isDebug;
        //check the isDebug value and set the proper app state
        if(isDebug){
            App_State = DEBUG;
            std::cout << "MSG: DEBUG IS ENABLED!" << std::endl;
        }
        else{
            App_State = ACTIVE;
            std::cout << "MSG: DEBUG IS DISABLED!" << std::endl;
        }
        pressed = !pressed;
    }else if(glfwGetKey(handle, GLFW_KEY_GRAVE_ACCENT) == GLFW_RELEASE && pressed){
        pressed = !pressed;
    }

    //debug line wireframe - toggle
    if(isDebug && glfwGetKey(handle, GLFW_KEY_TAB) == GLFW_PRESS){
        //set writeframe
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }else{
        //stop wireframe
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    //check for joystick
    if(glfwJoystickPresent(GLFW_JOYSTICK_1) == true && !controllerCheck){
        //print out that the joystick is connected
        const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
        std::cout << "Controller is connected! ID: " << name << std::endl;
        controllerCheck = !controllerCheck;
    }else if(glfwJoystickPresent(GLFW_JOYSTICK_1) == false && controllerCheck){
        std::cout << "Controller is disconnected!" << std::endl;
        controllerCheck = !controllerCheck;
    }

    //enable or disable joystick if it's connected
    if(controllerCheck){
        //toggle
        if(glfwGetKey(handle, GLFW_KEY_TAB) == GLFW_PRESS && !inputSwitch){
        //check to enable or disable
        controllerEnable = !controllerEnable;
        if(controllerEnable){
            //switch to use controller
            std::cout << "MSG: Controller input is enabled!" << std::endl;
            Input_State = KMANDCONTROLLER;
        }else{
            std::cout << "MSG: Controller input is disabled!" << std::endl;
            Input_State = KM;
        }
        inputSwitch = !inputSwitch;
        }else if(glfwGetKey(handle, GLFW_KEY_TAB) == GLFW_RELEASE && inputSwitch){
            inputSwitch = !inputSwitch;
        }
    }

    //check to enable or disable vsync - toggle
    if(isDebug){
        if(glfwGetKey(handle, GLFW_KEY_V) == GLFW_PRESS && !vSyncSwitch){
            vSyncState = !vSyncState;
            //check to disable or enable vsync
            if(vSyncState){
                //disable 
                glfwSwapInterval(0);
            }else{
                glfwSwapInterval(1);
            }
            std::cout << "V-Sync: " << vSyncState << std::endl;
            vSyncSwitch = !vSyncSwitch;
        }else if(glfwGetKey(handle, GLFW_KEY_V) == GLFW_RELEASE && vSyncSwitch){
            vSyncSwitch = !vSyncSwitch;
        }
    }
}

//initialization
void Window::init(){
    //Here goes the initial processing of shaders, textues, and objects
    game = new gameHandler(width, height, handle);
    game->init();
}

//updating
void Window::update(){
    //update any variables like moving objects or updating input
    //* NOTE: that any object that needs input will need to have reference to the window handleas a parameter to be passed down
    game->update(DeltaTime);
    game->setGameState(App_State);
    game->setControllerState(Input_State);
}

//rendering
void Window::render(){
    //here update visually the objects, shaders, textures, etc
    game->render();
}

//Frames
void Window::getFrameTime(){
    this->currentTime = glfwGetTime();
    this->timeDiff = this->currentTime - this->prevTime;
    this->counter++;
    if(this->timeDiff >= 1.0 / 30.0){
        //display frame per second & frame time
        std::string FPS = std::to_string((1.0 / this->timeDiff) * this->counter);
        std::string ms = std::to_string((this->timeDiff / this->counter) * 1000);
        //set up title
        std::string newTitle = "Project-Heaven - " + FPS + "FPS / " + ms + "ms";
        glfwSetWindowTitle(this->handle, newTitle.c_str());
        this->prevTime = this->currentTime;
        this->counter = 0;
    }
}