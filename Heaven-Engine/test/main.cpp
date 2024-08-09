//#include "inc/test_window.hpp"

#include <resourceSystems/managers/tag_manager.hpp>

//? debug print
#include <iostream>

// define a test struct
struct Foo {
    double t;
    const int i = 10;
};

int main(int argc, char* argv[]){

    /*
    TestWindow* window = new TestWindow(1280, 720);

    window->initializeWindow();

    window->runtime();

    delete window;
    */

    // test out tag manager
    float var = 1.0f;
    Foo bar;
    bar.t = 5.0f;
    TagManager::AddTag("test", var);
    TagManager::AddTag("bar", bar);

    bar.t = 1.0f;

    std::cout << TagManager::GetTag<float>("test") << "\n";
    std::cout << TagManager::GetTag<Foo>("bar").t << "\n";

    return 0;
}