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

void GameWindow::input(SDL_Event handle){
    //Add additional input
    game->events(this->eventHandle);
}

void GameWindow::update(){
    game->update(DeltaTime);
    game->setGameState(App_State);
    game->setControllerState(Input_State);
}

void GameWindow::render(){
    game->render();
}