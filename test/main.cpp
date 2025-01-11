#include "inc/test_window.hpp"

int main(int argc, char* argv[]){

    TestWindow window;

    window.initializeWindow(1280, 720);

    window.runtime();

    return 0;
}