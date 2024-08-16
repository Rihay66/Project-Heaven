#include <utilities/glfw_observer.hpp>

// include standard library
#include <cstdlib>

// initalize resources
bool                Observer::isAutoClearSet = false;

void Observer::Init(){
    // initialize ImGUI


}

void Observer::Render(){
    // call ImGUI render
    
}

void Observer::clear(){

}

void Observer::setUpAutoClear(){
    // set up on exit to call the Clear()
    if(!isAutoClearSet && std::atexit(clear) == 0){
        isAutoClearSet = true; // disable calling this function again
    }
}