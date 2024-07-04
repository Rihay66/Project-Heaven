#include "inc/test_window.hpp"

int main(int argc, char* argv[]){

    TestWindow* window = new TestWindow(320, 200);

    window->initializeWindow();

    window->runtime();

    delete window;

    return 0;
}