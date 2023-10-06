#include "../inc/gameWindow.hpp"

GameWindow::GameWindow(int w, int h, const char* name) : Window(w, h, name){
}

GameWindow::~GameWindow(){
    //delete any pointers
    delete game;
}

void GameWindow::init(){
    game = new gameHandler(width, height);
    game->init();
}

void GameWindow::input(){
    //Add additional input
    
}

void GameWindow::update(){
    if(game->joystick == nullptr){
        game->joystick = this->joystick;
    }

    game->update(DeltaTime);
    game->setGameState(App_State);
    game->setControllerState(Input_State);
}

void GameWindow::render(){
    game->render();
}