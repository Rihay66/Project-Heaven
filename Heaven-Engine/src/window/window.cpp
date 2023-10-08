#include <window/window.hpp>

//static vars
static bool isDebug = false;
static bool controllerCheck = false;
static bool controllerEnable = false;
static bool inputSwitch = false;

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
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
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
    this->window =SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, height, width, SDL_WINDOW_OPENGL);
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

    //Enable SDL event joystick handle
    SDL_GameControllerEventState(SDL_ENABLE);

    SDL_GetWindowSize(window, &w, &h);
	glViewport(0, 0, w, h);

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
    if(joystick != nullptr){
        SDL_GameControllerClose(joystick);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::getEvents(){
    //This function must be called once inside a loop
    // Get events from SDL
    while (SDL_PollEvent(&this->eventHandle))
    {
        // Stantard base event handling
        // Check for joysticks if available
        if (SDL_NumJoysticks() > 0 && !controllerCheck){
            // Loop and get controllers
            for (int i = 0; i < sizeof(controllerNames) / sizeof(controllerNames[0]); i++){
                if (controllerNames[i] != SDL_GameControllerNameForIndex(i)){
                    printf("%s : CONNECTED!\n", SDL_GameControllerNameForIndex(i));
                    controllerNames[i] = SDL_GameControllerNameForIndex(i);
                    controllerCheck = true;
                }
            }
        }
        else{
            // Disable controller enable flag
            controllerCheck = false;
        }

        // Use Event and get input
        switch (eventHandle.type)
        {
        case SDL_QUIT:
            //Check for Window exit button event
            //Set quit flag to true to be used to exit out of application
            this->quit = true;
            //Exit out of whole function
            return;
        case SDL_KEYDOWN:
            //Check for which key was pressed
            switch (eventHandle.key.keysym.sym)
            {
            case SDLK_ESCAPE: //Check if escape was pressed
                //Set quit flag to be true to be used to exit out of application
                this->quit = true;
                //Exit out of whole function
                return;
            case SDLK_BACKQUOTE: //Check if the ` was pressed
                //Enable or disable debug mode
                isDebug = !isDebug;

                //Check for isDebug flag and
                if(isDebug){
                    App_State = DEBUG;
                    std::cout << "MSG: DEBUG IS ENABLED!" << std::endl;
                }else{
                    App_State = ACTIVE;
                    std::cout << "MSG: DEBUG IS DISABLED!" << std::endl;
                }
            case SDLK_TAB: //Check if TAB was pressed
                //*NOTE: When a controller is found, for now enable it as first controller
                if(controllerCheck){
                    //Enable or disable the controllerEnable Flag
                    controllerEnable = !controllerEnable;
                    if(controllerEnable){
                        // Open controller joystick and switch input mode
                        joystick = SDL_GameControllerOpen(0);
                        Input_State = KMANDCONTROLLER;
                        printf("MSG: Controller Input Enabled!\n");
                    }else{
                        // Close joystick and switch input mode
                        SDL_GameControllerClose(joystick);
                        Input_State = KM;
                        printf("MSG: Controller Input Disabled!\n");
                    }
                }
            default:
                break;
            }
            break;
        default:
            break;
        }

        // Call virtual method for additional input
        this->input(this->eventHandle);

        //Exit out of handling events
        break;
    }
}

//Handle main window input function
void Window::input(SDL_Event handle){
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
void Window::getFrameTime(float count){
   std::string FPS = std::to_string(1.0f/count);
   std::string ms = std::to_string(count);
   std::string newTitle = "Project-Heaven - " + FPS + "FPS / " + ms + "ms";

   //Set up title
   SDL_SetWindowTitle(this->window, newTitle.c_str());
}