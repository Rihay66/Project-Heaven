#include "../inc/gameWindow.hpp"

GameWindow::GameWindow(int w, int h, const char* name) : Window(w, h, name){}

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
}

void GameWindow::update(){
    //Update the main game loop
    game->update(DeltaTime);
    game->setGameState(App_State);
    game->setControllerState(Input_State);
}

void GameWindow::render(){
    //Render the game
    game->render();
}