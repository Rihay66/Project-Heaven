#include "../inc/test_window.hpp"

TestWindow::TestWindow(int w, int h) : Window(w, h){

}

TestWindow::~TestWindow(){

}

void TestWindow::init(){

}

void TestWindow::update(){

}

void TestWindow::stepUpdate(double ts){

}

void TestWindow::render(double alpha){

    //render background
    glClearColor(0.35f, 0.35f, 0.35f, 1.0f);
}