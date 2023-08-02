#include "../inc/window.hpp"

#include "../inc/gameHandler.hpp"

//Callback func
static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

//static vars
static bool isDebug = false;
static bool pressed = false;

//Instantiate gameHandler object
gameHandler* game;

//Window constructor, intializes GLFW and GLAD then creates a window with the passed parameters
Window::Window(int h, int w, const char* name) : DeltaTime(0), State(ACTIVE), width(0), height(0){

    //set local vars
    width = w;
    height = h;

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

    //set up call back to update the opengl window
    glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);
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
            std::cout << "MSG: DEBUG IS ENABLED!" << std::endl;
            //disable vsync
            glfwSwapInterval(0);
        }
        else{
            State = ACTIVE;
            std::cout << "MSG: DEBUG IS DISABLED!" << std::endl;
            //enable vsync
            glfwSwapInterval(1);
        }
        pressed = !pressed;
    }else if(glfwGetKey(handle, GLFW_KEY_GRAVE_ACCENT) == GLFW_RELEASE && pressed){
        pressed = !pressed;
    }

    //debug line wireframe
    if(isDebug && glfwGetKey(handle, GLFW_KEY_TAB) == GLFW_PRESS){
        //set writeframe
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }else{
        //stop wireframe
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
    game->setGameState(State);
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