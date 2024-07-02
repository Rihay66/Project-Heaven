#include "inc/test_window.hpp"

int main(int argc, char* argv[]){

    TestWindow* window = new TestWindow(800, 600);

    window->initializeWindow();

    window->runtime();

    delete window;

    return 0;
}