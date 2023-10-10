#include <window/window.hpp>

//static vars
static bool isDebug = false;
static bool pressed = false;
static bool controllerCheck = false;

//Callback func
static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

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
    glfwTerminate();
}

void Window::getInput(){

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

    //check for joystick
    if(glfwJoystickPresent(GLFW_JOYSTICK_1) == true && !controllerCheck){
        //print out that the joystick is connected
        const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
        std::cout << "Controller is connected! ID: " << name << std::endl;
        std::cout << "MSG: Controller input is enabled!" << std::endl;
        Input_State = KMANDCONTROLLER;
        controllerCheck = !controllerCheck;
    }else if(glfwJoystickPresent(GLFW_JOYSTICK_1) == false && controllerCheck){
        std::cout << "Controller is disconnected!" << std::endl;
        std::cout << "MSG: Controller input is disabled!" << std::endl;
        Input_State = KM;
        controllerCheck = !controllerCheck;
    }

    //Call additional input
    this->input();
}

//Handle main window input function
void Window::input(){
    //Here goes additional input that is within SDL event handling and getEvent() loop
    //Can be overwritten 
}

//initialization
void Window::init(){
    //Here goes the initial processing of shaders, textues, and objects
}

//updating
void Window::update(){
    //update any variables like moving objects or updating input
    //* NOTE: that any object that needs input will need to have reference to the window handleas a parameter to be passed down
}

//rendering
void Window::render(){
    //here update visually the objects, shaders, textures, etc
}

//Frames
void Window::getFrameTime(){
    //TODO: Move getting the frame time to be using the engine's UI renderer and not GLFW
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