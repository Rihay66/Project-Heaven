#include "../inc/window.h"

//Callback func
static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

//static vars
static bool isDebug = false;
static bool pressed = false;

//Window constructor, intializes GLFW and GLAD then creates a window with the passed parameters
Window::Window(int h, int w, const char* name) : DeltaTime(0), State(ACTIVE){

    //init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
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

    //set openGL window size
    glViewport(0, 0, h, w);
    //set up call back to update the opengl window
    glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);

    //set up rendering for 2D
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "window successfully created" << std::endl;
}

//Destructor
Window::~Window(){
    printf("Exiting...\n");
    glfwTerminate();
}

//Handle main window input function
void Window::window_input(){
    //Check if escape key being pressed to exit
    if(glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        //set window to close
        glfwSetWindowShouldClose(handle, true);
    }

    //debug enabler button
    if(glfwGetKey(handle, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS && !pressed){
        isDebug = !isDebug;
        //check the isDebug value and set the proper app state
        if(isDebug){
            State = DEBUG;
            std::cout << "MSG: DEBUG IS ENABLED! State: " << std::endl;
        }
        else{
            State = ACTIVE;
            std::cout << "MSG: DEBUG IS DISABLED State: " << std::endl;
        }
        pressed = !pressed;
    }else if(glfwGetKey(handle, GLFW_KEY_GRAVE_ACCENT) == GLFW_RELEASE && pressed){
        pressed = !pressed;
    }
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