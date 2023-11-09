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

float Window::getDeltaTime(){
    // calculate delta time
    currentFrame = glfwGetTime();
    this->DeltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    return this->DeltaTime;
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
    if(glfwJoystickPresent(GLFW_JOYSTICK_1) == GLFW_TRUE && !controllerCheck){
        //print out that the joystick is connected
        const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
        std::cout << "Controller is connected! ID: " << name << std::endl;
        std::cout << "MSG: Controller input is enabled!" << std::endl;
        Input_State = KMANDCONTROLLER;
        controllerCheck = !controllerCheck;
    }else if(glfwJoystickPresent(GLFW_JOYSTICK_1) == GLFW_FALSE && controllerCheck){
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

//TODO: Fix the input of the camera

//Single threaded runtime of update and render()
void Window::runtime(){
    while(!glfwWindowShouldClose(this->handle)){
        // Get Deltatime
        this->getDeltaTime();

        // check for glfw events
        glfwPollEvents();

        // check for main window input
        getInput();

        // update any input, values, objects, loading etc..
        update();

        //render background
        //? Will be removed in final version
        glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        //draw or render
        render();

        //swap buffers
        glfwSwapBuffers(handle);
    }
}

//Create multithreaded runtime of update() and render()
void Window::threadedRuntime(){
    //Create two threads 

    //Create a seperate update thread
    std::thread updateT([this](){
        while(!glfwWindowShouldClose(handle)){
            //Get Deltatime
            this->getDeltaTime();

            //check for glfw events
            glfwPollEvents();

            //check for main window input
		    getInput();

		    //update any input, values, objects, loading etc..
		    update();
        }
    });

    while (!glfwWindowShouldClose(handle)){
        //render background
        //? Will be removed in final version
        glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        //draw or render
        render();

        //swap buffers
        glfwSwapBuffers(handle);
    }

    //Join the threaded after quit flag
    updateT.join();

    //Exiting print
    printf("Joining threads!\n");
}

//initialization
void Window::init(){
    //Here goes the initial processing of shaders, textues, and objects
}

//updating
void Window::update(){
    //update any variables like moving objects or updating input
    //* NOTE: that any object that needs input will need to have reference to the window handles a parameter to be passed down
}

//rendering
void Window::render(){
    //here update visually the objects, shaders, textures, etc
}