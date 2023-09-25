#include <window/window.hpp>

//static vars
static bool isDebug = false;
static bool pressed = false;
static bool controllerCheck = false;
static bool controllerEnable = false;
static bool inputSwitch = false;
static bool vSyncSwitch = false;
static bool vSyncState = false;

//Used to display sdl errors and exit with an error
static void sdl_die(const char * message) {
  fprintf(stderr, "%s: %s\n", message, SDL_GetError());
  exit(2);
}

//Window constructor, intializes GLFW and GLAD then creates a window with the passed parameters
Window::Window(int h, int w, const char* name) : DeltaTime(0), App_State(ACTIVE), Input_State(KM), width(0), height(0){

    //set local vars
    width = w;
    height = h;

    //init SDL
    // Initialize SDL 
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        sdl_die("Couldn't initialize SDL");
    
    atexit (SDL_Quit);
    SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

    // Request an OpenGL 4.5 context (should be core)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //Init the widnow 
    this->window =SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    //Check if window was initialized
    if (window == nullptr) 
        sdl_die("Couldn't set video mode");

    //Create OpenGL context for GLAD and SDL to talk to each other
    glContext = SDL_GL_CreateContext(window);
    if (glContext == NULL) 
        sdl_die("Failed to create OpenGL context");

    //Init GLAD
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
        std::cout << "Failed to init GLAD!" << std::endl;
        exit(-1);
    }
    // Use v-sync
    SDL_GL_SetSwapInterval(1);

    //set openGL window size
    glViewport(0, 0, h, w);

    //set up rendering for 2D
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Disable depth test and face culling.
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    std::cout << "window successfully created" << std::endl;
}

//Destructor
Window::~Window(){
    //delete any pointers
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//Handle main window input function
void Window::window_input(){
    /*
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
    */
   //Use Event and get input
    if(eventHandle.type == SDL_KEYDOWN){ //Check if there's a key being pressed
        if(eventHandle.key.keysym.sym == SDLK_ESCAPE){//Check if the key was the escape key
            //Exit from the app
            this->quit = true;
        }
    }else if(eventHandle.type == SDL_QUIT){
        //Check for Window exit button event
        this->quit = true;
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

//Frames
void Window::getFrameTime(){
    /*
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
    */
}