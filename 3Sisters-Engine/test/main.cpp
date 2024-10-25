#include "inc/test_window.hpp"

int main(int argc, char* argv[]){

    TestWindow window(1280, 720);

    window.initializeWindow();

    window.runtime();

    return 0;
}