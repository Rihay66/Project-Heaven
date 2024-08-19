#include <utilities/glfw_observer.hpp>

// include ImGUI implementation for GLFW and OpenGL
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// include standard library
#include <cstdlib>

// initalize resources
bool                Observer::isFrameCreated = false;
bool                Observer::isAutoClearSet = false;

void Observer::Init(GLFWwindow* handle){
    // set up auto clear
    setUpAutoClear();

    // initialize ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // grab imgui io
    ImGuiIO& io = ImGui::GetIO();
    // enable keyboard interaction
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // set up platform/render backends
    ImGui_ImplGlfw_InitForOpenGL(handle, true);
    ImGui_ImplOpenGL3_Init();
}

void Observer::NewObservations(){
    // start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // set frame creation flag
    isFrameCreated = true;
}

void Observer::ObserveDemo(){
    // show a imgui demo window
    
    // show demo window
    ImGui::ShowDemoWindow(); 
}

void Observer::FlushObservations(){
    // check if frame wasn't created
    if(!isFrameCreated)
        return; // stop function

    // call ImGUI render
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // set frame creation flag
    isFrameCreated = false;
}

void Observer::clear(){
    // clean ImGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Observer::setUpAutoClear(){
    // set up on exit to call the Clear()
    if(!isAutoClearSet && std::atexit(clear) == 0){
        isAutoClearSet = true; // disable calling this function again
    }
}