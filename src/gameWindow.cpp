#include "../inc/gameWindow.hpp"

//static var
static bool pressed = false;
static bool vSync = true;

GameWindow::GameWindow(int w, int h, const char* name) : Window(w, h, name){

}

GameWindow::~GameWindow(){
    //delete any pointers
    delete game;
}

void GameWindow::init(){
    //Init the the game 
    game = new gameHandler(width, height, this->handle);
    game->init();
}

void GameWindow::input(){
    //Add additional input for the window

    //! When a menu is created for entering and exiting the game this can be deprecated
    //Check if escape key being pressed to exit - button
    if(glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        //set window to close
        glfwSetWindowShouldClose(handle, true);
    }

    //V-sync disabler and enabler
    if(glfwGetKey(handle, GLFW_KEY_V) == GLFW_PRESS && !pressed){
        //Flip v-sync boolean
        vSync = !vSync;
        
        //Enable/Disable V-sync
        glfwSwapInterval((int)vSync);
        std::cout << "Vsync status: " << vSync  << "\n";

        pressed = !pressed;
    }else if(glfwGetKey(handle, GLFW_KEY_V) == GLFW_RELEASE && pressed){
        pressed = !pressed;
    }

}

void GameWindow::update(){
    //Update the main game loop
    game->update(DeltaTime);
    game->setGameState(App_State);
    game->setControllerState(Input_State);
}

void GameWindow::render(){
    //Render the game
    game->render(DeltaTime);
}