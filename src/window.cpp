#include "../inc/window.h"

//Callback func
static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

//Window constructor, intializes GLFW and GLAD then creates a window with the passed parameters
Window::Window(int h, int w, const char* name){

    //init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);

    std::cout << "window successfully created" << std::endl;
}

//Destructor
Window::~Window(){
    printf("Exiting...\n");
    glfwTerminate();
    exit(0);
}

//Handle main window input function
void Window::window_input(){
    //Check if escape key being pressed to exit
    if(glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        //set window to close
        glfwSetWindowShouldClose(handle, true);
    }
}